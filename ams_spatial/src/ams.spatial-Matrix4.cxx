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
#include <glm/mat4x4.hpp>
#include "ams/spatial/config.hpp"

module ams.spatial:Matrix4;
import :config;
import :Matrix3;
import :MatrixFunctions;
import :Quaternion;

namespace ams {

constexpr void Matrix4::transpose() {
  ams::transpose(*this);
}

constexpr Matrix4 Matrix4::transposed() const {
  Matrix4 ret = *this;
  ams::transpose(ret);
  return ret;
}

constexpr decimal_t Matrix4::determinant() const {
  return ams::determinant(*this);
}

constexpr bool Matrix4::invert() {
  return ams::inverse(*this);
}

constexpr Matrix4 Matrix4::inverted() const {
  Matrix4 ret = *this;
  ret.invert();
  return ret;
}

constexpr Matrix4 Matrix4::operator*(const Matrix3& other) const {
  // row-major matrix3 multiplication
  Matrix4 ret;
  ret.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0];
  ret.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1];
  ret.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2];
  ret.m[0][3] = m[0][3];
  ret.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0];
  ret.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1];
  ret.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2];
  ret.m[1][3] = m[1][3];
  ret.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0];
  ret.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1];
  ret.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2];
  ret.m[2][3] = m[2][3];
  ret.m[3][0] = m[3][0];
  ret.m[3][1] = m[3][1];
  ret.m[3][2] = m[3][2];
  ret.m[3][3] = m[3][3];
  return ret;
}

constexpr void Matrix4::rotate(const Quaternion& q) {
  // construct a 3x3 rotation matrix from the quaternion
  auto rot = Matrix3(q);
  *this = *this * rot;
}

} // ams