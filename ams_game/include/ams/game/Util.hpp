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
#include <nameof.hpp>
/*[ignore end]*/

/*[export module ams.game.Util]*/
#include <chrono>
#include <format>
#include <source_location>
/*[exclude begin]*/
#include <ams/Math.hpp>
#include "config.hpp"
#include "Logger.hpp"
/*[exclude end]*/
/*[import ams.Math]*/
/*[import ams.game.config]*/
/*[import ams.game.Log]*/

// chrono literals
/*[export]*/ using namespace std::chrono_literals;

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
  return duration_cast<T>(tu1s * step);
}

/**
 * @brief Converts a duration to a frame-per-second value.
 * @tparam T - The duration type.
 * @param unit - The duration value i.e. (1/60) as a std::chrono duration type.
 * @return The frame-per-second value i.e. 60.
 */
template<TDuration T>
[[nodiscard]] float unitToFps(T unit) {
  constexpr auto tusize = double_t(duration_cast<T>(1s).count()); // 1 second in T units as number
  return safe_div(tusize, unit.count());
}

namespace internal {
template<typename T>
concept TExcception = std::is_base_of_v<std::exception, T>;
template<typename T>
concept TDefaultConstructible = std::is_default_constructible_v<T> || std::is_void_v<T>;
}


/**
 * @brief If AMSExceptions is enabled, throws an exception, otherwise returns a default constructed value.
 * @tparam TEx - The exception type.
 * @tparam TDefault - The default value type.
 * @param errmsg - The error message.
 * @return The default value if exceptions are disabled, otherwise throws an exception.
 */
template<internal::TExcception TEx, internal::TDefaultConstructible TDefault>
TDefault throwOrDefault(const std::string& errmsg, TDefault def = TDefault(),
                        const std::source_location& loc = std::source_location::current()) {
  Logger::log(errmsg, LogLevel::Error, loc);
  if constexpr (AMSExceptions) {
    throw TEx(errmsg.c_str());
  } else {
    return def;
  }
}

/**
 * @brief If AMSExceptions is enabled, throws an exception, otherwise returns a default constructed value.
 * @tparam TEx - The exception type.
 * @param errmsg - The error message.
 * @return The default value if exceptions are disabled, otherwise throws an exception.
 */
template<internal::TExcception TEx>
void throwOrDefault(const std::string& errmsg, const std::source_location& loc = std::source_location::current()) {
  Logger::log(errmsg, LogLevel::Error, loc);
  if constexpr (AMSExceptions) {
    throw TEx(errmsg.c_str());
  }
}

} // ams
