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

/*[export module ams.game.internal.IRendererImpl]*/
/*[exclude begin]*/
#pragma once
#include "ams/game/Object.hpp"
#include "ams/game/ApplicationInfo.hpp"
/*[exclude end]*/
/*[import ams.game.Object]*/
/*[import ams.game.ApplicationInfo]*/

/*[export]*/ namespace ams {
class Window;

/**
 * @brief When true, Vulkan can be used as a rendering backend.
 */
constexpr bool AMSVulkanAvailable =
#ifndef AMS_REQUIRE_OPENGL
  true;
#else
  false;
#endif
} // namespace ams

constexpr bool AMSGraphicsDebug =
#ifdef AMS_GRAPHICS_DEBUG
  true;
#else
  false;
#endif

/*[export]*/ namespace ams::internal {

class RendererBackend : public Object {
protected:
  ApplicationInfo applicationInfo;
  Window* window;
public:
  RendererBackend(const ApplicationInfo& applicationInfo, Window* window)
  : Object(), applicationInfo(applicationInfo), window(window) {}
  
  virtual ~RendererBackend() = default;
  virtual bool init() { return true; }
  virtual void shutdown() {}
  virtual void beginFrame() {}
  virtual void endFrame() {}
  virtual void draw() {}
};

} // ams::internal
