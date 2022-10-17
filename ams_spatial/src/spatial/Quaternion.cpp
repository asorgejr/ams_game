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
#include "../../include/ams/spatial/Matrix.hpp"
#include "../../include/ams/spatial/Quaternion.hpp"
#else
import ams.spatial.Quaternion;
import ams.spatial.Matrix3;
#endif

namespace ams {

constexpr Quaternion::Quaternion(const Matrix3& m) {
  decimal_t tr = trace(m);
  if (tr > 0.0) {
    decimal_t s = 0.5 / sqrt(tr + 1.0);
    w = 0.25 / s;
    x = (m(2, 1) - m(1, 2)) * s;
    y = (m(0, 2) - m(2, 0)) * s;
    z = (m(1, 0) - m(0, 1)) * s;
  } else {
    if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
      decimal_t s = 2.0 * sqrt(1.0 + m(0, 0) - m(1, 1) - m(2, 2));
      w = (m(2, 1) - m(1, 2)) / s;
      x = 0.25 * s;
      y = (m(0, 1) + m(1, 0)) / s;
      z = (m(0, 2) + m(2, 0)) / s;
    } else if (m(1, 1) > m(2, 2)) {
      decimal_t s = 2.0 * sqrt(1.0 + m(1, 1) - m(0, 0) - m(2, 2));
      w = (m(0, 2) - m(2, 0)) / s;
      x = (m(0, 1) + m(1, 0)) / s;
      y = 0.25 * s;
      z = (m(1, 2) + m(2, 1)) / s;
    } else {
      decimal_t s = 2.0 * sqrt(1.0 + m(2, 2) - m(0, 0) - m(1, 1));
      w = (m(1, 0) - m(0, 1)) / s;
      x = (m(0, 2) + m(2, 0)) / s;
      y = (m(1, 2) + m(2, 1)) / s;
      z = 0.25 * s;
    }
  }
}

constexpr Quaternion Quaternion::operator*(const Matrix3& m) const {
  // row-major multiply with Matrix3
  return {
    this->w * m(0, 0) + this->x * m(1, 0) + this->y * m(2, 0),
    this->w * m(0, 1) + this->x * m(1, 1) + this->y * m(2, 1),
    this->w * m(0, 2) + this->x * m(1, 2) + this->y * m(2, 2),
    this->z
  };
}

constexpr Quaternion& Quaternion::operator*=(const Matrix3& m) {
  return *this = *this * m;
}

}