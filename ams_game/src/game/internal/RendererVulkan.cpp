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
#include "ams/game/Util.hpp"
#else
import ams.game.internal.RendererVulkan;
import ams.game.Window;
import ams.game.Util;
#endif

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VULKAN_HPP_STORAGE_SHARED 1
#define VULKAN_HPP_STORAGE_SHARED_EXPORT AMS_GAME_EXPORT
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_to_string.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <optional>
#include <coroutine>
#include <set>



VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace ams::internal {

using DebugSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT;
using DebugType = vk::DebugUtilsMessageTypeFlagBitsEXT;

struct DebugConfig {
  const bool enabled = AMSGraphicsDebug;
  const bool enableValidationLayers = AMSGraphicsDebug;
  const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };
  /** device extensions required for debugging */
  const std::vector<const char*> deviceExtensions = {
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
  };
  const vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo = {
    .sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT,
    .messageSeverity = DebugSeverity::eVerbose | DebugSeverity::eInfo | DebugSeverity::eWarning | DebugSeverity::eError,
    .messageType = DebugType::eGeneral | DebugType::ePerformance | DebugType::eValidation,
    .pfnUserCallback = defaultDebugCallback,
  };

  inline static constexpr DebugSeverity debugSeverity = 
    AMSGraphicsDebugSeverity < GraphicsDebugSeverity::Warning
      ? DebugSeverity::eError
      : AMSGraphicsDebugSeverity < GraphicsDebugSeverity::Info
        ? DebugSeverity::eWarning
        : AMSGraphicsDebugSeverity < GraphicsDebugSeverity::Debug
          ? DebugSeverity::eInfo : DebugSeverity::eVerbose;

  inline static VKAPI_ATTR
  VkBool32 VKAPI_CALL defaultDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                           VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                           VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
                                           void* /*pUserData*/ ) {
    std::ostringstream message;
    message << vk::to_string(static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>( messageSeverity )) << ": "
            << vk::to_string(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>( messageTypes )) << ":" << std::endl;
    message << std::string("\t") << "messageIDName   = <" << pCallbackData->pMessageIdName << ">" << std::endl;
    message << std::string("\t") << "messageIdNumber = " << pCallbackData->messageIdNumber << std::endl;
    message << std::string("\t") << "message         = <" << pCallbackData->pMessage << std::endl;
    if (0 < pCallbackData->queueLabelCount) {
      message << std::string("\t") << "Queue Labels:" << std::endl;
      for (uint32_t i = 0; i < pCallbackData->queueLabelCount; i++) {
        message << std::string("\t\t") << "labelName = <" << pCallbackData->pQueueLabels[i].pLabelName << ">" << std::endl;
      }
    }
    if (0 < pCallbackData->cmdBufLabelCount) {
      message << std::string("\t") << "CommandBuffer Labels:" << std::endl;
      for (uint32_t i = 0; i < pCallbackData->cmdBufLabelCount; i++) {
        message << std::string("\t\t") << "labelName = <" << pCallbackData->pCmdBufLabels[i].pLabelName << ">" << std::endl;
      }
    }
    if (0 < pCallbackData->objectCount) {
      message << std::string("\t") << "Objects:" << std::endl;
      for (uint32_t i = 0; i < pCallbackData->objectCount; i++) {
        message << std::string("\t\t") << "Object " << i << std::endl;
        message << std::string("\t\t\t") << "objectType   = "
                << vk::to_string(static_cast<vk::ObjectType>( pCallbackData->pObjects[i].objectType )) << std::endl;
        message << std::string("\t\t\t") << "objectHandle = " << pCallbackData->pObjects[i].objectHandle << std::endl;
        if (pCallbackData->pObjects[i].pObjectName) {
          message << std::string("\t\t\t") << "objectName   = <" << pCallbackData->pObjects[i].pObjectName << ">"  << std::endl;
        }
      }
    }
    if (static_cast<DebugSeverity>(messageSeverity) >= debugSeverity)
      std::cout << message.str() << std::endl;
    return false;
  }
};


struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  vk::SurfaceCapabilitiesKHR capabilities;
  std::vector<vk::SurfaceFormatKHR> formats;
  std::vector<vk::PresentModeKHR> presentModes;
};

struct DepthBuffer {
  vk::Image image;
  vk::Format format;
  vk::DeviceMemory memory;
  vk::ImageView view;
};

struct DataBuffer {
  size_t size;
  vk::Buffer buffer;
  vk::DeviceMemory memory;
  vk::BufferUsageFlagBits usage;
  vk::Flags<vk::MemoryPropertyFlagBits> memoryPropertyFlags;
};





struct AMS_GAME_EXPORT RendererVulkan::Impl {
  Window* window;
  // vulkan application info
  vk::ApplicationInfo _applicationInfo;
  // glfw required extensions
  std::vector<const char*> enabledExtensions;

  // required vulkan device extensions
  const std::vector<const char*> requiredDeviceExtensions {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

  
  // vulkan instance
  vk::Instance instance;
  // vulkan physical devices
  std::vector<vk::PhysicalDevice> physicalDevices;
  // vulkan physical device to use
  vk::PhysicalDevice physicalDevice;
  // vulkan logical device
  vk::Device device;
  // vulkan queue family indices
  QueueFamilyIndices indices;
  
  // vulkan surface
  vk::SurfaceKHR surface;
  
  Vec2<uint32_t> size;

  // vulkan queue family properties
//  QueueFamilyIndices queueFamilyIndices;
  // vulkan queue priority
  float queuePriority = 1.0f;
  // vulkan graphics queue
  vk::Queue graphicsQueue;

  // vulkan swapchain
  vk::SwapchainKHR swapchain;
  // vulkan swapchain images
  std::vector<vk::Image> swapchainImages;
  // vulkan swapchain image views
  std::vector<vk::ImageView> swapchainImageViews;
  // vulkan swapchain image format
  vk::Format swapchainImageFormat;
  // vulkan extent
  vk::Extent2D extent;

  // vulkan depth buffer
  DepthBuffer depthBuffer;
  
  DataBuffer uniformBuffer;
  vk::DescriptorPool descriptorPool;
  vk::DescriptorSetLayout descriptorSetLayout;
  vk::DescriptorSet descriptorSet;

  // vulkan render pass
  vk::RenderPass renderPass;
  // vulkan command pool
  vk::CommandPool commandPool;
  // vulkan command buffers
  std::vector<vk::CommandBuffer> commandBuffers;
  // vulkan framebuffers
  std::vector<vk::Framebuffer> framebuffers;
  // vulkan semaphores
  vk::Semaphore imageAvailableSemaphore;
  vk::Semaphore renderFinishedSemaphore;
  // vulkan fences
  std::vector<vk::Fence> inFlightFences;
  std::vector<vk::Fence> imagesInFlight;

  
  const DebugConfig dbgCfg;
  
  vk::DebugUtilsMessengerEXT debugMessenger;


  bool _isInitialized = false;
  
  Impl(const ApplicationInfo& appInfo, Window* window)
    : window(window)
  {
    if (glfwVulkanSupported() == GLFW_FALSE)
      return;
    _applicationInfo = vk::ApplicationInfo{
      .pApplicationName = appInfo.name.c_str(),
      .applicationVersion = appInfo.version,
      .pEngineName = appInfo.engineName.c_str(),
      .engineVersion = appInfo.engineVersion,
      .apiVersion = VK_API_VERSION_1_3
    };
    enabledExtensions = getRequiredExtensions();
    // create vulkan instance
    if (!createInstance())
      _isInitialized = false;
  }

  /**
   * @brief Step 1 of vulkan initialization.
   * Creates the vulkan instance.
   */
  bool createInstance() {
    // get vulkan instance process address
    vk::DynamicLoader dl;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr); // initialize vulkan-hpp dispatcher
    vk::InstanceCreateInfo instanceCreateInfo {
      .pApplicationInfo = &_applicationInfo,
      .enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size()),
      .ppEnabledExtensionNames = enabledExtensions.data()
    };
    if (dbgCfg.enableValidationLayers && !checkValidationLayerSupport()) {
      return throwOrDefault<std::runtime_error, bool>("validation layers requested, but not available!", false);
    } else if (dbgCfg.enableValidationLayers) {
      instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(dbgCfg.validationLayers.size());
      instanceCreateInfo.ppEnabledLayerNames = dbgCfg.validationLayers.data();
    }
    if (dbgCfg.enabled)
      instanceCreateInfo.pNext = &dbgCfg.debugUtilsMessengerCreateInfo;
    try {
      instance = vk::createInstance(instanceCreateInfo, nullptr);
      // initialize instance with dynamic dispatcher.
      VULKAN_HPP_DEFAULT_DISPATCHER.init(instance); // Calling instance methods will result in undefined behavior without this.
      _isInitialized = true;
    } catch (const vk::SystemError& err) {
      return false;
    }
    if (dbgCfg.enabled)
      if (createDebugUtilsMessengerEXT(instance, &dbgCfg.debugUtilsMessengerCreateInfo, nullptr, &debugMessenger) != vk::Result::eSuccess)
        return throwOrDefault<std::runtime_error, bool>("failed to set up debug messenger!", false);
    return true;
  }
  
  std::vector<const char*> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** pGlfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(pGlfwExtensions, pGlfwExtensions + glfwExtensionCount);
    if (dbgCfg.enabled) { // add a debug messenger
      // emplace all debugConfig.deviceExtensions
      extensions.insert(extensions.end(), dbgCfg.deviceExtensions.begin(), dbgCfg.deviceExtensions.end());
    }
    return extensions;
  }
  
  /**
   * @brief Initialize all members of the renderer which are required to create a logical device
   */
  bool initGPU() {
    if (!_isInitialized)
      return false;
    // create vulkan surface
    auto surf = createSurface();
    if (!surf.has_value()) {
      _isInitialized = false;
      return _isInitialized;
    }
    surface = *surf;
    // pick physical device
    auto dev = choosePhysicalDevice(surface);
    if (!dev.has_value()) {
      _isInitialized = false;
      return _isInitialized;
    }
    physicalDevice = *dev;
    indices = findQueueFamilies(physicalDevice, surface);
    // create vulkan device
    auto lodev = createLogicalDevice(physicalDevice, indices);
    if (!lodev.has_value()) {
      _isInitialized = false;
      return _isInitialized;
    }
    device = *lodev;
    graphicsQueue = device.getQueue(indices.graphicsFamily.value(), 0);
    auto ubuf = createUniformBuffer(physicalDevice, device);
    if (!ubuf.has_value()) {
      _isInitialized = false;
      return _isInitialized;
    }
    uniformBuffer = *ubuf;
    // TODO: https://github.com/KhronosGroup/Vulkan-Hpp/blob/f461105d147e52b246f5227607eb9910febacf0c/samples/07_InitUniformBuffer/07_InitUniformBuffer.cpp#L74
    
    _isInitialized = true;
    return _isInitialized;
  }
  
  /**
   * @brief Initialize renderer with a swapchain, render pass, command pool, command buffers, framebuffers, semaphores and fences.
   */
  bool initDeviceResources() {
    if (!_isInitialized)
      return false;
    // destroy old resources
    destroyDeviceGraphicsResources();
    // create vulkan swapchain
    auto scs = querySwapChainSupport(physicalDevice, surface); // swap chain support
    auto swap = createSwapchain(device, indices, scs);
    if (!swap.has_value())
      return false;
    swapchain = std::move(*swap);
    extent = getSwapExtent(scs.capabilities);
    swapchainImages = device.getSwapchainImagesKHR(swapchain);
    swapchainImageFormat = scs.formats.front().format;
    setImageViews(device, swapchainImages, swapchainImageFormat, swapchainImageViews);

    // create depth buffer
    auto depth = createDepthBuffer(physicalDevice, device);
    if (!depth.has_value())
      return false;
    depthBuffer = std::move(*depth);
    // create render pass
    if (!createRenderPass())
      return false;
    return true;
  }
  
  bool shutdown() {
    if (!_isInitialized)
      return false;
    if (!destroyDeviceGraphicsResources())
      return false;
    if (!destroyDeviceDataResources())
      return false;
    // destroy device
    if (device)
      device.destroy();
    // destroy surface
    instance.destroySurfaceKHR(surface);
    // destroy debug messenger
    if (dbgCfg.enabled)
      destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    // destroy instance
    instance.destroy();
    _isInitialized = false;
    return true;
  }
  
  bool destroyDeviceDataResources() {
    if (!_isInitialized)
      return false;
    // destroy uniform buffer
    if (uniformBuffer.buffer) {
      device.freeMemory(uniformBuffer.memory);
      device.destroyBuffer(uniformBuffer.buffer);
    }
    return true;
  }
  
  bool destroyDeviceGraphicsResources() {
    if (!_isInitialized)
      return false;
    // wait for device to finish
    device.waitIdle();
    // destroy semaphores if they exist
    if (imageAvailableSemaphore)
      device.destroySemaphore(imageAvailableSemaphore);
    if (renderFinishedSemaphore)
      device.destroySemaphore(renderFinishedSemaphore);
    // destroy framebuffers if they exist
    for (auto& framebuffer : framebuffers)
      device.destroyFramebuffer(framebuffer);
    // destroy command buffers if they exist
    if (commandPool)
      device.freeCommandBuffers(commandPool, commandBuffers);
    // destroy command pool if it exists
    if (commandPool)
      device.destroyCommandPool(commandPool);
    // destroy render pass if it exists
    if (renderPass)
      device.destroyRenderPass(renderPass);
    // destroy depth buffer if it exists
    if (depthBuffer.view)
      device.destroyImageView(depthBuffer.view);
    if (depthBuffer.image)
      device.destroyImage(depthBuffer.image);
    if (depthBuffer.memory)
      device.freeMemory(depthBuffer.memory);
    // destroy swapchain if it exists
    if (swapchain)
      device.destroySwapchainKHR(swapchain);
    // destroy image views if they exist
    for (auto& imageView : swapchainImageViews)
      device.destroyImageView(imageView);
    return true;
  }

  bool setupDebugMessenger(vk::Instance& inst) {
    if (!dbgCfg.enabled)
      return false;
    vk::DebugUtilsMessengerCreateInfoEXT createInfo = dbgCfg.debugUtilsMessengerCreateInfo;
    if (createDebugUtilsMessengerEXT(inst, &createInfo, nullptr, &debugMessenger) != vk::Result::eSuccess) {
      return false;
    }
    return true;
  }

  vk::Result createDebugUtilsMessengerEXT(vk::Instance& inst, const vk::DebugUtilsMessengerCreateInfoEXT* pCreateInfo, const vk::AllocationCallbacks* pAllocator, vk::DebugUtilsMessengerEXT* pDebugUtilsMessenger) {
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(inst.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
    if (!func)
      return vk::Result::eErrorExtensionNotPresent;
    return static_cast<vk::Result>(
      func(inst,
           reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(pCreateInfo),
           reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
           reinterpret_cast<VkDebugUtilsMessengerEXT*>(pDebugUtilsMessenger)
       )
    );
  }

  void destroyDebugUtilsMessengerEXT(vk::Instance& inst, vk::DebugUtilsMessengerEXT debugUtilsMessenger, const vk::AllocationCallbacks* pAllocator) {
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(inst.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
    if (func != nullptr) {
      func(inst, debugUtilsMessenger, reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
  }

  /**
   * @brief Step 2 of vulkan initialization.
   * Creates the surface.
   * This depends on createInstance() being called first.
   */
  std::optional<vk::SurfaceKHR> createSurface() const {
    if (window->getHandle() == nullptr)
      return throwOrDefault<std::runtime_error, std::optional<vk::SurfaceKHR>>("window handle is null!", std::nullopt);
    VkSurfaceKHR vkSurfaceKhr;
    glfwCreateWindowSurface(instance, window->getHandle(), nullptr, &vkSurfaceKhr);
    return vk::SurfaceKHR(vkSurfaceKhr);
  }
  
  /**                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
   * @brief Chooses the first eligible physical device.
   * This depends on createInstance() being called first.
   */
  std::optional<vk::PhysicalDevice> choosePhysicalDevice(const vk::SurfaceKHR& surf) const {
    auto devices = instance.enumeratePhysicalDevices();
    if (devices.empty())
      return throwOrDefault<std::runtime_error, std::optional<vk::PhysicalDevice>>(
        "Failed to find any GPU with Vulkan support", std::nullopt);
    auto it = std::find_if(devices.begin(), devices.end(), [&](const vk::PhysicalDevice& dv) {
      return isDeviceSuitable(dv, surf);
    });
    if (it == devices.end())
      return throwOrDefault<std::runtime_error, std::optional<vk::PhysicalDevice>>(
        "Failed to find a suitable GPU", std::nullopt);
    return *it;
  }
  
  /**                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
   * @brief If the provided physical device is suitable, it will be returned.
   */
  std::optional<vk::PhysicalDevice> choosePhysicalDevice(const vk::PhysicalDevice dev, const vk::SurfaceKHR& surf) const {
    if (!isDeviceSuitable(dev, surf))
      return std::nullopt;
    if (!checkDeviceExtensionSupport(dev))
      return std::nullopt;
    return dev;
  }
  
  /**
   * @brief Creates the logical device.
   * This depends choosePhysicalDevice() being called first.
   */
  std::optional<vk::Device> createLogicalDevice(vk::PhysicalDevice& dev, const QueueFamilyIndices& ind) const {
    // create the queue create infos
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {ind.graphicsFamily.value(), ind.presentFamily.value()};
    for (uint32_t queueFamily : uniqueQueueFamilies) {
      vk::DeviceQueueCreateInfo queueCreateInfo {
        .queueFamilyIndex = queueFamily,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
      };
      queueCreateInfos.push_back(queueCreateInfo);
    }
    vk::DeviceCreateInfo deviceCreateInfo{
      .flags = vk::DeviceCreateFlags(),
      .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
      .pQueueCreateInfos = queueCreateInfos.data(),
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size()),
      .ppEnabledExtensionNames = requiredDeviceExtensions.data(),
    };
    if (dbgCfg.enableValidationLayers) {
      deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(dbgCfg.validationLayers.size());
      deviceCreateInfo.ppEnabledLayerNames = dbgCfg.validationLayers.data();
    }
    // create the logical device
    auto ret = dev.createDevice(deviceCreateInfo);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(ret); // Calling device methods will result in undefined behavior without this.
    return ret;
  }
  
  /**
   * @brief Creates the uniform buffer.
   */
   std::optional<DataBuffer> createUniformBuffer(vk::PhysicalDevice& dev, vk::Device& lodev) const {
    DataBuffer ret;
    ret.size = sizeof(glm::mat4);
    ret.usage = vk::BufferUsageFlagBits::eUniformBuffer;
    ret.memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;
    vk::BufferCreateInfo bufferInfo {
      .flags = vk::BufferCreateFlags(),
      .size = ret.size,
      .usage = ret.usage,
      .sharingMode = vk::SharingMode::eExclusive
    };
    ret.buffer = lodev.createBuffer(bufferInfo);
    auto memRequirements = lodev.getBufferMemoryRequirements(ret.buffer);
    auto memType = findMemoryType(dev.getMemoryProperties(), memRequirements.memoryTypeBits, ret.memoryPropertyFlags);
    if (memType == -1)
      return throwOrDefault<std::runtime_error, std::optional<DataBuffer>>("failed to find suitable memory type!", std::nullopt);
    ret.memory = lodev.allocateMemory(vk::MemoryAllocateInfo {
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = memType
    });
    lodev.bindBufferMemory(ret.buffer, ret.memory, 0);
    return ret;
  }
   
  
  /**
   * @brief Creates the swapchain.
   */
  std::optional<vk::SwapchainKHR> createSwapchain(vk::Device& dev, const QueueFamilyIndices& ind, const SwapChainSupportDetails& scs) const {
    auto extent = getSwapExtent(scs.capabilities); // swap extent
    if (scs.formats.empty())
      return throwOrDefault<std::runtime_error, std::optional<vk::SwapchainKHR>>(
        "No surface formats available!", std::nullopt);
    auto surfaceFormat = scs.formats.front();
    if (surfaceFormat.format == vk::Format::eUndefined) {
      // if the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
      // there is no preferered format, so we assume VK_FORMAT_B8G8R8A8_UNORM
      surfaceFormat.format = vk::Format::eB8G8R8A8Unorm;
    }
    if (scs.presentModes.empty())
      return throwOrDefault<std::runtime_error, std::optional<vk::SwapchainKHR>>(
        "No surface present modes available!", std::nullopt);
    auto surfacePresentMode = scs.presentModes.front();
    
    vk::CompositeAlphaFlagBitsKHR compositeAlpha =
      (scs.capabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
        ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
        : (scs.capabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
            ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
            : (scs.capabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::eInherit)
                ? vk::CompositeAlphaFlagBitsKHR::eInherit
                : vk::CompositeAlphaFlagBitsKHR::eOpaque;
    
    vk::SwapchainCreateInfoKHR swapChainCreateInfo {
      .surface = surface,
      .minImageCount = scs.capabilities.minImageCount,
      .imageFormat = surfaceFormat.format,
      .imageColorSpace = surfaceFormat.colorSpace,
      .imageExtent = extent,
      .imageArrayLayers = 1,
      .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
      .preTransform = scs.capabilities.currentTransform,
      .compositeAlpha = compositeAlpha,
      .presentMode = surfacePresentMode,
      .clipped = true,
    };
    uint32_t qfi[2] = { ind.graphicsFamily.value(),
                        ind.presentFamily.value() }; // queue family indices
    if ( ind.graphicsFamily != ind.presentFamily ) {
      // If the graphics and present queues are from different queue families, we either have to explicitly transfer
      // ownership of images between the queues, or we have to create the swapchain with imageSharingMode as
      // VK_SHARING_MODE_CONCURRENT
      swapChainCreateInfo.imageSharingMode      = vk::SharingMode::eConcurrent;
      swapChainCreateInfo.queueFamilyIndexCount = 2;
      swapChainCreateInfo.pQueueFamilyIndices   = qfi;
    }
    // create the swapchain
    auto ret = dev.createSwapchainKHR(swapChainCreateInfo);
    return ret;
  }
  
  /**
   * @brief Creates the swapchain images.
   */
  void setImageViews(vk::Device& dev, const std::vector<vk::Image>& images, const vk::Format& format, std::vector<vk::ImageView>& imageViews) const {
    // destroy the old image views
    for (auto& iv : imageViews)
      dev.destroyImageView(iv);
    imageViews.resize(images.size());
    vk::ImageViewCreateInfo imageViewCreateInfo {
      .image = {},
      .viewType = vk::ImageViewType::e2D,
      .format = format,
      .components = {},
      .subresourceRange = {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
    };
    for (size_t i = 0; i < images.size(); i++) {
      imageViewCreateInfo.image = images[i];
      imageViews[i] = dev.createImageView(imageViewCreateInfo);
    }
  }
  
  /**
   * @brief Creates the depth buffer.
   * @param dev The physical device.
   * @param lodev The logical device.
   */
  std::optional<DepthBuffer> createDepthBuffer(const vk::PhysicalDevice& dev, vk::Device& lodev) {
    // destroy the old depth buffer if it exists TODO
//    if (depthBuffer.image)
//      lodev.destroyImage(depthBuffer.image);
//    if (depthBuffer.memory)
//      lodev.freeMemory(depthBuffer.memory);
//    if (depthBuffer.view)
//      lodev.destroyImageView(depthBuffer.view);
    // get the depth format
    auto format = vk::Format::eD16Unorm;
    auto formatProperties = dev.getFormatProperties(format);
    vk::ImageTiling tiling;
    if (formatProperties.linearTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
      tiling = vk::ImageTiling::eLinear;
    } else if (formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
      tiling = vk::ImageTiling::eOptimal;
    } else {
      return throwOrDefault<std::runtime_error, std::optional<DepthBuffer>>(
        "Depth format does not support depth stencil attachment!", std::nullopt);
    }
    auto imageCreateInfo = vk::ImageCreateInfo {
      .imageType = vk::ImageType::e2D,
      .format = format,
      .extent = {extent.width, extent.height, 1 },
      .mipLevels = 1,
      .arrayLayers = 1,
      .samples = vk::SampleCountFlagBits::e1,
      .tiling = tiling,
      .usage = vk::ImageUsageFlagBits::eDepthStencilAttachment,
      .sharingMode = vk::SharingMode::eExclusive,
      .queueFamilyIndexCount = 0,
      .pQueueFamilyIndices = nullptr,
      .initialLayout = vk::ImageLayout::eUndefined
    };
    DepthBuffer ret {
      .image = lodev.createImage(imageCreateInfo),
      .format = format
    };
    vk::MemoryRequirements memoryRequirements = lodev.getImageMemoryRequirements(ret.image);
    auto typeIndex = findMemoryType(dev.getMemoryProperties(), memoryRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);
    
    /*
    auto memoryProperties = dev.getMemoryProperties();
    vk::MemoryRequirements memoryRequirements = lodev.getImageMemoryRequirements(ret.image);
    auto typeBits = memoryRequirements.memoryTypeBits;
    auto typeIndex = uint32_t(~0);
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
      if ((typeBits & 1) == 1) {
        if ((memoryProperties.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal) == vk::MemoryPropertyFlagBits::eDeviceLocal) {
          typeIndex = i;
          break;
        }
      }
      typeBits >>= 1;
    }*/
    if (typeIndex == uint32_t(~0))
      return throwOrDefault<std::runtime_error, std::optional<DepthBuffer>>(
        "Could not find a memory type index that supports device local memory!", std::nullopt);
    ret.memory = lodev.allocateMemory(vk::MemoryAllocateInfo{
      .allocationSize = memoryRequirements.size,
      .memoryTypeIndex = typeIndex
    });
    lodev.bindImageMemory(ret.image, ret.memory, 0);
    ret.view = lodev.createImageView(vk::ImageViewCreateInfo{
      .image = ret.image,
      .viewType = vk::ImageViewType::e2D,
      .format = ret.format,
      .components = {},
      .subresourceRange = {vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1}
    });
    return ret;
  }
  
  /**
   * @brief Step 8 of vulkan initialization.
   * Creates the render pass.
   * Previous step createDepthBuffer(), must precede this step.
   */
  bool createRenderPass() {
    return true;
  }
  
  /**
   * @brief Checks for validation layer support. This should be called before vk::createInstance().
   */
  bool checkValidationLayerSupport() {
    auto availableLayers = vk::enumerateInstanceLayerProperties();
    for (const char* layerName : dbgCfg.validationLayers) {
      bool layerFound = false;
      for (const auto& layerProperties : availableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
          layerFound = true;
          break;
        }
      }
      if (!layerFound)
        return false;
    }
    return true;
  }

  /**
 * @brief Finds the queue family indices.
 * @param dev - the device to find the queue family indices for.
 */
  QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& dev, const vk::SurfaceKHR& surf) const {
    QueueFamilyIndices ret;
    auto queueFamilyProperties = dev.getQueueFamilyProperties();
    int i = 0;
    for (const auto& queueFamily : queueFamilyProperties) {
      // check if the queue family supports graphics
      if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
        ret.graphicsFamily = i;
      vk::Bool32 presentSupport = false;
      auto result = dev.getSurfaceSupportKHR(i, surf, &presentSupport);
      if (queueFamily.queueCount > 0 && presentSupport)
        ret.presentFamily = i;
      if (ret.isComplete())
        break;
      i++;
    }
    return ret;
  }
  
  /**
   * @brief Finds the memory type index.
   * @param memoryProperties - the memory properties to search.
   * @param typeBits - the type bits to search for.
   * @param requirementsMask - the requirements mask.
   * @return the memory type index. If no memory type index is found, then ~0 (-1) is returned.
   */
  uint32_t findMemoryType(const vk::PhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeBits, vk::MemoryPropertyFlags requirementsMask) const {
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
      if ((typeBits & 1) == 1) {
        if ((memoryProperties.memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask) {
          return i;
        }
      }
      typeBits >>= 1;
    }
    return uint32_t(~0);
  }
  
  /**
   * @brief Checks if the device is suitable for graphics output
   * @param dev - the device to check
   * @return true if the device is suitable, false otherwise
   */
  bool isDeviceSuitable(const vk::PhysicalDevice& dev, const vk::SurfaceKHR& surf) const {
    auto deviceProperties = dev.getProperties();
    auto deviceFeatures = dev.getFeatures();
    if (deviceProperties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu) return false;
    if (!deviceFeatures.geometryShader) return false;
    if (!checkDeviceExtensionSupport(dev)) return false;
    auto scs = querySwapChainSupport(dev, surf);
    if (scs.formats.empty() || scs.presentModes.empty()) return false;
    auto indicies = findQueueFamilies(dev, surf);
    return indicies.isComplete();
  }

  /**
   * @brief Checks for required extensions.
   */
  bool checkDeviceExtensionSupport(const vk::PhysicalDevice& dev) const {
    // check if the device supports the required extensions
    auto availableExtensions = dev.enumerateDeviceExtensionProperties();
    for (const auto& requiredExtension : requiredDeviceExtensions) {
      auto result = std::find_if(availableExtensions.begin(), availableExtensions.end(),
                                 [&requiredExtension](const vk::ExtensionProperties& extension) {
                                   return strcmp(extension.extensionName, requiredExtension) == 0;
                                 });
      if (result == availableExtensions.end())
        return false;
    }
    return true;
  }

  SwapChainSupportDetails querySwapChainSupport(const vk::PhysicalDevice& dev, const vk::SurfaceKHR& surf) const {
    SwapChainSupportDetails details;
    details.capabilities = dev.getSurfaceCapabilitiesKHR(surf);
    details.formats = dev.getSurfaceFormatsKHR(surf);
    details.presentModes = dev.getSurfacePresentModesKHR(surf);
    return details;
  }
  
  vk::Extent2D getSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) const {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
      return capabilities.currentExtent;
    else {
      vk::Extent2D actualExtent = { size.x, size.y };
      actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
      actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
      return actualExtent;
    }
  }
  
  bool resize(Vec2<uint32_t> newSize) {
    if (newSize.x == 0 || newSize.y == 0) return false;
    size = newSize;
    return initGPU();
  }
  
  
  
  
  
  
  void beginFrame() {
    // start recording commands to commandBuffers
    commandBuffers = device.allocateCommandBuffers(vk::CommandBufferAllocateInfo{
      .commandPool = commandPool,
      .level = vk::CommandBufferLevel::ePrimary,
      .commandBufferCount = 1
    });
    commandBuffers[0].begin(vk::CommandBufferBeginInfo{
      .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit
    });
    // begin render pass
  }

  void endFrame() {

  }

  void draw() {

  }
  
};




RendererVulkan::RendererVulkan(const ApplicationInfo& applicationInfo, Window* window)
  : RendererBackend(applicationInfo, window) {
  pImpl = std::make_unique<Impl>(applicationInfo, window);
}


bool RendererVulkan::init() {
  if (!pImpl->initGPU())
    return false;
  return pImpl->initDeviceResources();
}


void RendererVulkan::shutdown() {
//  pImpl->shutdown(); // TODO
//  pImpl->destroyDeviceResources();
}

RendererVulkan::~RendererVulkan() {
  shutdown();
}

void RendererVulkan::beginFrame() {
  pImpl->beginFrame();
}

void RendererVulkan::endFrame() {
  pImpl->endFrame();
}

void RendererVulkan::draw() {
  pImpl->draw();
}


vk::Instance RendererVulkan::getInstance() const {
  return pImpl->instance;
}

} // ams
