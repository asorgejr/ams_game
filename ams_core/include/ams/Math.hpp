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
/*[exclude begin]*/
#pragma once

#include "config.hpp"
/*[exclude end]*/
/*[export module ams.Math]*/
#include <cmath>
#include <type_traits>
#include <algorithm>
#include <stdexcept>
#include <gcem.hpp>
/*[import ams.config]*/

/**
 * @brief ams.Math - A fully constexpr math library.
 */
/*[export]*/ namespace ams {

template<typename TNum>
concept NumericT = std::is_arithmetic_v<TNum>;

template<typename TNum>
concept IntegralT = std::is_integral_v<TNum>;

template<typename TNum>
concept DecimalT = std::is_floating_point_v<TNum>;

/**
 * @brief Pi constant
 */
constexpr double PI = 3.14159265358979323846;
/**
 * @brief E constant
 */
constexpr double E = 2.71828182845904523536;
/**
 * @brief Tau constant
 */
constexpr double TAU = 6.28318530717958647692;
/**
 * @brief Golden ratio constant
 */
constexpr double PHI = 1.61803398874989484820;
/**
 * @brief Square root of 2 constant
 */
constexpr double SQRT2 = 1.41421356237309504880;
/**
 * @brief Square root of 3 constant
 */
constexpr double SQRT3 = 1.73205080756887729352;
/**
 * @brief Float epsilon
 */
constexpr float EPSILON_F = 1.19209290e-07f;
/**
 * @brief Double epsilon
 */
constexpr double EPSILON_D = 2.2204460492503131e-16;

namespace internal {
/**
 * @brief determines how to handle division by zero
 */
template<NumericT TNum>
constexpr TNum divbyzero() {
  if constexpr (AMSExceptions)
    throw std::domain_error("Division by zero");
  else
    return std::numeric_limits<TNum>::quiet_NaN();
}
}

/**
 * @brief Returns the absolute value of the given number.
 * @tparam TNum - any numeric type
 * @param num The number to get the absolute value of.
 * @return The absolute value of the given number.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum abs(TNum num) noexcept {
  return num < 0 ? -num : num;
}

/**
 * @brief Returns the sign of the given number.
 * @tparam TNum - any numeric type
 * @param num The number to get the sign of.
 * @return The sign of the given number, -1 if negative, 1 if positive, 0 if 0.
 */
template<NumericT TNum>
[[nodiscard]] constexpr int sign(TNum num) noexcept {
  if constexpr (std::is_floating_point_v<TNum>)
    return num < 0 ? -1 : num > 0 ? 1 : 0;
  else // branchless version for integers
    return (num > 0) - (num < 0);
}

/**
 * @brief floors the given number.
 * @tparam TNum - any numeric type
 * @param num The number to floor.
 * @return The floored number.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum floor(TNum num) noexcept {
  if (std::is_constant_evaluated())
    return static_cast<TNum>(gcem::floor<TNum>(num));
  else
    return static_cast<TNum>(std::floor(num));
}

/**
 * @brief Ceils the given number.
 * @tparam TNum - any numeric type
 * @param num The number to ceil.
 * @return The ceiled number.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum ceil(TNum num) noexcept {
  if (std::is_constant_evaluated())
    return gcem::ceil<TNum>(num);
  else
    return std::ceil<TNum>(num);
}

/**
 * @brief Rounds the given number.
 * @tparam TNum - any numeric type
 * @param num The number to round.
 * @return The rounded number.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum round(TNum num) noexcept {
  if (std::is_constant_evaluated())
    return gcem::round<TNum>(num);
  else
    return std::round<TNum>(num);
}

/**
 * @brief Truncates the given number.
 * @tparam TNum - any numeric type
 * @param num The number to truncate.
 * @return The truncated number.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum trunc(TNum num) noexcept {
  if (std::is_constant_evaluated())
    return gcem::trunc<TNum>(num);
  else
    return std::trunc<TNum>(num);
}

/**
 * @brief Returns the maximum of the two given numbers.
 * @tparam TNum1 - any numeric type
 * @tparam TNum2 - any numeric type
 * @param a The first number.
 * @param b The second number.
 * @return The maximum of the two given numbers.
 */
template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto max(TNum1 a, TNum2 b) noexcept {
  if (std::is_constant_evaluated())
    return gcem::max<TNum1, TNum2>(a, b);
  else
    return std::max<TNum1>(a, b);
}

/**
 * @brief Returns the minimum of the two given numbers.
 * @tparam TNum1 - any numeric type
 * @tparam TNum2 - any numeric type
 * @param a The first number.
 * @param b The second number.
 * @return The minimum of the two given numbers.
 */
template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto min(TNum1 a, TNum2 b) noexcept {
  if (std::is_constant_evaluated())
    return gcem::min<TNum1, TNum2>(a, b);
  else
    return std::min<TNum1>(a, b);
}

/**
 * @brief Returns whether the given number is odd.
 * @tparam TNum - any integral type
 * @param num The number to check.
 * @return Whether the given number is odd.
 */
template<IntegralT TNum>
[[nodiscard]] constexpr bool is_odd(TNum num) noexcept {
  return num % 2 != 0;
}

/**
 * @brief Returns whether the given number is even.
 * @tparam TNum - any integral type
 * @param num The number to check.
 * @return Whether the given number is even.
 */
template<IntegralT TNum>
[[nodiscard]] constexpr bool is_even(TNum num) noexcept {
  return num % 2 == 0;
}

/**
 * @brief integral modulo function that works with negative numbers
 * @tparam TNum - any numeric type
 * @param a - the dividend
 * @param b - the divisor
 * @return the remainder of a/b
 */
template<IntegralT TNum>
[[nodiscard]] constexpr TNum mod(TNum a, TNum b) {
  if (b == 0) {
    return internal::divbyzero<TNum>();
  }
  return (a % b + b) % b;
}

/**
 * @brief floating point modulo function that works with negative numbers
 * @tparam TNum - any numeric type
 * @param a - the dividend
 * @param b - the divisor
 * @return the remainder of a/b
 */
template<DecimalT TNum>
[[nodiscard]] constexpr TNum mod(TNum a, TNum b) {
  if (b == 0) {
    return internal::divbyzero<TNum>();
  }
  // https://stackoverflow.com/a/4633177
  return a - b * ams::floor<TNum>(a / b);
  // return std::fmod(std::fmod(a, b) + b, b);
}


/**
 * @brief the fractional part of a floating point number
 * @tparam TNum - any floating point type
 * @param val - value to get fractional part of
 * @return fractional part of val
 */
template<DecimalT TNum>
[[nodiscard]] constexpr TNum frac(TNum val) {
  return abs<TNum>(mod<TNum>(val, 1.0));
}

/**
 * @brief the fractional part of a floating point number
 * @tparam TNum - any numeric type
 * @param val - value to get fractional part of
 * @return fractional part of val
 */
template<IntegralT TNum>
[[nodiscard]] constexpr TNum frac(TNum val) {
  return 0;
}

/**
 * @brief square root function.
 * @tparam TNum - any floating point type
 * @param val - value to get square root of
 * @return square root of val
 */
template<NumericT TNum>
[[nodiscard]]
constexpr TNum sqrt(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::sqrt<TNum>(val);
  else
    return std::sqrt(val);
}


/**
 * @brief invert square root function.
 * @tparam TNum - any floating point type
 * @param val - value to get invert square root of
 * @return invert square root of val
 */
template<NumericT TNum>
[[nodiscard]]
constexpr TNum inv_sqrt(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::inv_sqrt<TNum>(val);
  else
    return 1.0 / std::sqrt<TNum>(val);
}


/**
 * @brief consteval logarithm of a number with a given base
 * @tparam TNum - any floating point type
 * @param val - value to get logarithm of
 * @return logarithm of val
 */
template<NumericT TNum, NumericT TNum2>
[[nodiscard]] constexpr TNum log(TNum val, TNum2 base) {
  if (val == 0) {
    return divbyzero<TNum2>();
  }
  if (std::is_constant_evaluated())
    return gcem::log<TNum>(val) / gcem::log<TNum2>(base);
  else
    return std::log<TNum>(val) / std::log<TNum2>(base);
}

/**
 * @brief the exponential function
 * @tparam TNum - any floating point type
 * @param val - value to get exponential of
 * @return exponential of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum exp(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::exp<TNum>(val);
  else
    return std::exp<TNum>(val);
}

/**
 * @brief the power function
 * @tparam TNum1 - any floating point type
 * @tparam TNum2 - any floating point type
 * @param base - base of the power
 * @param exp - exponent of the power
 * @return base to the power of exp
 */
template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr TNum1 pow(TNum1 base, TNum2 exp) {
  if (std::is_constant_evaluated())
    return gcem::pow<TNum1, TNum2>(base, exp);
  else
    return std::pow<TNum1, TNum2>(base, exp);
}

#pragma region Trigonometry

template<NumericT TNum>
[[nodiscard]] constexpr TNum radians(TNum degrees) {
  return degrees * PI / 180;
}

template<NumericT TNum>
[[nodiscard]] constexpr TNum degrees(TNum radians) {
  return radians * 180 / PI;
}

/**
 * @brief hypotenuse function.
 * @tparam TNum1 - any floating point type
 * @tparam TNum2 - any floating point type
 * @param a - first side
 * @param b - second side
 * @return hypotenuse of a and b
 */
template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto hypot(TNum1 a, TNum2 b) {
  if (std::is_constant_evaluated())
    return gcem::hypot<TNum1, TNum2>(a, b);
  else
    return std::hypot<TNum1, TNum2>(a, b);
}

/**
 * @brief invert hypotenuse function.
 * @tparam TNum1 - any floating point type
 * @tparam TNum2 - any floating point type
 * @param a - first side
 * @param b - second side
 * @return invert hypotenuse of a and b
 */
template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto inv_hypot(TNum1 a, TNum2 b) {
  if (std::is_constant_evaluated())
    return 1.0 / gcem::hypot<TNum1, TNum2>(a, b);
  else
    return 1.0 / std::hypot<TNum1, TNum2>(a, b);
}

/**
 * @brief the sine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get sine of
 * @return sine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum sin(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::sin<TNum>(val);
  else
    return std::sin(val);
}

/**
 * @brief the cosine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get cosine of
 * @return cosine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum cos(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::cos<TNum>(val);
  else
    return std::cos(val);
}

/**
 * @brief the tangent of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get tangent of
 * @return tangent of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum tan(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::tan<TNum>(val);
  else
    return std::tan(val);
}

/**
 * @brief the arcsine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get arcsine of
 * @return arcsine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum asin(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::asin<TNum>(val);
  else
    return std::asin(val);
}

/**
 * @brief the arccosine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get arccosine of
 * @return arccosine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum acos(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::acos<TNum>(val);
  else
    return std::acos(val);
}

/**
 * @brief the arctangent of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get arctangent of
 * @return arctangent of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum atan(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::atan<TNum>(val);
  else
    return std::atan(val);
}

/**
 * @brief the arctangent of an angle
 * @tparam TNum - any floating point type
 * @param y - the y value
 * @param x - the x value
 * @return arctangent of y/x
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum atan2(TNum y, TNum x) {
  if (std::is_constant_evaluated())
    return gcem::atan2<TNum>(y, x);
  else
    return std::atan2(y, x);
}

/**
 * @brief the hyperbolic sine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic sine of
 * @return hyperbolic sine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum sinh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::sinh<TNum>(val);
  else
    return std::sinh(val);
}

/**
 * @brief the hyperbolic cosine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic cosine of
 * @return hyperbolic cosine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum cosh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::cosh<TNum>(val);
  else
    return std::cosh(val);
}

/**
 * @brief the hyperbolic tangent of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic tangent of
 * @return hyperbolic tangent of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum tanh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::tanh<TNum>(val);
  else
    return std::tanh(val);
}

/**
 * @brief the hyperbolic arcsine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic arcsine of
 * @return hyperbolic arcsine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum asinh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::asinh<TNum>(val);
  else
    return std::asinh(val);
}

/**
 * @brief the hyperbolic arccosine of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic arccosine of
 * @return hyperbolic arccosine of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum acosh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::acosh<TNum>(val);
  else
    return std::acosh(val);
}

/**
 * @brief the hyperbolic arctangent of an angle
 * @tparam TNum - any floating point type
 * @param val - value to get hyperbolic arctangent of
 * @return hyperbolic arctangent of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum atanh(TNum val) {
  if (std::is_constant_evaluated())
    return gcem::atanh<TNum>(val);
  else
    return std::atanh(val);
}

#pragma endregion Trigonometry


/**
 * @brief remaps a value from one range to another
 * @tparam TNum - any integral type
 * @param val - value to be remapped
 * @param imin - input range minimum
 * @param imax - input range maximum
 * @param omin - output range minimum
 * @param omax - output range maximum
 * @return value remapped from input range to output range
 */
template<IntegralT TNum>
[[nodiscard]] constexpr TNum remap(TNum val, TNum imin, TNum imax, TNum omin, TNum omax) {
  return TNum((val - imin) * double(omax - omin) / (imax - imin) + omin);
}


/**
 * @brief remaps a value from one range to another
 * @tparam TNum - any floating point type
 * @param val - value to be remapped
 * @param imin - input range minimum
 * @param imax - input range maximum
 * @param omin - output range minimum
 * @param omax - output range maximum
 * @return value remapped from input range to output range
 */
template<DecimalT TNum>
[[nodiscard]] constexpr TNum remap(TNum val, TNum imin, TNum imax, TNum omin, TNum omax) {
  return (val - imin) * (omax - omin) / (imax - imin) + omin;
}

/**
 * @brief clamps a value between a minimum and maximum value
 * @tparam TNum - any numeric type
 * @param val - value to be clamped
 * @param min - minimum value
 * @param max - maximum value
 * @return value clamped between min and max
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum clamp(TNum val, TNum min, TNum max) {
  return val < min ? min : val > max ? max : val;
}

/**
 * @brief wraps value around min and max
 * @tparam TNum - any numeric type
 * @param val - value to be wrapped
 * @param min - minimum value
 * @param max - maximum value
 * @return value wrapped between min and max
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum wrap(TNum val, TNum min, TNum max) {
  return val == max ? max : mod<TNum>(val - min, max - min) + min;
}


/**
 * @brief linear interpolation between two values
 * @tparam TNum - any numeric type
 * @param a - first value
 * @param b - second value
 * @param t - interpolation value
 * @return a + (b - a) * t
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum lerp(TNum a, TNum b, float t) {
  return a + (b - a) * t;
}

/**
 * @brief is a value within a range
 * 
 * @tparam TNum - any type which supports < and > operators
 * @param value - value to check
 * @param min - is value >= min
 * @param max - is value <= max
 * @return true - value is within range
 * @return false - value is not within range
 */
template<NumericT TNum>
[[nodiscard]] constexpr bool within(TNum value, TNum min, TNum max) {
  return (value >= min) && (value <= max);
}

/**
 * @brief is a value nearly zero
 * @tparam TNum - any floating point type
 * @param value - value to check
 * @param epsilon - epsilon value
 * @return true - value is nearly zero
 * @return false - value is not nearly zero
 */
template<DecimalT TNum>
[[nodiscard]] constexpr bool is_naught(TNum value, TNum epsilon = std::numeric_limits<TNum>::epsilon()) {
  return abs(value) < epsilon;
}

/**
 * @brief is a value nearly equal to another value
 * @tparam TNum - any floating point type
 * @param a - first value
 * @param b - second value
 * @param epsilon - epsilon value
 * @return true - values are nearly equal
 * @return false - values are not nearly equal
 */
template<DecimalT TNum>
[[nodiscard]] constexpr bool is_equal(TNum a, TNum b, TNum epsilon = std::numeric_limits<TNum>::epsilon()) {
  return abs(a - b) < epsilon;
}

template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto copysign(TNum1 x, TNum2 y) {
  // hand rolled copysign to avoid std::copysign
  return y < 0 ? -abs(x) : abs(x);
}

template<NumericT TNum1, NumericT TNum2>
[[nodiscard]] constexpr auto safe_div(TNum1 x, TNum2 y) {
  return y == 0 ? 0 : x / y;
}

}
