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

/*[export module ams.game.MouseButton]*/

/*[export]*/ namespace ams {

/**
 * @brief Mouse buttons. This is a wrapper for GLFW mouse buttons.
 */
enum class AMS_GAME_EXPORT MouseButton {
  Left = 0,
  Right = 1,
  Middle = 2,
  Button4 = 3,
  Button5 = 4,
  Button6 = 5,
  Button7 = 6,
  Button8 = 7,
  Last = Button8,
  LeftButton = Left,
  RightButton = Right,
  MiddleButton = Middle
};

/**
 * @brief Convert a GLFW mouse button int to a MouseButton enum.
 */
inline MouseButton AMS_GAME_EXPORT toMouseButton(int glfwMouseButton) {
  switch (glfwMouseButton) {
    case 0:
      return MouseButton::Left;
    case 1:
      return MouseButton::Right;
    case 2:
      return MouseButton::Middle;
    case 3:
      return MouseButton::Button4;
    case 4:
      return MouseButton::Button5;
    case 5:
      return MouseButton::Button6;
    case 6:
      return MouseButton::Button7;
    case 7:
      return MouseButton::Button8;
    default:
      return MouseButton::Last;
  }
}

/**
 * @brief A Mouse action. This is a wrapper for GLFW mouse actions.
 */
enum class AMS_GAME_EXPORT MouseAction {
  Press = 0,
  Release = 1,
  Repeat = 2
};

/**
 * @brief Convert a GLFW mouse action int to a MouseAction enum.
 */
inline MouseAction AMS_GAME_EXPORT toMouseAction(int glfwMouseAction) {
  switch (glfwMouseAction) {
    case 0:
      return MouseAction::Press;
    case 1:
      return MouseAction::Release;
    case 2:
      return MouseAction::Repeat;
    default:
      return MouseAction::Press;
  }
}

struct AMS_GAME_EXPORT MousePress {
  /**
   * @brief The mouse button that was pressed.
   */
  MouseButton button;
  /**
   * @brief The action that was performed.
   */
  MouseAction action;
  /**
   * @brief The modifier keys that were pressed as a bitfield. See ams::KeyModifier.
   */
  int mods;
};

} // ams
