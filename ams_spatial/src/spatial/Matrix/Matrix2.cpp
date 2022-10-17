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
#include "../../../include/ams/spatial/Matrix/Matrix2.hpp"
#include "../../../include/ams/spatial/Matrix.hpp"
#else
import ams.spatial.Matrix2;
import ams.spatial.Quaternion;
#endif

namespace ams {

constexpr void Matrix2::transpose() {
  std::swap(m[0][1], m[1][0]);
}

constexpr Matrix2 Matrix2::transposed() const {
  return {m[0][0], m[1][0], m[0][1], m[1][1]};
}

constexpr decimal_t Matrix2::determinant() const {
  return ams::determinant(*this);
}

constexpr bool Matrix2::invert() {
  return ams::inverse(*this);
}

constexpr Matrix2 Matrix2::inverted() const {
  Matrix2 ret = *this;
  ret.invert();
  return ret;
}

} // ams