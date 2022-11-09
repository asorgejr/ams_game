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
#include "ams/game/Display.hpp"
#include "ams/game/Application.hpp"
#else
import ams.game.Display;
import ams.game.Application;
#endif

#include <GLFW/glfw3.h>


namespace ams {

Display::Display(GLFWmonitor* monitor)
: Object(),
  _monitor(monitor)
{
  if (glfwInit() == GLFW_FALSE) {
    if constexpr (AMSExceptions) {
      throw std::runtime_error("Failed to initialize GLFW");
    }
  }
  if (monitor == nullptr) {
    if constexpr (AMSExceptions)
      throw NullPointerException("Invalid monitor");
    else
      return;
  }
  _mode = glfwGetVideoMode(_monitor);
  name = glfwGetMonitorName(_monitor);
  _size = { _mode->width, _mode->height };
  glfwGetMonitorPos(_monitor, &_position.x, &_position.y);
  
  // get display supported resolutions
  int count;
  auto modes = glfwGetVideoModes(_monitor, &count);
  for (int i = 0; i < count; i++) {
    _resolutions.push_back({ modes[i].width, modes[i].height });
  }
}

Vec2<int> Display::getSize() const {
  return _size;
}

Vec2<int> Display::getPosition() const {
  return _position;
}

int Display::getRefreshRate() const {
  return _mode->refreshRate;
}

Vec3<int> Display::getBitDepth() const {
  return {_mode->redBits, _mode->greenBits, _mode->blueBits};
}

const std::string& Display::getName() const {
  return name;
}

const uuid_t& Display::getId() const {
  return id;
}

GLFWmonitor* Display::getHandle() const {
  return _monitor;
}

std::vector<Display> Display::getDisplays() {
  if (glfwInit() == GLFW_FALSE) {
    if constexpr (AMSExceptions) {
      throw std::runtime_error("Failed to initialize GLFW");
    }
  }
  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);
  std::vector<Display> displays;
  for (int i = 0; i < count; i++) {
    if (monitors[i] == nullptr)
      continue;
    displays.emplace_back(monitors[i]);
  }
  return displays;
}

const std::vector<Vec2<int>>& Display::getSupportedResolutions() const {
  return _resolutions;
}

} // ams
