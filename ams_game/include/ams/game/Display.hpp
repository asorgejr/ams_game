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
/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[exclude begin]*/
#include <ams/spatial/Vec/Vec2.hpp>
#include <ams/spatial/Vec/Vec3.hpp>
#include "Object.hpp"
/*[exclude end]*/

/*[export module ams.game.Display]*/

#include <memory>
/*[import ams.spatial.Vec2]*/
/*[import ams.spatial.Vec3]*/
/*[import ams.game.Object]*/

typedef struct GLFWmonitor GLFWmonitor;
typedef struct GLFWvidmode GLFWvidmode;

/*[export]*/ namespace ams {

class Application;

/**
 * @brief Display keeps track of the display size and information.
 */
class AMS_GAME_EXPORT Display final : private Object {
private:
  GLFWmonitor* _monitor = nullptr;
  const GLFWvidmode* _mode = nullptr;
  Vec2<int> _size{};
  Vec2<int> _position{};
  std::vector<Vec2<int>> _resolutions{};

public:
  Display(GLFWmonitor* monitor);

  ~Display() = default;

  /**
   * @brief Get the size of the display.
   */
  Vec2<int> getSize() const;

  /**
   * @brief Get the position of the display.
   */
  Vec2<int> getPosition() const;

  /**
   * @brief Get the refresh rate of the display.
   */
  int getRefreshRate() const;

  /**
   * @brief Get the bit depth of the display as RGB.
   */
  Vec3<int> getBitDepth() const;

  const std::string& getName() const;

  const uuid_t& getId() const;

  /**
   * @brief Get all supported resolutions for the display.
   */
  const std::vector<Vec2<int>>& getSupportedResolutions() const;
  
  /**
   * @brief Get the raw GLFW monitor. Use this with caution.
   */
  GLFWmonitor* getHandle() const;

  /**
   * @brief Gets all the displays connected to the system.
   * @details The first display at index 0 is the primary display.
   */
  static std::vector<Display> getDisplays();
};

} // ams
