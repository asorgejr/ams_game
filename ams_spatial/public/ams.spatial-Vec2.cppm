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
module;
#include "ams/spatial/config.hpp"

export module ams.spatial:Vec2;

import ams;
import :config;


export namespace ams {

/**
 * 
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec2 {
  T x, y;

  constexpr Vec2() : x(0), y(0) {}
  
  // Implicit conversion from underlying type is allowed
  constexpr Vec2(T x) : x(x), y(x) {}

  constexpr Vec2(T x, T y) : x(x), y(y) {}

  constexpr Vec2(const Vec2& v) : x(v.x), y(v.y) {}

  template<Vec2T V2T> constexpr Vec2(const V2T& v) : x(v.x), y(v.y) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    if constexpr (AMSExceptions)
      if (i < 0 || i > 1) throw std::out_of_range("Vec2 subscript out of range");
    return (&x)[i];
  }
  
  // copy assignment operator
  constexpr Vec2<T>& operator=(const Vec2<T>& v) {
    x = v.x;
    y = v.y;
    return *this;
  }
  
  template<Vec2T V2T> Vec2<T>& operator=(const V2T& v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  // arithmetic operators
  constexpr Vec2<T> operator+(const Vec2<T>& v) const {
    return Vec2<T>(x + v.x, y + v.y);
  }

  constexpr Vec2<T> operator-(const Vec2<T>& v) const {
    return Vec2<T>(x - v.x, y - v.y);
  }

  constexpr Vec2<T> operator*(const Vec2<T>& v) const {
    return Vec2<T>(x * v.x, y * v.y);
  }

  constexpr Vec2<T> operator/(const Vec2<T>& v) const {
    return Vec2<T>(x / v.x, y / v.y);
  }

  constexpr Vec2<T> operator%(const Vec2<T>& v) const {
    return Vec2<T>(ams::mod(x, v.x), ams::mod(y, v.y));
  }

  template<Vec2T V2T> Vec2<T> operator+(const V2T& v) const {
    return Vec2<T>(x + v.x, y + v.y);
  }

  template<Vec2T V2T> Vec2<T> operator-(const V2T& v) const {
    return Vec2<T>(x - v.x, y - v.y);
  }

  template<Vec2T V2T> Vec2<T> operator*(const V2T& v) const {
    return Vec2<T>(x * v.x, y * v.y);
  }

  template<Vec2T V2T> Vec2<T> operator/(const V2T& v) const {
    return Vec2<T>(x / v.x, y / v.y);
  }

  template<Vec2T V2T> Vec2<T> operator%(const V2T& v) const {
    return Vec2<T>(mod<T>(x, v.x), mod<T>(y, v.y));
  }

  constexpr Vec2<T> operator+(const T& v) const {
    return Vec2<T>(x + v, y + v);
  }

  constexpr Vec2<T> operator-(const T& v) const {
    return Vec2<T>(x - v, y - v);
  }

  constexpr Vec2<T> operator*(const T& v) const {
    return Vec2<T>(x * v, y * v);
  }

  constexpr Vec2<T> operator/(const T& v) const {
    return Vec2<T>(x / v, y / v);
  }

  constexpr Vec2<T> operator%(const T& v) const {
    return Vec2<T>(mod<T>(x, v), mod<T>(y, v));
  }

  // compound assignment operators
  constexpr Vec2<T>& operator+=(const Vec2<T>& v) {
    return *this = *this + v;
  }

  constexpr Vec2<T>& operator-=(const Vec2<T>& v) {
    return *this = *this - v;
  }

  constexpr Vec2<T>& operator*=(const Vec2<T>& v) {
    return *this = *this * v;
  }

  constexpr Vec2<T>& operator/=(const Vec2<T>& v) {
    return *this = *this / v;
  }

  constexpr Vec2<T>& operator%=(const Vec2<T>& v) {
    return *this = *this % v;
  }

  template<Vec2T V2T> Vec2<T>& operator+=(const V2T& v) {
    return *this = *this + v;
  }

  template<Vec2T V2T> Vec2<T>& operator-=(const V2T& v) {
    return *this = *this - v;
  }

  template<Vec2T V2T> Vec2<T>& operator*=(const V2T& v) {
    return *this = *this * v;
  }

  template<Vec2T V2T> Vec2<T>& operator/=(const V2T& v) {
    return *this = *this / v;
  }

  template<Vec2T V2T> Vec2<T>& operator%=(const V2T& v) {
    return *this = *this % v;
  }

  constexpr Vec2<T>& operator+=(const T& v) {
    return *this = *this + v;
  }

  constexpr Vec2<T>& operator-=(const T& v) {
    return *this = *this - v;
  }

  constexpr Vec2<T>& operator*=(const T& v) {
    return *this = *this * v;
  }

  constexpr Vec2<T>& operator/=(const T& v) {
    return *this = *this / v;
  }

  constexpr Vec2<T>& operator%=(const T& v) {
    return *this = *this % v;
  }

  // urnary operators
  constexpr Vec2<T> operator-() const {
    return Vec2<T>(-x, -y);
  }

  constexpr Vec2<T> operator!() const {
    return Vec2<T>(!x, !y);
  }

  // lhs-rhs operators
  constexpr friend Vec2<T> operator+(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs + rhs.x, lhs + rhs.y);
  }

  constexpr friend Vec2<T> operator-(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs - rhs.x, lhs - rhs.y);
  }

  constexpr friend Vec2<T> operator*(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs * rhs.x, lhs * rhs.y);
  }

  constexpr friend Vec2<T> operator/(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs / rhs.x, lhs / rhs.y);
  }

  constexpr friend Vec2<T> operator%(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs % rhs.x, lhs % rhs.y);
  }

  // comparison operators
  template<Vec2T V2T> bool operator==(const V2T& other) const {
    return x == other.x && y == other.y;
  }

  template<Vec2T V2T> bool operator!=(const V2T& other) const {
    return !(*this == other);
  }

  template<Vec2T V2T> bool operator<(const V2T& other) const {
    return x < other.x && y < other.y;
  }

  template<Vec2T V2T> bool operator>(const V2T& other) const {
    return x > other.x && y > other.y;
  }

  template<Vec2T V2T> bool operator<=(const V2T& other) const {
    return x <= other.x && y <= other.y;
  }

  template<Vec2T V2T> bool operator>=(const V2T& other) const {
    return x >= other.x && y >= other.y;
  }

  constexpr static Vec2<decimal_t> zero() { return {0, 0}; }
  constexpr static Vec2<decimal_t> one() { return {1, 1}; }
  constexpr static Vec2<decimal_t> unit_x() { return {1, 0}; }
  constexpr static Vec2<decimal_t> unit_y() { return {0, 1}; }

#pragma region swizzle
#ifdef AMS_VEC_SWIZZLE_METHODS
  [[nodiscard]] constexpr Vec2<T> xx() const {
    return Vec2<T>(x, x);
  }

  [[nodiscard]] constexpr Vec2<T> xy() const {
    return Vec2<T>(x, y);
  }

  [[nodiscard]] constexpr Vec2<T> yx() const {
    return Vec2<T>(y, x);
  }

  [[nodiscard]] constexpr Vec2<T> yy() const {
    return Vec2<T>(y, y);
  }
#endif // AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle

};


} // ams
