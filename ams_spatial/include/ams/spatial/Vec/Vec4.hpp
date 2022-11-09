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
#include "Vec3.hpp"
/*[exclude end]*/
/*[export module ams.spatial.Vec4]*/
#include <stdexcept>
/*[import ams]*/
/*[import ams.spatial.internal]*/
/*[import ams.spatial.Vec2]*/
/*[import ams.spatial.Vec3]*/

/*[export]*/ namespace ams {

/**
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec4 {
  T x, y, z, w;

  constexpr Vec4() : x(0), y(0), z(0), w(0) {}

  constexpr explicit Vec4(T x) : x(x), y(x), z(x), w(x) {}

  constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

  constexpr Vec4(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

  template<Vec4T V4T> constexpr Vec4(const V4T& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
  
  template<Vec3T V3T> constexpr Vec4(const V3T& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    if constexpr (AMSExceptions)
      if (i < 0 || i > 3) throw std::out_of_range("Vec4 subscript out of range");
    return (&x)[i];
  }

  // const copy assignment operator
  constexpr Vec4<T>& operator=(const Vec4<T>& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }
  
  // copy assignment operator
  template<Vec4T V4T> constexpr Vec4<T>& operator=(const V4T& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  // arithmetic operators
  constexpr Vec4<T> operator+(const Vec4<T>& other) const {
    return Vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  constexpr Vec4<T> operator-(const Vec4<T>& other) const {
    return Vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  constexpr Vec4<T> operator*(const Vec4<T>& other) const {
    return Vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
  }

  constexpr Vec4<T> operator/(const Vec4<T>& other) const {
    return Vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
  }

  constexpr Vec4<T> operator%(const Vec4<T>& other) const {
    return Vec4<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z), mod<T>(w, other.w));
  }

  template<Vec4T V4T> Vec4<T> operator+(const V4T& other) const {
    return Vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  template<Vec4T V4T> Vec4<T> operator-(const V4T& other) const {
    return Vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  template<Vec4T V4T> Vec4<T> operator*(const V4T& other) const {
    return Vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
  }

  template<Vec4T V4T> Vec4<T> operator/(const V4T& other) const {
    return Vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
  }

  template<Vec4T V4T> Vec4<T> operator%(const V4T& other) const {
    return Vec4<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z), mod<T>(w, other.w));
  }

  constexpr Vec4<T> operator+(T scalar) const {
    return Vec4<T>(x + scalar, y + scalar, z + scalar, w + scalar);
  }

  constexpr Vec4<T> operator-(T scalar) const {
    return Vec4<T>(x - scalar, y - scalar, z - scalar, w - scalar);
  }

  constexpr Vec4<T> operator*(T scalar) const {
    return Vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  constexpr Vec4<T> operator/(T scalar) const {
    return Vec4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
  }

  constexpr Vec4<T> operator%(T scalar) const {
    return Vec4<T>(mod<T>(x, scalar), mod<T>(y, scalar), mod<T>(z, scalar), mod<T>(w, scalar));
  }

  // compound assignment operators
  constexpr Vec4<T>& operator+=(const Vec4<T>& other) {
    return *this = *this + other;
  }

  constexpr Vec4<T>& operator-=(const Vec4<T>& other) {
    return *this = *this - other;
  }

  constexpr Vec4<T>& operator*=(const Vec4<T>& other) {
    return *this = *this * other;
  }

  constexpr Vec4<T>& operator/=(const Vec4<T>& other) {
    return *this = *this / other;
  }

  constexpr Vec4<T>& operator%=(const Vec4<T>& other) {
    return *this = *this % other;
  }

  template<Vec4T V4T> Vec4<T>& operator+=(const V4T& other) {
    return *this = *this + other;
  }

  template<Vec4T V4T> Vec4<T>& operator-=(const V4T& other) {
    return *this = *this - other;
  }

  template<Vec4T V4T> Vec4<T>& operator*=(const V4T& other) {
    return *this = *this * other;
  }

  template<Vec4T V4T> Vec4<T>& operator/=(const V4T& other) {
    return *this = *this / other;
  }

  template<Vec4T V4T> Vec4<T>& operator%=(const V4T& other) {
    return *this = *this % other;
  }

  constexpr Vec4<T>& operator+=(T scalar) {
    return *this = *this + scalar;
  }

  constexpr Vec4<T>& operator-=(T scalar) {
    return *this = *this - scalar;
  }

  constexpr Vec4<T>& operator*=(T scalar) {
    return *this = *this * scalar;
  }

  constexpr Vec4<T>& operator/=(T scalar) {
    return *this = *this / scalar;
  }

  constexpr Vec4<T>& operator%=(T scalar) {
    return *this = *this % scalar;
  }

  // unary operators
  constexpr Vec4<T> operator-() const {
    return Vec4<T>(-x, -y, -z, -w);
  }

  constexpr Vec4<T> operator!() const {
    return Vec4<T>(!x, !y, !z, !w);
  }
  
  // scalar lhs-rhs operators
  constexpr friend Vec4<T> operator+(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
  }

  constexpr friend Vec4<T> operator-(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
  }

  constexpr friend Vec4<T> operator*(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
  }

  constexpr friend Vec4<T> operator/(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
  }

  // comparison operators
  template<Vec4T V4T> bool operator==(const V4T& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  template<Vec4T V4T> bool operator!=(const V4T& other) const {
    return !(*this == other);
  }

  template<Vec4T V4T> bool operator<(const V4T& other) const {
    return x < other.x && y < other.y && z < other.z && w < other.w;
  }

  template<Vec4T V4T> bool operator<=(const V4T& other) const {
    return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
  }

  template<Vec4T V4T> bool operator>(const V4T& other) const {
    return x > other.x && y > other.y && z > other.z && w > other.w;
  }

  template<Vec4T V4T> bool operator>=(const V4T& other) const {
    return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
  }

  constexpr static Vec4<decimal_t> zero() { return {0, 0, 0, 0}; }
  constexpr static Vec4<decimal_t> one() { return {1, 1, 1, 1}; }
  constexpr static Vec4<decimal_t> unit_x() { return {1, 0, 0, 0}; }
  constexpr static Vec4<decimal_t> unit_y() { return {0, 1, 0, 0}; }
  constexpr static Vec4<decimal_t> unit_z() { return {0, 0, 1, 0}; }
  constexpr static Vec4<decimal_t> unit_w() { return {0, 0, 0, 1}; }

#pragma endregion operators
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
  [[nodiscard]] constexpr Vec2<T> xw() const {
    return Vec2<T>(x, w);
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
  [[nodiscard]] constexpr Vec2<T> yw() const {
    return Vec2<T>(y, w);
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
  [[nodiscard]] constexpr Vec2<T> zw() const {
    return Vec2<T>(z, w);
  }
  [[nodiscard]] constexpr Vec2<T> wx() const {
    return Vec2<T>(w, x);
  }
  [[nodiscard]] constexpr Vec2<T> wy() const {
    return Vec2<T>(w, y);
  }
  [[nodiscard]] constexpr Vec2<T> wz() const {
    return Vec2<T>(w, z);
  }
  [[nodiscard]] constexpr Vec2<T> ww() const {
    return Vec2<T>(w, w);
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
  [[nodiscard]] constexpr Vec3<T> xxw() const {
    return Vec3<T>(x, x, w);
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
  [[nodiscard]] constexpr Vec3<T> xyw() const {
    return Vec3<T>(x, y, w);
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
  [[nodiscard]] constexpr Vec3<T> xzw() const {
    return Vec3<T>(x, z, w);
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
  [[nodiscard]] constexpr Vec3<T> yxw() const {
    return Vec3<T>(y, x, w);
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
  [[nodiscard]] constexpr Vec3<T> yyw() const {
    return Vec3<T>(y, y, w);
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
  [[nodiscard]] constexpr Vec3<T> yzw() const {
    return Vec3<T>(y, z, w);
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
  [[nodiscard]] constexpr Vec3<T> zxw() const {
    return Vec3<T>(z, x, w);
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
  [[nodiscard]] constexpr Vec3<T> zyw() const {
    return Vec3<T>(z, y, w);
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
  [[nodiscard]] constexpr Vec3<T> zzw() const {
    return Vec3<T>(z, z, w);
  }
  [[nodiscard]] constexpr Vec3<T> wxx() const {
    return Vec3<T>(w, x, x);
  }
  [[nodiscard]] constexpr Vec3<T> wxy() const {
    return Vec3<T>(w, x, y);
  }
  [[nodiscard]] constexpr Vec3<T> wxz() const {
    return Vec3<T>(w, x, z);
  }
  [[nodiscard]] constexpr Vec3<T> wxw() const {
    return Vec3<T>(w, x, w);
  }
  [[nodiscard]] constexpr Vec3<T> wyx() const {
    return Vec3<T>(w, y, x);
  }
  [[nodiscard]] constexpr Vec3<T> wyy() const {
    return Vec3<T>(w, y, y);
  }
  [[nodiscard]] constexpr Vec3<T> wyz() const {
    return Vec3<T>(w, y, z);
  }
  [[nodiscard]] constexpr Vec3<T> wyw() const {
    return Vec3<T>(w, y, w);
  }
  [[nodiscard]] constexpr Vec3<T> wzx() const {
    return Vec3<T>(w, z, x);
  }
  [[nodiscard]] constexpr Vec3<T> wzy() const {
    return Vec3<T>(w, z, y);
  }
  [[nodiscard]] constexpr Vec3<T> wzz() const {
    return Vec3<T>(w, z, z);
  }
  [[nodiscard]] constexpr Vec3<T> wzw() const {
    return Vec3<T>(w, z, w);
  }
  [[nodiscard]] constexpr Vec3<T> wwx() const {
    return Vec3<T>(w, w, x);
  }
  [[nodiscard]] constexpr Vec3<T> wwy() const {
    return Vec3<T>(w, w, y);
  }
  [[nodiscard]] constexpr Vec3<T> wwz() const {
    return Vec3<T>(w, w, z);
  }
  [[nodiscard]] constexpr Vec3<T> www() const {
    return Vec3<T>(w, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> xxxx() const {
    return Vec4<T>(x, x, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> xxxy() const {
    return Vec4<T>(x, x, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> xxxz() const {
    return Vec4<T>(x, x, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> xxxw() const {
    return Vec4<T>(x, x, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> xxyx() const {
    return Vec4<T>(x, x, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> xxyy() const {
    return Vec4<T>(x, x, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> xxyz() const {
    return Vec4<T>(x, x, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> xxyw() const {
    return Vec4<T>(x, x, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> xxzx() const {
    return Vec4<T>(x, x, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> xxzy() const {
    return Vec4<T>(x, x, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> xxzz() const {
    return Vec4<T>(x, x, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> xxzw() const {
    return Vec4<T>(x, x, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> xxwx() const {
    return Vec4<T>(x, x, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> xxwy() const {
    return Vec4<T>(x, x, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> xxwz() const {
    return Vec4<T>(x, x, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> xxww() const {
    return Vec4<T>(x, x, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> xyxx() const {
    return Vec4<T>(x, y, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> xyxy() const {
    return Vec4<T>(x, y, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> xyxz() const {
    return Vec4<T>(x, y, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> xyxw() const {
    return Vec4<T>(x, y, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> xyyx() const {
    return Vec4<T>(x, y, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> xyyy() const {
    return Vec4<T>(x, y, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> xyyz() const {
    return Vec4<T>(x, y, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> xyyw() const {
    return Vec4<T>(x, y, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> xyzx() const {
    return Vec4<T>(x, y, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> xyzy() const {
    return Vec4<T>(x, y, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> xyzz() const {
    return Vec4<T>(x, y, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> xyzw() const {
    return Vec4<T>(x, y, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> xywx() const {
    return Vec4<T>(x, y, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> xywy() const {
    return Vec4<T>(x, y, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> xywz() const {
    return Vec4<T>(x, y, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> xyww() const {
    return Vec4<T>(x, y, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> xzxx() const {
    return Vec4<T>(x, z, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> xzxy() const {
    return Vec4<T>(x, z, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> xzxz() const {
    return Vec4<T>(x, z, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> xzxw() const {
    return Vec4<T>(x, z, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> xzyx() const {
    return Vec4<T>(x, z, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> xzyy() const {
    return Vec4<T>(x, z, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> xzyz() const {
    return Vec4<T>(x, z, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> xzyw() const {
    return Vec4<T>(x, z, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> xzzx() const {
    return Vec4<T>(x, z, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> xzzy() const {
    return Vec4<T>(x, z, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> xzzz() const {
    return Vec4<T>(x, z, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> xzzw() const {
    return Vec4<T>(x, z, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> xzwx() const {
    return Vec4<T>(x, z, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> xzwy() const {
    return Vec4<T>(x, z, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> xzwz() const {
    return Vec4<T>(x, z, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> xzww() const {
    return Vec4<T>(x, z, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> xwxx() const {
    return Vec4<T>(x, w, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> xwxy() const {
    return Vec4<T>(x, w, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> xwxz() const {
    return Vec4<T>(x, w, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> xwxw() const {
    return Vec4<T>(x, w, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> xwyx() const {
    return Vec4<T>(x, w, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> xwyy() const {
    return Vec4<T>(x, w, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> xwyz() const {
    return Vec4<T>(x, w, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> xwyw() const {
    return Vec4<T>(x, w, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> xwzx() const {
    return Vec4<T>(x, w, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> xwzy() const {
    return Vec4<T>(x, w, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> xwzz() const {
    return Vec4<T>(x, w, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> xwzw() const {
    return Vec4<T>(x, w, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> xwwx() const {
    return Vec4<T>(x, w, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> xwwy() const {
    return Vec4<T>(x, w, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> xwwz() const {
    return Vec4<T>(x, w, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> xwww() const {
    return Vec4<T>(x, w, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> yxxx() const {
    return Vec4<T>(y, x, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> yxxy() const {
    return Vec4<T>(y, x, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> yxxz() const {
    return Vec4<T>(y, x, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> yxxw() const {
    return Vec4<T>(y, x, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> yxyx() const {
    return Vec4<T>(y, x, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> yxyy() const {
    return Vec4<T>(y, x, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> yxyz() const {
    return Vec4<T>(y, x, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> yxyw() const {
    return Vec4<T>(y, x, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> yxzx() const {
    return Vec4<T>(y, x, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> yxzy() const {
    return Vec4<T>(y, x, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> yxzz() const {
    return Vec4<T>(y, x, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> yxzw() const {
    return Vec4<T>(y, x, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> yxwx() const {
    return Vec4<T>(y, x, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> yxwy() const {
    return Vec4<T>(y, x, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> yxwz() const {
    return Vec4<T>(y, x, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> yxww() const {
    return Vec4<T>(y, x, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> yyxx() const {
    return Vec4<T>(y, y, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> yyxy() const {
    return Vec4<T>(y, y, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> yyxz() const {
    return Vec4<T>(y, y, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> yyxw() const {
    return Vec4<T>(y, y, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> yyyx() const {
    return Vec4<T>(y, y, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> yyyy() const {
    return Vec4<T>(y, y, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> yyyz() const {
    return Vec4<T>(y, y, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> yyyw() const {
    return Vec4<T>(y, y, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> yyzx() const {
    return Vec4<T>(y, y, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> yyzy() const {
    return Vec4<T>(y, y, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> yyzz() const {
    return Vec4<T>(y, y, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> yyzw() const {
    return Vec4<T>(y, y, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> yywx() const {
    return Vec4<T>(y, y, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> yywy() const {
    return Vec4<T>(y, y, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> yywz() const {
    return Vec4<T>(y, y, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> yyww() const {
    return Vec4<T>(y, y, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> yzxx() const {
    return Vec4<T>(y, z, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> yzxy() const {
    return Vec4<T>(y, z, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> yzxz() const {
    return Vec4<T>(y, z, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> yzxw() const {
    return Vec4<T>(y, z, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> yzyx() const {
    return Vec4<T>(y, z, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> yzyy() const {
    return Vec4<T>(y, z, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> yzyz() const {
    return Vec4<T>(y, z, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> yzyw() const {
    return Vec4<T>(y, z, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> yzzx() const {
    return Vec4<T>(y, z, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> yzzy() const {
    return Vec4<T>(y, z, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> yzzz() const {
    return Vec4<T>(y, z, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> yzzw() const {
    return Vec4<T>(y, z, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> yzwx() const {
    return Vec4<T>(y, z, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> yzwy() const {
    return Vec4<T>(y, z, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> yzwz() const {
    return Vec4<T>(y, z, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> yzww() const {
    return Vec4<T>(y, z, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> ywxx() const {
    return Vec4<T>(y, w, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> ywxy() const {
    return Vec4<T>(y, w, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> ywxz() const {
    return Vec4<T>(y, w, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> ywxw() const {
    return Vec4<T>(y, w, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> ywyx() const {
    return Vec4<T>(y, w, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> ywyy() const {
    return Vec4<T>(y, w, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> ywyz() const {
    return Vec4<T>(y, w, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> ywyw() const {
    return Vec4<T>(y, w, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> ywzx() const {
    return Vec4<T>(y, w, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> ywzy() const {
    return Vec4<T>(y, w, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> ywzz() const {
    return Vec4<T>(y, w, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> ywzw() const {
    return Vec4<T>(y, w, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> ywwx() const {
    return Vec4<T>(y, w, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> ywwy() const {
    return Vec4<T>(y, w, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> ywwz() const {
    return Vec4<T>(y, w, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> ywww() const {
    return Vec4<T>(y, w, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> zxxx() const {
    return Vec4<T>(z, x, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> zxxy() const {
    return Vec4<T>(z, x, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> zxxz() const {
    return Vec4<T>(z, x, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> zxxw() const {
    return Vec4<T>(z, x, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> zxyx() const {
    return Vec4<T>(z, x, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> zxyy() const {
    return Vec4<T>(z, x, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> zxyz() const {
    return Vec4<T>(z, x, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> zxyw() const {
    return Vec4<T>(z, x, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> zxzx() const {
    return Vec4<T>(z, x, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> zxzy() const {
    return Vec4<T>(z, x, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> zxzz() const {
    return Vec4<T>(z, x, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> zxzw() const {
    return Vec4<T>(z, x, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> zxwx() const {
    return Vec4<T>(z, x, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> zxwy() const {
    return Vec4<T>(z, x, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> zxwz() const {
    return Vec4<T>(z, x, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> zxww() const {
    return Vec4<T>(z, x, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> zyxx() const {
    return Vec4<T>(z, y, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> zyxy() const {
    return Vec4<T>(z, y, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> zyxz() const {
    return Vec4<T>(z, y, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> zyxw() const {
    return Vec4<T>(z, y, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> zyyx() const {
    return Vec4<T>(z, y, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> zyyy() const {
    return Vec4<T>(z, y, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> zyyz() const {
    return Vec4<T>(z, y, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> zyyw() const {
    return Vec4<T>(z, y, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> zyzx() const {
    return Vec4<T>(z, y, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> zyzy() const {
    return Vec4<T>(z, y, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> zyzz() const {
    return Vec4<T>(z, y, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> zyzw() const {
    return Vec4<T>(z, y, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> zywx() const {
    return Vec4<T>(z, y, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> zywy() const {
    return Vec4<T>(z, y, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> zywz() const {
    return Vec4<T>(z, y, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> zyww() const {
    return Vec4<T>(z, y, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> zzxx() const {
    return Vec4<T>(z, z, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> zzxy() const {
    return Vec4<T>(z, z, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> zzxz() const {
    return Vec4<T>(z, z, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> zzxw() const {
    return Vec4<T>(z, z, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> zzyx() const {
    return Vec4<T>(z, z, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> zzyy() const {
    return Vec4<T>(z, z, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> zzyz() const {
    return Vec4<T>(z, z, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> zzyw() const {
    return Vec4<T>(z, z, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> zzzx() const {
    return Vec4<T>(z, z, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> zzzy() const {
    return Vec4<T>(z, z, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> zzzz() const {
    return Vec4<T>(z, z, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> zzzw() const {
    return Vec4<T>(z, z, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> zzwx() const {
    return Vec4<T>(z, z, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> zzwy() const {
    return Vec4<T>(z, z, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> zzwz() const {
    return Vec4<T>(z, z, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> zzww() const {
    return Vec4<T>(z, z, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> zwxx() const {
    return Vec4<T>(z, w, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> zwxy() const {
    return Vec4<T>(z, w, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> zwxz() const {
    return Vec4<T>(z, w, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> zwxw() const {
    return Vec4<T>(z, w, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> zwyx() const {
    return Vec4<T>(z, w, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> zwyy() const {
    return Vec4<T>(z, w, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> zwyz() const {
    return Vec4<T>(z, w, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> zwyw() const {
    return Vec4<T>(z, w, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> zwzx() const {
    return Vec4<T>(z, w, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> zwzy() const {
    return Vec4<T>(z, w, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> zwzz() const {
    return Vec4<T>(z, w, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> zwzw() const {
    return Vec4<T>(z, w, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> zwwx() const {
    return Vec4<T>(z, w, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> zwwy() const {
    return Vec4<T>(z, w, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> zwwz() const {
    return Vec4<T>(z, w, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> zwww() const {
    return Vec4<T>(z, w, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> wxxx() const {
    return Vec4<T>(w, x, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> wxxy() const {
    return Vec4<T>(w, x, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> wxxz() const {
    return Vec4<T>(w, x, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> wxxw() const {
    return Vec4<T>(w, x, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> wxyx() const {
    return Vec4<T>(w, x, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> wxyy() const {
    return Vec4<T>(w, x, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> wxyz() const {
    return Vec4<T>(w, x, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> wxyw() const {
    return Vec4<T>(w, x, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> wxzx() const {
    return Vec4<T>(w, x, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> wxzy() const {
    return Vec4<T>(w, x, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> wxzz() const {
    return Vec4<T>(w, x, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> wxzw() const {
    return Vec4<T>(w, x, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> wxwx() const {
    return Vec4<T>(w, x, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> wxwy() const {
    return Vec4<T>(w, x, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> wxwz() const {
    return Vec4<T>(w, x, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> wxww() const {
    return Vec4<T>(w, x, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> wyxx() const {
    return Vec4<T>(w, y, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> wyxy() const {
    return Vec4<T>(w, y, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> wyxz() const {
    return Vec4<T>(w, y, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> wyxw() const {
    return Vec4<T>(w, y, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> wyyx() const {
    return Vec4<T>(w, y, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> wyyy() const {
    return Vec4<T>(w, y, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> wyyz() const {
    return Vec4<T>(w, y, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> wyyw() const {
    return Vec4<T>(w, y, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> wyzx() const {
    return Vec4<T>(w, y, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> wyzy() const {
    return Vec4<T>(w, y, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> wyzz() const {
    return Vec4<T>(w, y, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> wyzw() const {
    return Vec4<T>(w, y, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> wywx() const {
    return Vec4<T>(w, y, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> wywy() const {
    return Vec4<T>(w, y, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> wywz() const {
    return Vec4<T>(w, y, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> wyww() const {
    return Vec4<T>(w, y, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> wzxx() const {
    return Vec4<T>(w, z, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> wzxy() const {
    return Vec4<T>(w, z, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> wzxz() const {
    return Vec4<T>(w, z, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> wzxw() const {
    return Vec4<T>(w, z, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> wzyx() const {
    return Vec4<T>(w, z, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> wzyy() const {
    return Vec4<T>(w, z, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> wzyz() const {
    return Vec4<T>(w, z, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> wzyw() const {
    return Vec4<T>(w, z, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> wzzx() const {
    return Vec4<T>(w, z, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> wzzy() const {
    return Vec4<T>(w, z, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> wzzz() const {
    return Vec4<T>(w, z, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> wzzw() const {
    return Vec4<T>(w, z, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> wzwx() const {
    return Vec4<T>(w, z, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> wzwy() const {
    return Vec4<T>(w, z, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> wzwz() const {
    return Vec4<T>(w, z, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> wzww() const {
    return Vec4<T>(w, z, w, w);
  }
  [[nodiscard]] constexpr Vec4<T> wwxx() const {
    return Vec4<T>(w, w, x, x);
  }
  [[nodiscard]] constexpr Vec4<T> wwxy() const {
    return Vec4<T>(w, w, x, y);
  }
  [[nodiscard]] constexpr Vec4<T> wwxz() const {
    return Vec4<T>(w, w, x, z);
  }
  [[nodiscard]] constexpr Vec4<T> wwxw() const {
    return Vec4<T>(w, w, x, w);
  }
  [[nodiscard]] constexpr Vec4<T> wwyx() const {
    return Vec4<T>(w, w, y, x);
  }
  [[nodiscard]] constexpr Vec4<T> wwyy() const {
    return Vec4<T>(w, w, y, y);
  }
  [[nodiscard]] constexpr Vec4<T> wwyz() const {
    return Vec4<T>(w, w, y, z);
  }
  [[nodiscard]] constexpr Vec4<T> wwyw() const {
    return Vec4<T>(w, w, y, w);
  }
  [[nodiscard]] constexpr Vec4<T> wwzx() const {
    return Vec4<T>(w, w, z, x);
  }
  [[nodiscard]] constexpr Vec4<T> wwzy() const {
    return Vec4<T>(w, w, z, y);
  }
  [[nodiscard]] constexpr Vec4<T> wwzz() const {
    return Vec4<T>(w, w, z, z);
  }
  [[nodiscard]] constexpr Vec4<T> wwzw() const {
    return Vec4<T>(w, w, z, w);
  }
  [[nodiscard]] constexpr Vec4<T> wwwx() const {
    return Vec4<T>(w, w, w, x);
  }
  [[nodiscard]] constexpr Vec4<T> wwwy() const {
    return Vec4<T>(w, w, w, y);
  }
  [[nodiscard]] constexpr Vec4<T> wwwz() const {
    return Vec4<T>(w, w, w, z);
  }
  [[nodiscard]] constexpr Vec4<T> wwww() const {
    return Vec4<T>(w, w, w, w);
  }
#endif //AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle
};

} // ams
