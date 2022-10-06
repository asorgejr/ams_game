//
// Created by asorgejr on 9/25/2022.
//
export module ams.Math;

import <cmath>;
import <type_traits>;

export namespace ams {

template<typename TNum>
concept NumericT = std::is_arithmetic_v<TNum>;

template<typename TNum>
concept IntegralT = std::is_integral_v<TNum>;

template<typename TNum>
concept DecimalT = std::is_floating_point_v<TNum>;


/**
 * @brief Returns the absolute value of the given number.
 * @tparam TNum - any numeric type
 * @param num The number to get the absolute value of.
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum abs(TNum num) noexcept {
  return num < 0 ? -num : num;
}

/**
 * @brief integral modulo function that works with negative numbers
 * @tparam TNum - any numeric type
 * @param a - the dividend
 * @param b - the divisor
 */
template<IntegralT TNum>
[[nodiscard]] constexpr TNum mod(TNum a, TNum b) {
    return (a % b + b) % b;
}

/**
 * @brief floating point modulo function that works with negative numbers
 * @tparam TNum - any numeric type
 * @param a - the dividend
 * @param b - the divisor
 */
template<DecimalT TNum>
[[nodiscard]] constexpr TNum mod(TNum a, TNum b) {
    return std::fmod(std::fmod(a, b) + b, b);
}


/**
 * @brief the fractional part of a floating point number
 * @tparam TNum - any floating point type
 * @param val - value to get fractional part of
 * @return fractional part of val
 */
template<NumericT TNum>
[[nodiscard]] constexpr TNum frac(TNum val) {
  return abs<TNum>(mod<long double>(val, 1.0));
}

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

}
