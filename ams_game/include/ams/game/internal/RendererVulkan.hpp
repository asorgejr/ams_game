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

/*[module]*/
/*[exclude begin]*/
#pragma once
/*[exclude end]*/

#ifndef AMS_REQUIRE_OPENGL

/*[ignore begin]*/
#include "ams_game_export.hpp"
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VULKAN_HPP_STORAGE_SHARED 1
#define VULKAN_HPP_STORAGE_SHARED_EXPORT AMS_GAME_EXPORT
#include <vulkan/vulkan_raii.hpp>
/*[ignore end]*/

/*[export module ams.game.internal.RendererVulkan]*/
/*[exclude begin]*/
#include "RendererBackend.hpp"
/*[exclude end]*/

/*[import ams.game.internal.RendererBackend]*/

/*[export]*/ namespace ams::internal {

class AMS_GAME_EXPORT RendererVulkan : public RendererBackend {
private:
  // vulkan instance
  vk::Instance _instance;
  // vulkan physical devices
  std::vector<vk::PhysicalDevice> _physicalDevices;
  // vulkan logical device
  vk::Device _device;
  // vulkan surface
  vk::SurfaceKHR _surface;
  // vulkan queue family index
  uint32_t _queueFamilyIndex = 0;
  // vulkan queue
  vk::Queue _queue;
  // vulkan swapchain
  vk::SwapchainKHR _swapchain;
  // vulkan swapchain images
  std::vector<vk::Image> _swapchainImages;
  // vulkan swapchain image views
  std::vector<vk::ImageView> _swapchainImageViews;
  // vulkan render pass
  vk::RenderPass _renderPass;
  // vulkan command pool
  vk::CommandPool _commandPool;
  // vulkan command buffers
  std::vector<vk::CommandBuffer> _commandBuffers;
  // vulkan framebuffers
  std::vector<vk::Framebuffer> _framebuffers;
  // vulkan semaphores
  vk::Semaphore _imageAvailableSemaphore;
  vk::Semaphore _renderFinishedSemaphore;
  // vulkan fences
  std::vector<vk::Fence> _inFlightFences;
  std::vector<vk::Fence> _imagesInFlight;
  // vulkan sync objects
  size_t _currentFrame = 0;
  
  bool _framebufferResized = false;
public:
  explicit RendererVulkan(const ApplicationInfo& appInfo, Window* window);
  ~RendererVulkan() override;
  
  bool init() override;

  void shutdown() override;

  void beginFrame() override;

  void endFrame() override;

  void draw() override;

};

} // ams

#endif // AMS_REQUIRE_OPENGL