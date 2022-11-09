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

/*[export module ams.game.Key]*/

#include <set>

/*[export]*/ namespace ams {

/**
 * @brief Key is an enum class that contains all the keys that can be pressed.
 * @note This is a wrapper for GLFW's key codes.
 */
enum class AMS_GAME_EXPORT Key {
  Unknown = -1,
  Space = 32,
  Apostrophe = 39,
  Comma = 44,
  Minus = 45,
  Period = 46,
  Slash = 47,
  Num0 = 48,
  Num1 = 49,
  Num2 = 50,
  Num3 = 51,
  Num4 = 52,
  Num5 = 53,
  Num6 = 54,
  Num7 = 55,
  Num8 = 56,
  Num9 = 57,
  Semicolon = 59,
  Equal = 61,
  A = 65,
  B = 66,
  C = 67,
  D = 68,
  E = 69,
  F = 70,
  G = 71,
  H = 72,
  I = 73,
  J = 74,
  K = 75,
  L = 76,
  M = 77,
  N = 78,
  O = 79,
  P = 80,
  Q = 81,
  R = 82,
  S = 83,
  T = 84,
  U = 85,
  V = 86,
  W = 87,
  X = 88,
  Y = 89,
  Z = 90,
  LeftBracket = 91,
  Backslash = 92,
  RightBracket = 93,
  GraveAccent = 96,
  World1 = 161,
  World2 = 162,
  Escape = 256,
  Enter = 257,
  Tab = 258,
  Backspace = 259,
  Insert = 260,
  Delete = 261,
  Right = 262,
  Left = 263,
  Down = 264,
  Up = 265,
  PageUp = 266,
  PageDown = 267,
  Home = 268,
  End = 269,
  CapsLock = 280,
  ScrollLock = 281,
  NumLock = 282,
  PrintScreen = 283,
  Pause = 284,
  F1 = 290,
  F2 = 291,
  F3 = 292,
  F4 = 293,
  F5 = 294,
  F6 = 295,
  F7 = 296,
  F8 = 297,
  F9 = 298,
  F10 = 299,
  F11 = 300,
  F12 = 301,
  F13 = 302,
  F14 = 303,
  F15 = 304,
  F16 = 305,
  F17 = 306,
  F18 = 307,
  F19 = 308,
  F20 = 309,
  F21 = 310,
  F22 = 311,
  F23 = 312,
  F24 = 313,
  F25 = 314,
  KP0 = 320,
  KP1 = 321,
  KP2 = 322,
  KP3 = 323,
  KP4 = 324,
  KP5 = 325,
  KP6 = 326,
  KP7 = 327,
  KP8 = 328,
  KP9 = 329,
  KPDecimal = 330,
  KPDivide = 331,
  KPMultiply = 332,
  KPSubtract = 333,
  KPAdd = 334,
  KPEnter = 335,
  KPEqual = 336,
  LeftShift = 340,
  LeftControl = 341,
  LeftAlt = 342,
  LeftSuper = 343,
  RightShift = 344,
  RightControl = 345,
  RightAlt = 346,
  RightSuper = 347,
  Menu = 348
};

/**
 * @brief Key is an enum class that contains all the modifier keys that can be pressed.
 * @note This is a wrapper for GLFW's key codes.
 */
enum class AMS_GAME_EXPORT ModKey {
  Shift = 0x0001,
  Control = 0x0002,
  Alt = 0x0004,
  Super = 0x0008,
  CapsLock = 0x0010,
  NumLock = 0x0020
};

/**
 * @brief Converts an integer to a Key.
 * @param key The integer to convert.
 * @return The Key.
 */
inline Key AMS_GAME_EXPORT glfwToKey(int key) noexcept {
  return static_cast<Key>(key);
}

/**
 * @brief Converts an integer bitfield to a set of ModKey.
 * @param mod The integer to convert.
 * @return The set of ModKey.
 */
inline std::set<ModKey> AMS_GAME_EXPORT toModKeySet(int mod) noexcept {
  std::set<ModKey> mods;
  if (mod & static_cast<int>(ModKey::Shift)) {
    mods.insert(ModKey::Shift);
  }
  if (mod & static_cast<int>(ModKey::Control)) {
    mods.insert(ModKey::Control);
  }
  if (mod & static_cast<int>(ModKey::Alt)) {
    mods.insert(ModKey::Alt);
  }
  if (mod & static_cast<int>(ModKey::Super)) {
    mods.insert(ModKey::Super);
  }
  if (mod & static_cast<int>(ModKey::CapsLock)) {
    mods.insert(ModKey::CapsLock);
  }
  if (mod & static_cast<int>(ModKey::NumLock)) {
    mods.insert(ModKey::NumLock);
  }
  return mods;
}

/**
 * @brief KeyPress stores the key and the modifier keys that are pressed.
 */
struct AMS_GAME_EXPORT KeyPress {
  /**
   * @brief The key that is pressed.
   */
  Key key;
  /**
   * @brief The modifier keys that are pressed as a bitfield. See ModKey.
   */
  int mods;
};

} // ams
