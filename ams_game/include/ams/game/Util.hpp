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

/*[export module ams.game.Util]*/
/*[exclude begin]*/
#pragma once
#include <ams/Math.hpp>
/*[exclude end]*/
#include <chrono>
/*[import ams.Math]*/

// chrono literals
using namespace std::chrono_literals;

/*[export]*/ namespace ams {

template<typename T>
concept TDuration =
  std::is_convertible_v<T, std::chrono::duration<float>> && requires(T t) {
    { t.count() } -> std::convertible_to<float>;
};

/**
 * @brief Converts a frame-per-second value to a duration.
 * @tparam T - The duration type.
 * @param fps - The frame-per-second value i.e. 60.
 * @return The duration value i.e. (1/60) in std::chrono::milliseconds.
 */
template<TDuration T>
[[nodiscard]] T fpsToUnit(float fps) {
  constexpr auto tu1s = duration_cast<T>(1s); // 1 second in T units
  auto step = safe_div(1.0f, fps);
  return duration_cast<time_unit>(tu1s * step);
}

/**
 * @brief Converts a duration to a frame-per-second value.
 * @tparam T - The duration type.
 * @param unit - The duration value i.e. (1/60) in std::chrono::milliseconds.
 * @return The frame-per-second value i.e. 60.
 */
template<TDuration T>
[[nodiscard]] float unitToFps(T unit) {
  constexpr auto tusize = duration_cast<T>(1s).count(); // 1 second in T units as number
  return safe_div(tusize, unit.count());
}

} // ams
