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
#include <ams/Math.hpp>
#include "../internal/config.hpp"
#include "Vec2.hpp"
/*[exclude end]*/
/*[export module ams.spatial.Vec3]*/
#include <stdexcept>
/*[import ams]*/
/*[import ams.spatial.internal]*/
/*[import ams.spatial.Vec2]*/

/*[export]*/ namespace ams {

/**
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec3 {
  T x, y, z;

  constexpr Vec3() : x(0), y(0), z(0) {}

  constexpr explicit Vec3(T x) : x(x), y(x), z(x) {}

  constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

  constexpr Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

  constexpr explicit Vec3(const Vec2<T>& v) : x(v.x), y(v.y), z(0) {}

  template<Vec3T V3T> constexpr explicit Vec3(const V3T& v) : x(v.x), y(v.y), z(v.z) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    if constexpr (AMSExceptions)
      if (i < 0 || i > 2) throw std::out_of_range("Vec3 subscript out of range");
    return (&x)[i];
  }

  // copy assignment operator
  template<Vec3T V3T> Vec3<T>& operator=(const V3T& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  // arithmetic operators
  constexpr Vec3<T> operator+(const Vec3<T>& v) const {
    return Vec3<T>(x + v.x, y + v.y, z + v.z);
  }

  constexpr Vec3<T> operator-(const Vec3<T>& v) const {
    return Vec3<T>(x - v.x, y - v.y, z - v.z);
  }

  constexpr Vec3<T> operator*(const Vec3<T>& v) const {
    return Vec3<T>(x * v.x, y * v.y, z * v.z);
  }

  constexpr Vec3<T> operator/(const Vec3<T>& v) const {
    return Vec3<T>(x / v.x, y / v.y, z / v.z);
  }

  constexpr Vec3<T> operator%(const Vec3<T>& v) const {
    return Vec3<T>(x % v.x, y % v.y, z % v.z);
  }

  template<Vec3T V3T> Vec3<T> operator+(const V3T& other) const {
    return Vec3<T>(x + other.x, y + other.y, z + other.z);
  }

  template<Vec3T V3T> Vec3<T> operator-(const V3T& other) const {
    return Vec3<T>(x - other.x, y - other.y, z - other.z);
  }

  template<Vec3T V3T> Vec3<T> operator*(const V3T& other) const {
    return Vec3<T>(x * other.x, y * other.y, z * other.z);
  }

  template<Vec3T V3T> Vec3<T> operator/(const V3T& other) const {
    return Vec3<T>(x / other.x, y / other.y, z / other.z);
  }

  template<Vec3T V3T> Vec3<T> operator%(const V3T& other) const {
    return Vec3<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z));
  }

  constexpr Vec3<T> operator+(const T& other) const {
    return Vec3<T>(x + other, y + other, z + other);
  }

  constexpr Vec3<T> operator-(const T& other) const {
    return Vec3<T>(x - other, y - other, z - other);
  }

  constexpr Vec3<T> operator*(const T& other) const {
    return Vec3<T>(x * other, y * other, z * other);
  }

  constexpr Vec3<T> operator/(const T& other) const {
    return Vec3<T>(x / other, y / other, z / other);
  }

  constexpr Vec3<T> operator%(const T& other) const {
    return Vec3<T>(mod<T>(x, other), mod<T>(y, other), mod<T>(z, other));
  }

  // compound assignment operators
  constexpr Vec3<T>& operator+=(const Vec3<T>& v) {
    return *this = *this + v;
  }

  constexpr Vec3<T>& operator-=(const Vec3<T>& v) {
    return *this = *this - v;
  }

  constexpr Vec3<T>& operator*=(const Vec3<T>& v) {
    return *this = *this * v;
  }

  constexpr Vec3<T>& operator/=(const Vec3<T>& v) {
    return *this = *this / v;
  }

  constexpr Vec3<T>& operator%=(const Vec3<T>& v) {
    return *this = *this % v;
  }

  template<Vec3T V3T> Vec3<T>& operator+=(const V3T& other) {
    return *this = *this + other;
  }

  template<Vec3T V3T> Vec3<T>& operator-=(const V3T& other) {
    return *this = *this - other;
  }

  template<Vec3T V3T> Vec3<T>& operator*=(const V3T& other) {
    return *this = *this * other;
  }

  template<Vec3T V3T> Vec3<T>& operator/=(const V3T& other) {
    return *this = *this / other;
  }

  template<Vec3T V3T> Vec3<T>& operator%=(const V3T& other) {
    return *this = *this % other;
  }

  constexpr Vec3<T>& operator+=(const T& other) {
    return *this = *this + other;
  }

  constexpr Vec3<T>& operator-=(const T& other) {
    return *this = *this - other;
  }

  constexpr Vec3<T>& operator*=(const T& other) {
    return *this = *this * other;
  }

  constexpr Vec3<T>& operator/=(const T& other) {
    return *this = *this / other;
  }

  constexpr Vec3<T>& operator%=(const T& other) {
    return *this = *this % other;
  }

  // unary operators
  constexpr Vec3<T> operator-() const {
    return Vec3<T>(-x, -y, -z);
  }

  constexpr Vec3<T> operator!() const {
    return Vec3<T>(!x, !y, !z);
  }

  // lhs-rhs operators
  constexpr friend Vec3<T> operator+(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
  }

  constexpr friend Vec3<T> operator-(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
  }

  constexpr friend Vec3<T> operator*(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }

  constexpr friend Vec3<T> operator/(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
  }

  // comparison operators
  template<Vec3T V3T> bool operator==(const V3T& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  template<Vec3T V3T> bool operator!=(const V3T& other) const {
    return !(*this == other);
  }

  template<Vec3T V3T> bool operator<(const V3T& other) const {
    return x < other.x && y < other.y && z < other.z;
  }

  template<Vec3T V3T> bool operator>(const V3T& other) const {
    return x > other.x && y > other.y && z > other.z;
  }

  template<Vec3T V3T> bool operator<=(const V3T& other) const {
    return x <= other.x && y <= other.y && z <= other.z;
  }

  template<Vec3T V3T> bool operator>=(const V3T& other) const {
    return x >= other.x && y >= other.y && z >= other.z;
  }

#pragma endregion operators

  constexpr static Vec3<decimal_t> zero() { return { 0, 0, 0 }; }
  constexpr static Vec3<decimal_t> one() { return { 1, 1, 1 }; }
  constexpr static Vec3<decimal_t> up() { return { 0, 1, 0 }; }
  constexpr static Vec3<decimal_t> down() { return { 0, -1, 0 }; }
  constexpr static Vec3<decimal_t> left() { return { -1, 0, 0 }; }
  constexpr static Vec3<decimal_t> right() { return { 1, 0, 0 }; }
  constexpr static Vec3<decimal_t> forward() { return { 0, 0, 1 }; }
  constexpr static Vec3<decimal_t> backward() { return { 0, 0, -1 }; }

#pragma region swizzle
#ifdef AMS_VEC_SWIZZLE_METHODS
  [[nodiscard]] constexpr Vec2<T> xx() const {
    return Vec2<T>(x, x);
  }
  [[nodiscard]] constexpr Vec2<T> xy() const {
    return Vec2<T>(x, y);
  }
  [[nodiscard]] constexpr Vec2<T> xz() const {
    return Vec2<T>(x, z);
  }
  [[nodiscard]] constexpr Vec2<T> yx() const {
    return Vec2<T>(y, x);
  }
  [[nodiscard]] constexpr Vec2<T> yy() const {
    return Vec2<T>(y, y);
  }
  [[nodiscard]] constexpr Vec2<T> yz() const {
    return Vec2<T>(y, z);
  }
  [[nodiscard]] constexpr Vec2<T> zx() const {
    return Vec2<T>(z, x);
  }
  [[nodiscard]] constexpr Vec2<T> zy() const {
    return Vec2<T>(z, y);
  }
  [[nodiscard]] constexpr Vec2<T> zz() const {
    return Vec2<T>(z, z);
  }
  [[nodiscard]] constexpr Vec3<T> xxx() const {
    return Vec3<T>(x, x, x);
  }
  [[nodiscard]] constexpr Vec3<T> xxy() const {
    return Vec3<T>(x, x, y);
  }
  [[nodiscard]] constexpr Vec3<T> xxz() const {
    return Vec3<T>(x, x, z);
  }
  [[nodiscard]] constexpr Vec3<T> xyx() const {
    return Vec3<T>(x, y, x);
  }
  [[nodiscard]] constexpr Vec3<T> xyy() const {
    return Vec3<T>(x, y, y);
  }
  [[nodiscard]] constexpr Vec3<T> xyz() const {
    return Vec3<T>(x, y, z);
  }
  [[nodiscard]] constexpr Vec3<T> xzx() const {
    return Vec3<T>(x, z, x);
  }
  [[nodiscard]] constexpr Vec3<T> xzy() const {
    return Vec3<T>(x, z, y);
  }
  [[nodiscard]] constexpr Vec3<T> xzz() const {
    return Vec3<T>(x, z, z);
  }
  [[nodiscard]] constexpr Vec3<T> yxx() const {
    return Vec3<T>(y, x, x);
  }
  [[nodiscard]] constexpr Vec3<T> yxy() const {
    return Vec3<T>(y, x, y);
  }
  [[nodiscard]] constexpr Vec3<T> yxz() const {
    return Vec3<T>(y, x, z);
  }
  [[nodiscard]] constexpr Vec3<T> yyx() const {
    return Vec3<T>(y, y, x);
  }
  [[nodiscard]] constexpr Vec3<T> yyy() const {
    return Vec3<T>(y, y, y);
  }
  [[nodiscard]] constexpr Vec3<T> yyz() const {
    return Vec3<T>(y, y, z);
  }
  [[nodiscard]] constexpr Vec3<T> yzx() const {
    return Vec3<T>(y, z, x);
  }
  [[nodiscard]] constexpr Vec3<T> yzy() const {
    return Vec3<T>(y, z, y);
  }
  [[nodiscard]] constexpr Vec3<T> yzz() const {
    return Vec3<T>(y, z, z);
  }
  [[nodiscard]] constexpr Vec3<T> zxx() const {
    return Vec3<T>(z, x, x);
  }
  [[nodiscard]] constexpr Vec3<T> zxy() const {
    return Vec3<T>(z, x, y);
  }
  [[nodiscard]] constexpr Vec3<T> zxz() const {
    return Vec3<T>(z, x, z);
  }
  [[nodiscard]] constexpr Vec3<T> zyx() const {
    return Vec3<T>(z, y, x);
  }
  [[nodiscard]] constexpr Vec3<T> zyy() const {
    return Vec3<T>(z, y, y);
  }
  [[nodiscard]] constexpr Vec3<T> zyz() const {
    return Vec3<T>(z, y, z);
  }
  [[nodiscard]] constexpr Vec3<T> zzx() const {
    return Vec3<T>(z, z, x);
  }
  [[nodiscard]] constexpr Vec3<T> zzy() const {
    return Vec3<T>(z, z, y);
  }
  [[nodiscard]] constexpr Vec3<T> zzz() const {
    return Vec3<T>(z, z, z);
  }
#endif // AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle
};

} // ams
