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
/*[export module ams.spatial.Quaternion]*/
/*[exclude begin]*/
#pragma once
#include "Vec.hpp"
/*[exclude end]*/
#include <cstdlib>
/*[import ams]*/
/*[import ams.spatial.Vec]*/

namespace ams {

struct Matrix3;

/*[export]*/ struct Quaternion : public Vec4<decimal_t> {
public:
  constexpr Quaternion() = default;

  constexpr Quaternion(decimal_t x, decimal_t y, decimal_t z, decimal_t w)
  : Vec4<decimal_t>(x, y, z, w) {}

  explicit constexpr Quaternion(const Vec4<decimal_t>& v)
  : Vec4<decimal_t>(v) {}

  constexpr Quaternion(const Quaternion& q)
  : Vec4<decimal_t>(q) {}
  
  constexpr Quaternion(const Vec3<decimal_t> &axis, decimal_t angle) {
    const decimal_t halfAngle = angle * 0.5;
    const decimal_t sinHalfAngle = sin(halfAngle);
    const decimal_t cosHalfAngle = cos(halfAngle);
    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    z = axis.z * sinHalfAngle;
    w = cosHalfAngle;
  }
  
  explicit constexpr Quaternion(const Matrix3 &m);

  virtual ~Quaternion() = default;

  constexpr Quaternion& operator=(const Quaternion& q) {
    Vec4<decimal_t>::operator=(q);
    return *this;
  }

  constexpr Quaternion& operator=(const Vec4<decimal_t>& v) {
    Vec4<decimal_t>::operator=(v);
    return *this;
  }

  constexpr Quaternion& operator=(const Vec3<decimal_t>& v) {
    *this = Quaternion(v.x, v.y, v.z, 1);
    return *this;
  }

  constexpr Quaternion& operator=(decimal_t d) {
    *this = Quaternion(d, d, d, d);
    return *this;
  }

  constexpr Quaternion operator+(const Quaternion& q) const {
    return {this->x + q.x, this->y + q.y, this->z + q.z, this->w + q.w};
  }

  constexpr Quaternion& operator+=(const Quaternion& q) {
    return *this = *this + q;
  }

  constexpr Quaternion operator-(const Quaternion& q) const {
    return {this->x - q.x, this->y - q.y, this->z - q.z, this->w - q.w};
  }

  constexpr Quaternion& operator-=(const Quaternion& q) {
    return *this = *this - q;
  }

  constexpr Quaternion operator*(const Quaternion& q) const {
    return {
      this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
      this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,
      this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w,
      this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z
    };
  }

  constexpr Quaternion& operator*=(const Quaternion& q) {
    return *this = *this * q;
  }

  constexpr Quaternion operator/(const Quaternion& q) const {
    return *this * q.inverted();
  }

  constexpr Quaternion& operator/=(const Quaternion& q) {
    return *this = *this / q;
  }
  
  constexpr Quaternion operator*(const Matrix3& m) const;

  constexpr Quaternion& operator*=(const Matrix3& m);

  [[nodiscard]] constexpr Vec3<decimal_t> euler() {
    decimal_t x = this->x;
    decimal_t y = this->y;
    decimal_t z = this->z;
    decimal_t w = this->w;
    decimal_t sinr_cosp = 2 * (w * x + y * z);
    decimal_t cosr_cosp = 1 - 2 * (x * x + y * y);
    decimal_t roll = atan2(sinr_cosp, cosr_cosp);
    decimal_t sinp = 2 * (w * y - z * x);
    decimal_t pitch = abs(sinp) >= 1 ? copysign(PI / 2, sinp) : asin(sinp);
    decimal_t siny_cosp = 2 * (w * z + x * y);
    decimal_t cosy_cosp = 1 - 2 * (y * y + z * z);
    decimal_t yaw = atan2(siny_cosp, cosy_cosp);
    return {roll, pitch, yaw};
  }

  [[nodiscard]] constexpr Quaternion inverted() const {
    return {-this->x, -this->y, -this->z, this->w};
  }
  
  constexpr void lookat(const Vec3<decimal_t>& direction, const Vec3<decimal_t>& up) {
    // quaternion lookat calculation

    // 1. get the rotation axis
    Vec3<decimal_t> axis = cross(up, direction);
    axis = normalize(axis);
    // 2. get the rotation angle
    decimal_t angle = acos(dot(up, direction));
    // 3. create the quaternion
    *this = Quaternion(axis, angle);
  }

  [[nodiscard]] static constexpr Quaternion identity() {
    return {0.0, 0.0, 0.0, 1.0};
  }

  static constexpr void fromAxisAngle(Quaternion& q, const Vec3<decimal_t>& axis, decimal_t angle) {
    decimal_t half_angle = angle / 2.0;
    decimal_t sin_half_angle = sin(half_angle);
    q.x = axis.x * sin_half_angle;
    q.y = axis.y * sin_half_angle;
    q.z = axis.z * sin_half_angle;
    q.w = cos(half_angle);
  }

  [[nodiscard]]
  static constexpr Quaternion fromAxisAngle(const Vec3<decimal_t>& axis, decimal_t angle) {
    Quaternion q;
    fromAxisAngle(q, axis, angle);
    return q;
  }

  static constexpr void fromEuler(Quaternion& q, const Vec3<decimal_t>& euler) {
    decimal_t roll = euler.x;
    decimal_t pitch = euler.y;
    decimal_t yaw = euler.z;
    decimal_t sin_roll = sin(roll * 0.5);
    decimal_t cos_roll = cos(roll * 0.5);
    decimal_t sin_pitch = sin(pitch * 0.5);
    decimal_t cos_pitch = cos(pitch * 0.5);
    decimal_t sin_yaw = sin(yaw * 0.5);
    decimal_t cos_yaw = cos(yaw * 0.5);
    q.x = sin_roll * cos_pitch * cos_yaw - cos_roll * sin_pitch * sin_yaw;
    q.y = cos_roll * sin_pitch * cos_yaw + sin_roll * cos_pitch * sin_yaw;
    q.z = cos_roll * cos_pitch * sin_yaw - sin_roll * sin_pitch * cos_yaw;
    q.w = cos_roll * cos_pitch * cos_yaw + sin_roll * sin_pitch * sin_yaw;
  }

  [[nodiscard]]
  static constexpr Quaternion fromEuler(const Vec3<decimal_t>& euler) {
    Quaternion q;
    fromEuler(q, euler);
    return q;
  }

  [[nodiscard]]
  static constexpr Quaternion lookAt(const Vec3<decimal_t>& direction, const Vec3<decimal_t>& up) {
    Quaternion q;
    q.lookat(direction, up);
    return q;
  }

};

} // ams
