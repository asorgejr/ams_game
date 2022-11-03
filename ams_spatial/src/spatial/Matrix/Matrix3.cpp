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

#ifndef AMS_MODULES
#include "../../../include/ams/spatial/Matrix/Matrix3.hpp"
#include "../../../include/ams/spatial/Matrix.hpp"
#include "../../../include/ams/spatial/Quaternion.hpp"
#else
import ams.spatial.Matrix3;
import ams.spatial.Quaternion;
#endif

namespace ams {

constexpr Matrix3::Matrix3(const Matrix4& mat)
: m{mat.m[0][0], mat.m[0][1], mat.m[0][2],
    mat.m[1][0], mat.m[1][1], mat.m[1][2],
    mat.m[2][0], mat.m[2][1], mat.m[2][2]} {}

constexpr Matrix3::Matrix3(const Quaternion& q) {
  const decimal_t x2 = q.x * q.x;
  const decimal_t y2 = q.y * q.y;
  const decimal_t z2 = q.z * q.z;
  const decimal_t xy = q.x * q.y;
  const decimal_t xz = q.x * q.z;
  const decimal_t yz = q.y * q.z;
  const decimal_t wx = q.w * q.x;
  const decimal_t wy = q.w * q.y;
  const decimal_t wz = q.w * q.z;
  m[0][0] = 1.0f - 2.0f * (y2 + z2);
  m[0][1] = 2.0f * (xy - wz);
  m[0][2] = 2.0f * (xz + wy);
  m[1][0] = 2.0f * (xy + wz);
  m[1][1] = 1.0f - 2.0f * (x2 + z2);
  m[1][2] = 2.0f * (yz - wx);
  m[2][0] = 2.0f * (xz - wy);
  m[2][1] = 2.0f * (yz + wx);
  m[2][2] = 1.0f - 2.0f * (x2 + y2);
}

constexpr void Matrix3::transpose() {
  ams::transpose(*this);
}

constexpr Matrix3 Matrix3::transposed() const {
  Matrix3 ret = *this;
  ams::transpose(ret);
  return ret;
}

constexpr decimal_t Matrix3::determinant() const {
  return ams::determinant(*this);
}

constexpr bool Matrix3::invert() {
  return ams::inverse(*this);
}

constexpr Matrix3 Matrix3::inverted() const {
  Matrix3 ret = *this;
  ret.invert();
  return ret;
}

constexpr Quaternion Matrix3::quaternion() const {
  decimal_t t = m[0][0] + m[1][1] + m[2][2];
  decimal_t x, y, z, w;
  if (t > 0) {
    decimal_t s = sqrt(t + 1) * 2;
    x = (m[2][1] - m[1][2]) / s;
    y = (m[0][2] - m[2][0]) / s;
    z = (m[1][0] - m[0][1]) / s;
    w = 0.25 * s;
  } else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
    decimal_t s = sqrt(1 + m[0][0] - m[1][1] - m[2][2]) * 2;
    x = 0.25 * s;
    y = (m[0][1] + m[1][0]) / s;
    z = (m[0][2] + m[2][0]) / s;
    w = (m[2][1] - m[1][2]) / s;
  } else if (m[1][1] > m[2][2]) {
    decimal_t s = sqrt(1 + m[1][1] - m[0][0] - m[2][2]) * 2;
    x = (m[0][1] + m[1][0]) / s;
    y = 0.25 * s;
    z = (m[1][2] + m[2][1]) / s;
    w = (m[0][2] - m[2][0]) / s;
  } else {
    decimal_t s = sqrt(1 + m[2][2] - m[0][0] - m[1][1]) * 2;
    x = (m[0][2] + m[2][0]) / s;
    y = (m[1][2] + m[2][1]) / s;
    z = 0.25 * s;
    w = (m[1][0] - m[0][1]) / s;
  }
  return {x, y, z, w};
}

} // ams