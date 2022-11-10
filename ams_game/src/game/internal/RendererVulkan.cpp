/*
 * Copyright 2022 - Anthony Sorge
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions 
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef AMS_MODULES
#include "ams/game/internal/RendererVulkan.hpp"
#include "ams/game/Window.hpp"
#else
import ams.game.internal.RendererVulkan;
import ams.game.Window;
#endif

#include <GLFW/glfw3.h>


VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace ams::internal {

RendererVulkan::RendererVulkan(const ApplicationInfo& applicationInfo, Window* window)
  : RendererBackend(applicationInfo, window)
{
  if (glfwVulkanSupported() == GLFW_FALSE)
    return;
  vk::ApplicationInfo appInfo {
    .pApplicationName = applicationInfo.name.c_str(),
    .applicationVersion = applicationInfo.version,
    .pEngineName = applicationInfo.engineName.c_str(),
    .engineVersion = applicationInfo.engineVersion,
    .apiVersion = VK_API_VERSION_1_2
  };
  // discover extensions
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  vk::InstanceCreateInfo instanceCreateInfo {
    .pApplicationInfo = &appInfo,
    .enabledExtensionCount = glfwExtensionCount,
    .ppEnabledExtensionNames = glfwExtensions
  };
  vk::DynamicLoader dl;
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
  VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
  // create vulkan instance
  _instance = vk::createInstance(instanceCreateInfo);
  VULKAN_HPP_DEFAULT_DISPATCHER.init(_instance);
  // discover physical device
  _physicalDevices = _instance.enumeratePhysicalDevices();
  // create vulkan surface
  VkSurfaceKHR surface;
  glfwCreateWindowSurface(_instance, window->getHandle(), nullptr, &surface);
  _surface = vk::SurfaceKHR(surface);
  // discover queue family
  for (const auto& physicalDevice : _physicalDevices) {
    auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();
    for (uint32_t i = 0; i < queueFamilyProperties.size(); i++) {
      if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) {
        _queueFamilyIndex = i;
        break;
      }
    }
  }
  // create logical device
  float queuePriority = 1.0f;
  vk::DeviceQueueCreateInfo deviceQueueCreateInfo {
    .queueFamilyIndex = _queueFamilyIndex,
    .queueCount = 1,
    .pQueuePriorities = &queuePriority
  };
  vk::DeviceCreateInfo deviceCreateInfo {
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &deviceQueueCreateInfo
  };
  _device = _physicalDevices[0].createDevice(deviceCreateInfo);
}

RendererVulkan::~RendererVulkan() = default;

bool RendererVulkan::init() {
  _queue = _device.getQueue(_queueFamilyIndex, 0);

  // create swapchain
  vk::SurfaceCapabilitiesKHR surfaceCapabilities = _physicalDevices[0].getSurfaceCapabilitiesKHR(_surface);
  vk::SurfaceFormatKHR surfaceFormat = _physicalDevices[0].getSurfaceFormatsKHR(_surface)[0];
  vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
  vk::Extent2D extent = surfaceCapabilities.currentExtent;
  vk::SwapchainCreateInfoKHR swapchainCreateInfo {
    .surface = _surface,
    .minImageCount = surfaceCapabilities.minImageCount,
    .imageFormat = surfaceFormat.format,
    .imageColorSpace = surfaceFormat.colorSpace,
    .imageExtent = extent,
    .imageArrayLayers = 1,
    .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
    .preTransform = surfaceCapabilities.currentTransform,
    .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
    .presentMode = presentMode,
    .clipped = VK_TRUE
  };
  _swapchain = _device.createSwapchainKHR(swapchainCreateInfo);
  _swapchainImages = _device.getSwapchainImagesKHR(_swapchain);
  _swapchainImageViews.resize(_swapchainImages.size());
  for (size_t i = 0; i < _swapchainImages.size(); i++) {
    vk::ImageViewCreateInfo imageViewCreateInfo {
      .image = _swapchainImages[i],
      .viewType = vk::ImageViewType::e2D,
      .format = surfaceFormat.format,
      .subresourceRange = {
        .aspectMask = vk::ImageAspectFlagBits::eColor,
        .levelCount = 1,
        .layerCount = 1
      }
    };
    _swapchainImageViews[i] = _device.createImageView(imageViewCreateInfo);
  }

  // create render pass
  vk::AttachmentDescription colorAttachment {
    .format = surfaceFormat.format,
    .samples = vk::SampleCountFlagBits::e1,
    .loadOp = vk::AttachmentLoadOp::eClear,
    .storeOp = vk::AttachmentStoreOp::eStore,
    .stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
    .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
    .initialLayout = vk::ImageLayout::eUndefined,
    .finalLayout = vk::ImageLayout::ePresentSrcKHR
  };
  vk::AttachmentReference colorAttachmentRef {
    .attachment = 0,
    .layout = vk::ImageLayout::eColorAttachmentOptimal
  };
  vk::SubpassDescription subpass {
    .pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
    .colorAttachmentCount = 1,
    .pColorAttachments = &colorAttachmentRef
  };
  vk::RenderPassCreateInfo renderPassCreateInfo {
    .attachmentCount = 1,
    .pAttachments = &colorAttachment,
    .subpassCount = 1,
    .pSubpasses = &subpass
  };
  _renderPass = _device.createRenderPass(renderPassCreateInfo);

  // create framebuffers
  _framebuffers.resize(_swapchainImageViews.size());
  for (size_t i = 0; i < _swapchainImageViews.size(); i++) {
    vk::FramebufferCreateInfo framebufferCreateInfo {
      .renderPass = _renderPass,
      .attachmentCount = 1,
      .pAttachments = &_swapchainImageViews[i],
      .width = extent.width,
      .height = extent.height,
      .layers = 1
    };
    _framebuffers[i] = _device.createFramebuffer(framebufferCreateInfo);
  }

  // create command pool
  vk::CommandPoolCreateInfo commandPoolCreateInfo {
    .queueFamilyIndex = _queueFamilyIndex
  };
  _commandPool = _device.createCommandPool(commandPoolCreateInfo);

  // create command buffers
  vk::CommandBufferAllocateInfo commandBufferAllocateInfo {
    .commandPool = _commandPool,
    .level = vk::CommandBufferLevel::ePrimary,
    .commandBufferCount = static_cast<uint32_t>(_swapchainImages.size())
  };
  _commandBuffers = _device.allocateCommandBuffers(commandBufferAllocateInfo);

  // create semaphores
  vk::SemaphoreCreateInfo semaphoreCreateInfo;
  _imageAvailableSemaphore = _device.createSemaphore(semaphoreCreateInfo);
  _renderFinishedSemaphore = _device.createSemaphore(semaphoreCreateInfo);

  // create vertex buffer
  vk::BufferCreateInfo bufferCreateInfo {
    .size = sizeof(vertices),
    .usage = vk::BufferUsageFlagBits::eVertexBuffer,
    .sharingMode = vk::SharingMode::eExclusive
  };
  return true;
}


void RendererVulkan::shutdown() {

}

/**
 * @brief RendererVulkan::beginFrame
 * @details This function is called at the beginning of each frame.
 */
void RendererVulkan::beginFrame() {
  // start recording commands to _commandBuffers
  _commandBuffers = _device.allocateCommandBuffers(vk::CommandBufferAllocateInfo {
    .commandPool = _commandPool,
    .level = vk::CommandBufferLevel::ePrimary,
    .commandBufferCount = 1
  });
  _commandBuffers[0].begin(vk::CommandBufferBeginInfo {
    .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit
  });
  // begin render pass
  
}

void RendererVulkan::endFrame() {

}

void RendererVulkan::draw() {

}

} // ams


/*
class RendererVulkanImpl {
public:
  // instance
  VkInstance instance;
  // physical device
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  // logical device
  VkDevice device;
  // queue
  VkQueue graphicsQueue;
  // surface
  VkSurfaceKHR surface;
  // swap chain
  VkSwapchainKHR swapChain;
  // swap chain images
  std::vector<VkImage> swapChainImages;
  // swap chain image format
  VkFormat swapChainImageFormat;
  // swap chain extent
  VkExtent2D swapChainExtent;
  // swap chain image views
  std::vector<VkImageView> swapChainImageViews;
  // render pass
  VkRenderPass renderPass;
  // graphics pipeline
  VkPipeline graphicsPipeline;
  // pipeline layout
  VkPipelineLayout pipelineLayout;
  // framebuffers
  std::vector<VkFramebuffer> swapChainFramebuffers;
  // command pool
  VkCommandPool commandPool;
  // command buffers
  std::vector<VkCommandBuffer> commandBuffers;
  // semaphores
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  // fences
  std::vector<VkFence> inFlightFences;
  // current frame
  size_t currentFrame = 0;
  // validation layers
  const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };
  // device extensions
  const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };
  // debug messenger
  VkDebugUtilsMessengerEXT debugMessenger;
  // debug callback
  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
  ) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
  }
  // check validation layer support
  bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (const char* layerName : validationLayers) {
      bool layerFound = false;
      for (const auto& layerProperties : availableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
          layerFound = true;
          break;
        }
      }
      if (!layerFound) {
        return false;
      }
    }
    return true;
  }
  // create instance
  void createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
      throw std::runtime_error("validation layers requested, but not available!");
    }
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (enableValidationLayers) {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
      populateDebugMessengerCreateInfo(debugCreateInfo);
      createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    } else {
      createInfo.enabledLayerCount = 0;
      createInfo.pNext = nullptr;
    }
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
      throw std::runtime_error("failed to create instance!");
    }
  }
  // get required extensions
  std::vector<const char*> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers) {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
  }
  // setup debug messenger
  void setupDebugMessenger() {
    if (!enableValidationLayers) return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);
    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
      throw std::runtime_error("failed to set up debug messenger!");
    }
  }
  // populate debug messenger create info
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
      VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
  }
  // pick physical device
  void pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    for (const auto& device : devices) {
      if (isDeviceSuitable(device)) {
        physicalDevice = device;
        break;
      }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }
  }
  RendererVulkanImpl() {}
  ~RendererVulkanImpl();
};
*/
