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
/*[ignore end]*/

/*[export module ams.game.internal.RendererVulkan]*/
/*[exclude begin]*/
#include "RendererBackend.hpp"
/*[exclude end]*/

/*[import ams.game.internal.RendererBackend]*/

/*[export]*/ namespace vk {
class Instance;
}

/*[export]*/ namespace ams::internal {

class AMS_GAME_EXPORT RendererVulkan : public RendererBackend {
private:
  struct AMS_GAME_EXPORT Impl;
  std::unique_ptr<Impl> pImpl;
  // vulkan sync objects
  size_t _currentFrame = 0;
  bool _framebufferResized = false;
  bool _isInitialized = false;
  
public:
  explicit RendererVulkan(const ApplicationInfo& appInfo, Window* window);
  ~RendererVulkan() override;
  
  /**
   * @brief Initialize vulkan renderer
   * @return true if successful
   */
  bool init() override;

  /**
   * @brief Handles shutdown of the renderer.
   */
  void shutdown() override;

  /**
   * @brief Begin rendering a frame.
   */
  void beginFrame() override;

  /**
   * @brief End rendering a frame.
   */
  void endFrame() override;

  /**
   * @brief Begin drawing a command buffer.
   */
  void draw() override;
  
  /**
   * @brief Get the vulkan instance
   * @return vulkan instance
   */
  [[nodiscard]] vk::Instance getInstance() const;
  
  
  
private:

};

} // ams

#endif // AMS_REQUIRE_OPENGL