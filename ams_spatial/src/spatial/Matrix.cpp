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
import ams.spatial.Matrix;
import ams.spatial.Quaternion;
#endif

namespace ams {

constexpr void rotate(Matrix3& mat, const Quaternion& quat) {
  decimal_t x2 = quat.x + quat.x;
  decimal_t y2 = quat.y + quat.y;
  decimal_t z2 = quat.z + quat.z;
  decimal_t xx2 = quat.x * x2;
  decimal_t yy2 = quat.y * y2;
  decimal_t zz2 = quat.z * z2;
  decimal_t xy2 = quat.x * y2;
  decimal_t xz2 = quat.x * z2;
  decimal_t yz2 = quat.y * z2;
  decimal_t wx2 = quat.w * x2;
  decimal_t wy2 = quat.w * y2;
  decimal_t wz2 = quat.w * z2;
  decimal_t m00 = 1.0 - yy2 - zz2;
  decimal_t m01 = xy2 + wz2;
  decimal_t m02 = xz2 - wy2;
  decimal_t m10 = xy2 - wz2;
  decimal_t m11 = 1.0 - xx2 - zz2;
  decimal_t m12 = yz2 + wx2;
  decimal_t m20 = xz2 + wy2;
  decimal_t m21 = yz2 - wx2;
  decimal_t m22 = 1.0 - xx2 - yy2;
  decimal_t rm00 = mat[0][0] * m00 + mat[0][1] * m10 + mat[0][2] * m20;
  decimal_t rm01 = mat[0][0] * m01 + mat[0][1] * m11 + mat[0][2] * m21;
  decimal_t rm02 = mat[0][0] * m02 + mat[0][1] * m12 + mat[0][2] * m22;
  decimal_t rm10 = mat[1][0] * m00 + mat[1][1] * m10 + mat[1][2] * m20;
  decimal_t rm11 = mat[1][0] * m01 + mat[1][1] * m11 + mat[1][2] * m21;
  decimal_t rm12 = mat[1][0] * m02 + mat[1][1] * m12 + mat[1][2] * m22;
  decimal_t rm20 = mat[2][0] * m00 + mat[2][1] * m10 + mat[2][2] * m20;
  decimal_t rm21 = mat[2][0] * m01 + mat[2][1] * m11 + mat[2][2] * m21;
  decimal_t rm22 = mat[2][0] * m02 + mat[2][1] * m12 + mat[2][2] * m22;
  mat[0][0] = rm00;
  mat[0][1] = rm01;
  mat[0][2] = rm02;
  mat[1][0] = rm10;
  mat[1][1] = rm11;
  mat[1][2] = rm12;
  mat[2][0] = rm20;
  mat[2][1] = rm21;
  mat[2][2] = rm22;
}

constexpr void rotate(Matrix4& mat, const Quaternion& quat) {
  decimal_t x2 = quat.x + quat.x;
  decimal_t y2 = quat.y + quat.y;
  decimal_t z2 = quat.z + quat.z;
  decimal_t xx2 = quat.x * x2;
  decimal_t yy2 = quat.y * y2;
  decimal_t zz2 = quat.z * z2;
  decimal_t xy2 = quat.x * y2;
  decimal_t xz2 = quat.x * z2;
  decimal_t yz2 = quat.y * z2;
  decimal_t wx2 = quat.w * x2;
  decimal_t wy2 = quat.w * y2;
  decimal_t wz2 = quat.w * z2;
  decimal_t m00 = 1.0 - yy2 - zz2;
  decimal_t m01 = xy2 + wz2;
  decimal_t m02 = xz2 - wy2;
  decimal_t m10 = xy2 - wz2;
  decimal_t m11 = 1.0 - xx2 - zz2;
  decimal_t m12 = yz2 + wx2;
  decimal_t m20 = xz2 + wy2;
  decimal_t m21 = yz2 - wx2;
  decimal_t m22 = 1.0 - xx2 - yy2;
  decimal_t rm00 = mat[0][0] * m00 + mat[0][1] * m10 + mat[0][2] * m20;
  decimal_t rm01 = mat[0][0] * m01 + mat[0][1] * m11 + mat[0][2] * m21;
  decimal_t rm02 = mat[0][0] * m02 + mat[0][1] * m12 + mat[0][2] * m22;
  decimal_t rm10 = mat[1][0] * m00 + mat[1][1] * m10 + mat[1][2] * m20;
  decimal_t rm11 = mat[1][0] * m01 + mat[1][1] * m11 + mat[1][2] * m21;
  decimal_t rm12 = mat[1][0] * m02 + mat[1][1] * m12 + mat[1][2] * m22;
  decimal_t rm20 = mat[2][0] * m00 + mat[2][1] * m10 + mat[2][2] * m20;
  decimal_t rm21 = mat[2][0] * m01 + mat[2][1] * m11 + mat[2][2] * m21;
  decimal_t rm22 = mat[2][0] * m02 + mat[2][1] * m12 + mat[2][2] * m22;
  mat[0][0] = rm00;
  mat[0][1] = rm01;
  mat[0][2] = rm02;
  mat[1][0] = rm10;
  mat[1][1] = rm11;
  mat[1][2] = rm12;
  mat[2][0] = rm20;
  mat[2][1] = rm21;
  mat[2][2] = rm22;
}

constexpr Matrix2 maketransform(const Vec2<decimal_t>& t, decimal_t r, const Vec2<decimal_t>& s, const Vec2<decimal_t>& p,
                      TRSOrder trsOrder) {
  Matrix2 mat = Matrix2::identity();
  switch (trsOrder) {
    case TRSOrder::SRT:
      scale(mat, s);
      rotate(mat, r);
      translate(mat, t);
      break;
    case TRSOrder::STR:
      scale(mat, s);
      translate(mat, t);
      rotate(mat, r);
      break;
    case TRSOrder::RST:
      rotate(mat, r);
      scale(mat, s);
      translate(mat, t);
      break;
    case TRSOrder::RTS:
      rotate(mat, r);
      translate(mat, t);
      scale(mat, s);
      break;
    case TRSOrder::TSR:
      translate(mat, t);
      scale(mat, s);
      rotate(mat, r);
      break;
    case TRSOrder::TRS:
      translate(mat, t);
      rotate(mat, r);
      scale(mat, s);
      break;
  }
  translate(mat, p);
  return mat;
}

constexpr Matrix3 maketransform(const Vec3<decimal_t>& r, const Vec3<decimal_t>& s, TRSOrder trsOrder, EulerOrder eulerOrder) {
  Matrix3 mat = Matrix3::identity();
  switch(trsOrder) {
    case TRSOrder::SRT:
      scale(mat, s);
      rotate(mat, r, eulerOrder);
      break;
    case TRSOrder::STR:
      scale(mat, s);
      rotate(mat, r, eulerOrder);
      break;
    case TRSOrder::RST:
      rotate(mat, r, eulerOrder);
      scale(mat, s);
      break;
    case TRSOrder::RTS:
      rotate(mat, r, eulerOrder);
      scale(mat, s);
      break;
    case TRSOrder::TSR:
      translate(mat, r);
      scale(mat, s);
      break;
    case TRSOrder::TRS:
      translate(mat, r);
      scale(mat, s);
      break;
  }
  return mat;
}

constexpr Matrix4
maketransform(const Vec3<decimal_t>& t, const Vec3<decimal_t>& r, const Vec3<decimal_t>& s, const Vec3<decimal_t>& p,
              const Vec3<decimal_t>& pr, TRSOrder trsOrder, EulerOrder eulerOrder) {
  Matrix4 mat = Matrix4::identity();
  switch(trsOrder) {
    case TRSOrder::SRT:
      scale(mat, s);
      rotate(mat, r, eulerOrder);
      translate(mat, t);
      break;
    case TRSOrder::STR:
      scale(mat, s);
      translate(mat, t);
      rotate(mat, r, eulerOrder);
      break;
    case TRSOrder::RST:
      rotate(mat, r, eulerOrder);
      scale(mat, s);
      translate(mat, t);
      break;
    case TRSOrder::RTS:
      rotate(mat, r, eulerOrder);
      translate(mat, t);
      scale(mat, s);
      break;
    case TRSOrder::TSR:
      translate(mat, t);
      scale(mat, s);
      rotate(mat, r, eulerOrder);
      break;
    case TRSOrder::TRS:
      translate(mat, t);
      rotate(mat, r, eulerOrder);
      scale(mat, s);
      break;
  }
  translate(mat, p);
  rotate(mat, pr, eulerOrder);
  return mat;
}

constexpr Matrix3 maketransform(const Vec3<decimal_t>& forward, const Vec3<decimal_t>& up) {
  Matrix3 mat = Matrix3::identity();
  lookAt(mat, Vec3<decimal_t>::zero(), forward, up);
  return mat;
}

constexpr Matrix4 maketransform(const Vec3<decimal_t>& t, const Vec3<decimal_t>& forward, const Vec3<decimal_t>& up) {
  Matrix4 mat = Matrix4::identity();
  lookAt(mat, t, t + forward, up);
  return mat;
}

constexpr Vec3<decimal_t> ptransform(const Vec3<decimal_t>& pos, const Matrix3& mat) {
  // transform pos using row-major matrix mat
  return {pos.x * mat[0][0] + pos.y * mat[1][0] + pos.z * mat[2][0],
          pos.x * mat[0][1] + pos.y * mat[1][1] + pos.z * mat[2][1],
          pos.x * mat[0][2] + pos.y * mat[1][2] + pos.z * mat[2][2]};
}

constexpr Vec3<decimal_t> ptransform(const Vec3<decimal_t>& pos, const Matrix4& mat) {
  // transform pos using row-major matrix mat
  return {pos.x * mat[0][0] + pos.y * mat[1][0] + pos.z * mat[2][0] + mat[3][0],
          pos.x * mat[0][1] + pos.y * mat[1][1] + pos.z * mat[2][1] + mat[3][1],
          pos.x * mat[0][2] + pos.y * mat[1][2] + pos.z * mat[2][2] + mat[3][2]};
}

constexpr Vec3<decimal_t> ntransform(const Vec3<decimal_t>& normal, const Matrix3& mat) {
  // transform normal using row-major matrix mat
  return {normal.x * mat[0][0] + normal.y * mat[0][1] + normal.z * mat[0][2],
          normal.x * mat[1][0] + normal.y * mat[1][1] + normal.z * mat[1][2],
          normal.x * mat[2][0] + normal.y * mat[2][1] + normal.z * mat[2][2]};
}

constexpr Vec3<decimal_t> ntransform(const Vec3<decimal_t>& normal, const Matrix4& mat) {
  // transform normal using row-major matrix mat
  return {normal.x * mat[0][0] + normal.y * mat[0][1] + normal.z * mat[0][2],
          normal.x * mat[1][0] + normal.y * mat[1][1] + normal.z * mat[1][2],
          normal.x * mat[2][0] + normal.y * mat[2][1] + normal.z * mat[2][2]};
}

}
