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
/*[module]*/
/*[exclude begin]*/
#pragma once
#include <ams/Array.hpp>
#include "Vec.hpp"
#include "Matrix/Matrix2.hpp"
#include "Matrix/Matrix3.hpp"
#include "Matrix/Matrix4.hpp"
/*[exclude end]*/
/*[ignore begin]*/
#include <concepts>
/*[ignore end]*/
/*[export module ams.spatial.Matrix]*/
/*[import <stdexcept>]*/
/*[import ams]*/
/*[import ams.Array]*/
/*[import ams.spatial.internal]*/
/*[import ams.spatial.Vec]*/
/*[export import ams.spatial.Matrix2]*/
/*[export import ams.spatial.Matrix3]*/
/*[export import ams.spatial.Matrix4]*/

/*[export]*/namespace ams {

// Concepts for Matrix types
// Requirements are the type must have a double-bracket operator: [][]


enum class EulerOrder {
  XYZ,
  XZY,
  YXZ,
  YZX,
  ZXY,
  ZYX
};

enum class TRSOrder {
  SRT,
  STR,
  RST,
  RTS,
  TSR,
  TRS
};

struct Quaternion;


#pragma region Funcs

/**
 * @brief Creates a Matrix2 from a set of rows
 * @param row1 - The first row
 * @param row2 - The second row
 * @return The Matrix2 created from the rows
 */
constexpr Matrix2 fromRows(const Vec2<decimal_t>& row1, const Vec2<decimal_t>& row2) {
  return {row1.x, row1.y, row2.x, row2.y};
}

/**
 * @brief Creates a Matrix3 from a set of rows
 * @param row1 - The first row
 * @param row2 - The second row
 * @param row3 - The third row
 * @return The Matrix3 created from the rows
 */
constexpr Matrix3 fromRows(const Vec3<decimal_t>& row1, const Vec3<decimal_t>& row2,
                           const Vec3<decimal_t>& row3) {
  return {row1.x, row1.y, row1.z, row2.x, row2.y, row2.z, row3.x, row3.y, row3.z};
}

/**
 * @brief Creates a Matrix4 from a set of rows
 * @param row1 - The first row
 * @param row2 - The second row
 * @param row3 - The third row
 * @param row4 - The fourth row
 * @return The Matrix4 created from the rows
 */
constexpr Matrix4 fromRows(const Vec4<decimal_t>& row1, const Vec4<decimal_t>& row2,
                           const Vec4<decimal_t>& row3, const Vec4<decimal_t>& row4) {
  return {row1.x, row1.y, row1.z, row1.w,
          row2.x, row2.y, row2.z, row2.w,
          row3.x, row3.y, row3.z, row3.w,
          row4.x, row4.y, row4.z, row4.w};
}


/**
 * @brief Creates a Matrix2 from a set of columns
 * @param col1 - The first column
 * @param col2 - The second column
 * @return The Matrix2 created from the columns
 */
constexpr Matrix2 fromCols(const Vec2<decimal_t>& col1, const Vec2<decimal_t>& col2) {
  return {col1.x, col2.x, col1.y, col2.y};
}

/**
 * @brief Creates a Matrix3 from a set of columns
 * @param col1 - The first column
 * @param col2 - The second column
 * @param col3 - The third column
 * @return The Matrix3 created from the columns
 */
constexpr Matrix3 fromCols(const Vec3<decimal_t>& col1, const Vec3<decimal_t>& col2,
                           const Vec3<decimal_t>& col3) {
  return {col1.x, col2.x, col3.x, col1.y, col2.y, col3.y, col1.z, col2.z, col3.z};
}

/**
 * @brief Creates a Matrix4 from a set of columns
 * @param col1 - The first column
 * @param col2 - The second column
 * @param col3 - The third column
 * @param col4 - The fourth column
 * @return The Matrix4 created from the columns
 */
constexpr Matrix4 fromCols(const Vec4<decimal_t>& col1, const Vec4<decimal_t>& col2,
                           const Vec4<decimal_t>& col3, const Vec4<decimal_t>& col4) {
  return {col1.x, col2.x, col3.x, col4.x,
          col1.y, col2.y, col3.y, col4.y,
          col1.z, col2.z, col3.z, col4.z,
          col1.w, col2.w, col3.w, col4.w};
}


/**
 * @brief Creates a Matrix3 from a Quaternion
 * @param q - The Quaternion to create the Matrix3 from
 * @return The Matrix3 created from the Quaternion
 */
constexpr Matrix3 fromQuaternion(const Vec4<decimal_t>& q) {
  decimal_t x = q.x;
  decimal_t y = q.y;
  decimal_t z = q.z;
  decimal_t w = q.w;
  decimal_t x2 = x * x;
  decimal_t y2 = y * y;
  decimal_t z2 = z * z;
  decimal_t w2 = w * w;
  return {w2 + x2 - y2 - z2, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y,
          2 * x * y + 2 * w * z, w2 - x2 + y2 - z2, 2 * y * z - 2 * w * x,
          2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, w2 - x2 - y2 + z2};
}

/**
 * @brief Creates a Matrix3 from a Quaternion
 * @tparam TVec4 - The type of the Quaternion
 * @param q - The Quaternion to create the Matrix3 from
 * @return The Matrix3 created from the Quaternion
 */
template<Vec4T TVec4>
constexpr Matrix3 fromQuaternion(const TVec4& q) {
  return fromQuaternion(Vec4<decimal_t>(q));
}

/**
 * @brief Extracts a Quaternion from a Matrix3
 * @param mat - The Matrix3 to extract the Quaternion from
 * @return The Quaternion extracted from the Matrix3
 */
constexpr Vec4<decimal_t> toQuaternion(const Matrix3& mat) {
  decimal_t trace = mat(0, 0) + mat(1, 1) + mat(2, 2);
  if (trace > 0) {
    decimal_t s = 0.5 / sqrt(trace + 1.0);
    return {s * (mat(2, 1) - mat(1, 2)), s * (mat(0, 2) - mat(2, 0)), s * (mat(1, 0) - mat(0, 1)), 0.25 / s};
  } else if (mat(0, 0) > mat(1, 1) && mat(0, 0) > mat(2, 2)) {
    decimal_t s = 2.0 * sqrt(1.0 + mat(0, 0) - mat(1, 1) - mat(2, 2));
    return {(mat(2, 1) - mat(1, 2)) / s, (mat(0, 1) + mat(1, 0)) / s, (mat(0, 2) + mat(2, 0)) / s, (mat(1, 2) - mat(2, 1)) / s};
  } else if (mat(1, 1) > mat(2, 2)) {
    decimal_t s = 2.0 * sqrt(1.0 + mat(1, 1) - mat(0, 0) - mat(2, 2));
    return {(mat(0, 2) - mat(2, 0)) / s, (mat(0, 1) + mat(1, 0)) / s, (mat(1, 2) + mat(2, 1)) / s, (mat(2, 0) - mat(0, 2)) / s};
  } else {
    decimal_t s = 2.0 * sqrt(1.0 + mat(2, 2) - mat(0, 0) - mat(1, 1));
    return {(mat(1, 0) - mat(0, 1)) / s, (mat(0, 2) + mat(2, 0)) / s, (mat(1, 2) + mat(2, 1)) / s,
            (mat(0, 1) - mat(1, 0)) / s};
  }
}


/**
 * @brief Creates a Matrix3 from euler anglesr
 * @param x - Pitch (x-axis rotation)
 * @param y - Yaw (y-axis rotation)
 * @param z - Roll (z-axis rotation)
 * @param is_degrees - Whether the angles are in degrees
 * @return The Matrix3 created from the euler angles
 */
constexpr Matrix3 fromEulerAngles(decimal_t x, decimal_t y, decimal_t z, bool is_degrees=false) {
  if (is_degrees) {
    x = radians(x);
    y = radians(y);
    z = radians(z);
  }
  // pitch (x-axis rotation)
  decimal_t sx = -sin(x);
  decimal_t cx = cos(x);
  // yaw (y-axis rotation)
  decimal_t sy = -sin(y);
  decimal_t cy = cos(y);
  // roll (z-axis rotation)
  decimal_t sz = -sin(z);
  decimal_t cz = cos(z);
  
  // calculate rotation matrix elements
  decimal_t m00 = cy * cz;
  decimal_t m01 = -cy * sz;
  decimal_t m02 = sy;
  decimal_t m10 = cz * sx * sy + cx * sz;
  decimal_t m11 = cx * cz - sx * sy * sz;
  decimal_t m12 = -cy * sx;
  decimal_t m20 = -cx * cz * sy + sx * sz;
  decimal_t m21 = cz * sx + cx * sy * sz;
  decimal_t m22 = cx * cy;
  
  return {m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22};
}

/**
 * @brief Creates a Matrix3 from euler angles
 * @param angles - The euler angles
 * @param is_degrees - Whether the angles are in degrees
 * @return The Matrix3 created from the euler angles
 */
constexpr Matrix3 fromEulerAngles(const Vec3<decimal_t>& angles, bool is_degrees=false) {
  return fromEulerAngles(angles.x, angles.y, angles.z, is_degrees);
}

/**
 * @brief Extracts the euler angles from a Matrix3
 * @param mat - The Matrix3 to extract the euler angles from
 * @param is_degrees - Whether to return the euler angles in degrees
 * @return The euler angles extracted from the Matrix3
 */
constexpr Vec3<decimal_t> toEulerAngles(const Matrix3& mat, bool is_degrees=false) {
  decimal_t x, y, z;
  decimal_t m00 = mat[0][0];
  decimal_t m01 = mat[0][1];
  decimal_t m02 = mat[0][2];
  decimal_t m10 = mat[1][0];
  decimal_t m11 = mat[1][1];
  decimal_t m12 = mat[1][2];
  decimal_t m20 = mat[2][0];
  decimal_t m21 = mat[2][1];
  decimal_t m22 = mat[2][2];

  // pitch (x-axis rotation)
  decimal_t sx = -m12;
  x = asin(sx);
  decimal_t cx = cos(x);

  if (abs(cx) > 0.0005) {
    // yaw (y-axis rotation)
    decimal_t sy = -m02 / cx;
    decimal_t cy = m22 / cx;
    y = atan2(sy, cy);

    // roll (z-axis rotation)
    decimal_t sz = -m10 / cx;
    decimal_t cz = m11 / cx;
    z = atan2(sz, cz);
  } else {
    // yaw (y-axis rotation)
    decimal_t sy = -m20;
    decimal_t cy = m00;
    y = atan2(sy, cy);

    // roll (z-axis rotation)
    z = 0;
  }

  if (is_degrees) {
    x = degrees(x);
    y = degrees(y);
    z = degrees(z);
  }
  
  return {x, y, z};
}

/**
 * @brief Extracts the euler angles from a Matrix3
 * @param mat - The Matrix3 to extract the euler angles from
 * @return The euler angles extracted from the Matrix3
 */
constexpr Vec3<decimal_t> toEulerAngles1(const Matrix3& mat) {
  // calculate from row-major rotation matrix (i, j), y-up
  // pitch (x-axis rotation)
  decimal_t x = atan2(mat(2, 1), mat(2, 2));
  // yaw (y-axis rotation)
  decimal_t y = asin(mat(2, 0));
  // roll (z-axis rotation)
  decimal_t z = atan2(-mat(1, 0), mat(0, 0));
  return {x, y, z};
}


/**
 * @brief Scales the matrix by the given vector
 * @param mat - The matrix to scale
 * @param v - The vector to scale by
 */
constexpr void scale(Matrix2& mat, const Vec2<decimal_t>& v) {
  mat[0][0] *= v.x;
  mat[0][1] *= v.y;
  mat[1][0] *= v.x;
  mat[1][1] *= v.y;
}

/**
 * @brief Scales the matrix by the given value
 * @param mat - The matrix to scale
 * @param d - The value to scale by
 */
constexpr void scale(Matrix2& mat, decimal_t d) {
  mat[0][0] *= d;
  mat[0][1] *= d;
  mat[1][0] *= d;
  mat[1][1] *= d;
}

/**
 * @brief Scales the matrix by the given vector
 * @param mat - The matrix to scale
 * @param v - The vector to scale by
 */
constexpr void scale(Matrix3& mat, const Vec3<decimal_t>& v) {
  mat[0][0] *= v.x;
  mat[0][1] *= v.x;
  mat[0][2] *= v.x;
  mat[1][0] *= v.y;
  mat[1][1] *= v.y;
  mat[1][2] *= v.y;
  mat[2][0] *= v.z;
  mat[2][1] *= v.z;
  mat[2][2] *= v.z;
}

/**
 * @brief Scales the matrix by the given value
 * @param mat - The matrix to scale
 * @param d - The value to scale by
 */
constexpr void scale(Matrix3& mat, decimal_t d) {
  mat[0][0] *= d;
  mat[0][1] *= d;
  mat[0][2] *= d;
  mat[1][0] *= d;
  mat[1][1] *= d;
  mat[1][2] *= d;
  mat[2][0] *= d;
  mat[2][1] *= d;
  mat[2][2] *= d;
}

/**
 * @brief Scales the matrix by the given vector
 * @param mat - The matrix to scale
 * @param v - The vector to scale by
 */
constexpr void scale(Matrix4& mat, const Vec3<decimal_t>& v) {
  mat[0][0] *= v.x;
  mat[0][1] *= v.x;
  mat[0][2] *= v.x;
  mat[0][3] *= v.x;
  mat[1][0] *= v.y;
  mat[1][1] *= v.y;
  mat[1][2] *= v.y;
  mat[1][3] *= v.y;
  mat[2][0] *= v.z;
  mat[2][1] *= v.z;
  mat[2][2] *= v.z;
  mat[2][3] *= v.z;
}

/**
 * @brief Scales the matrix by the given value
 * @param mat - The matrix to scale
 * @param d - The value to scale by
 */
constexpr void scale(Matrix4& mat, decimal_t d) {
  mat[0][0] *= d;
  mat[0][1] *= d;
  mat[0][2] *= d;
  mat[0][3] *= d;
  mat[1][0] *= d;
  mat[1][1] *= d;
  mat[1][2] *= d;
  mat[1][3] *= d;
  mat[2][0] *= d;
  mat[2][1] *= d;
  mat[2][2] *= d;
  mat[2][3] *= d;
  mat[3][0] *= d;
  mat[3][1] *= d;
  mat[3][2] *= d;
  mat[3][3] *= d;
}


/**
 * @brief Rotates a matrix by a given angle
 * @param mat - The matrix to rotate
 * @param angle - The angle to rotate by
 */
constexpr void rotate(Matrix2& mat, decimal_t angle) {
  decimal_t c = cos(angle);
  decimal_t s = sin(angle);
  decimal_t m00 = mat[0][0] * c + mat[0][1] * s;
  decimal_t m01 = mat[0][0] * -s + mat[0][1] * c;
  decimal_t m10 = mat[1][0] * c + mat[1][1] * s;
  decimal_t m11 = mat[1][0] * -s + mat[1][1] * c;
  mat[0][0] = m00;
  mat[0][1] = m01;
  mat[1][0] = m10;
  mat[1][1] = m11;
}

/**
 * Rotates the matrix by the given angle around the given axis, combining the rotation with the given matrix
 * @param mat - the matrix to rotate
 * @param angle - the angle in radians
 * @param axis - the axis to rotate around
 */
constexpr void rotate(Matrix3& mat, decimal_t angle, const Vec3<decimal_t>& axis) {
  decimal_t c = cos(angle);
  decimal_t s = sin(angle);
  decimal_t t = 1 - c;
  decimal_t x = axis.x;
  decimal_t y = axis.y;
  decimal_t z = axis.z;
  decimal_t tx = t * x;
  decimal_t ty = t * y;
  decimal_t m00 = tx * x + c;
  decimal_t m01 = tx * y + s * z;
  decimal_t m02 = tx * z - s * y;
  decimal_t m10 = tx * y - s * z;
  decimal_t m11 = ty * y + c;
  decimal_t m12 = ty * z + s * x;
  decimal_t m20 = tx * z + s * y;
  decimal_t m21 = ty * z - s * x;
  decimal_t m22 = t * z * z + c;
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

/**
 * Rotates the matrix by the given angle around the given axis, combining the rotation with the given matrix
 * @param mat - the matrix to rotate
 * @param angle - the angle in radians
 * @param axis - the axis to rotate around
 */
constexpr void rotate(Matrix4& mat, decimal_t angle, const Vec3<decimal_t>& axis) {
  decimal_t c = cos(angle);
  decimal_t s = sin(angle);
  decimal_t t = 1 - c;
  decimal_t x = axis.x;
  decimal_t y = axis.y;
  decimal_t z = axis.z;
  decimal_t tx = t * x;
  decimal_t ty = t * y;
  decimal_t m00 = tx * x + c;
  decimal_t m01 = tx * y + s * z;
  decimal_t m02 = tx * z - s * y;
  decimal_t m10 = tx * y - s * z;
  decimal_t m11 = ty * y + c;
  decimal_t m12 = ty * z + s * x;
  decimal_t m20 = tx * z + s * y;
  decimal_t m21 = ty * z - s * x;
  decimal_t m22 = t * z * z + c;
  decimal_t rm00 = mat[0][0] * m00 + mat[0][1] * m10 + mat[0][2] * m20;
  decimal_t rm01 = mat[0][0] * m01 + mat[0][1] * m11 + mat[0][2] * m21;
  decimal_t rm02 = mat[0][0] * m02 + mat[0][1] * m12 + mat[0][2] * m22;
  decimal_t rm10 = mat[1][0] * m00 + mat[1][1] * m10 + mat[1][2] * m20;
  decimal_t rm11 = mat[1][0] * m01 + mat[1][1] * m11 + mat[1][2] * m21;
  decimal_t rm12 = mat[1][0] * m02 + mat[1][1] * m12 + mat[1][2] * m22;
  decimal_t rm20 = mat[2][0] * m00 + mat[2][1] * m10 + mat[2][2] * m20;
  decimal_t rm21 = mat[2][0] * m01 + mat[2][1] * m11 + mat[2][2] * m21;
  decimal_t rm22 = mat[2][0] * m02 + mat[2][1] * m12 + mat[2][2] * m22;
  decimal_t rm30 = mat[3][0] * m00 + mat[3][1] * m10 + mat[3][2] * m20;
  decimal_t rm31 = mat[3][0] * m01 + mat[3][1] * m11 + mat[3][2] * m21;
  decimal_t rm32 = mat[3][0] * m02 + mat[3][1] * m12 + mat[3][2] * m22;
  mat[0][0] = rm00;
  mat[0][1] = rm01;
  mat[0][2] = rm02;
  mat[1][0] = rm10;
  mat[1][1] = rm11;
  mat[1][2] = rm12;
  mat[2][0] = rm20;
  mat[2][1] = rm21;
  mat[2][2] = rm22;
  mat[3][0] = rm30;
  mat[3][1] = rm31;
  mat[3][2] = rm32;
}

/**
 * @brief Rotates a matrix by a euler angle
 * @param mat - The matrix to rotate
 * @param eulerAngles - The euler rotation to apply
 * @param order - The order in which to rotate
 */
constexpr void rotate(Matrix3& mat, const Vec3<decimal_t>& eulerAngles, EulerOrder order) {
  switch (order) {
    case EulerOrder::XYZ:
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      break;
    case EulerOrder::XZY:
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      break;
    case EulerOrder::YXZ:
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      break;
    case EulerOrder::YZX:
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      break;
    case EulerOrder::ZXY:
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      break;
    case EulerOrder::ZYX:
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      break;
  }
}

/**
 * @brief Rotates a matrix by a quaternion
 * @param mat - The matrix to rotate
 * @param quat - The quaternion to rotate by
 */
constexpr void rotate(Matrix3& mat, const Quaternion& quat);

/**
 * @brief Rotates a matrix by a euler angle
 * @param mat - The matrix to rotate
 * @param eulerAngles - The euler rotation to apply
 * @param order - The order in which to rotate
 */
constexpr void rotate(Matrix4& mat, const Vec3<decimal_t>& eulerAngles, EulerOrder order) {
  switch (order) {
    case EulerOrder::XYZ:
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      break;
    case EulerOrder::XZY:
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      break;
    case EulerOrder::YXZ:
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      break;
    case EulerOrder::YZX:
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      break;
    case EulerOrder::ZXY:
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      break;
    case EulerOrder::ZYX:
      rotate(mat, eulerAngles.x, Vec3<decimal_t>::right());
      rotate(mat, eulerAngles.y, Vec3<decimal_t>::up());
      rotate(mat, eulerAngles.z, Vec3<decimal_t>::forward());
      break;
  }
}

/**
 * @brief Rotates a matrix by a quaternion
 * @param mat - The matrix to rotate
 * @param quat - The quaternion to rotate by
 */
constexpr void rotate(Matrix4& mat, const Quaternion& quat);


/**
 * @brief Translates a matrix by a given vector
 * @param mat - The matrix to translate
 * @param t - The translation vector
 */
constexpr void translate(Matrix2& mat, const Vec2<decimal_t>& t) {
  mat[0][0] += t.x;
  mat[1][1] += t.y;
}

/**
 * @brief Translates a matrix by a given vector
 * @param mat - The matrix to translate
 * @param t - The translation vector
 */
constexpr void translate(Matrix3& mat, const Vec3<decimal_t>& t) {
  mat[0][0] += t.x;
  mat[1][1] += t.y;
  mat[2][2] += t.z;
}

/**
 * @brief Translates a matrix by a given vector
 * @param mat - The matrix to translate
 * @param t - The translation vector
 */
constexpr void translate(Matrix4& mat, const Vec3<decimal_t>& t) {
  mat[0][0] += t.x;
  mat[1][1] += t.y;
  mat[2][2] += t.z;
}


/**
 * @brief Gets the diagonal of a Matrix2
 * @param mat - The Matrix2 to get the diagonal of
 * @return - The diagonal of the Matrix2
 */
constexpr Vec2<decimal_t> diagonal(const Matrix2& mat) {
  return {mat[0][0], mat[1][1]};
}

/**
 * @brief Gets the diagonal of a Matrix3
 * @param mat - The Matrix3 to get the diagonal of
 * @return - The diagonal of the Matrix3
 */
constexpr Vec3<decimal_t> diagonal(const Matrix3& mat) {
  return { mat[0][0], mat[1][1], mat[2][2] };
}

/**
 * @brief Gets the diagonal of a Matrix4
 * @param mat - The Matrix4 to get the diagonal of
 * @return - The diagonal of the Matrix4
 */
constexpr Vec3<decimal_t> diagonal(const Matrix4& mat) {
  return { mat[0][0], mat[1][1], mat[2][2] };
}


/**
 * @brief Gets the trace of a Matrix2
 * @param mat - The Matrix2 to get the trace of
 * @details The trace of a matrix is the sum of the diagonal elements
 * @return - The trace of the Matrix2
 */
constexpr decimal_t trace(const Matrix2& mat) {
  return mat[0][0] + mat[1][1];
}

/**
 * @brief Gets the trace of a Matrix3
 * @param mat - The Matrix3 to get the trace of
 * @details The trace of a matrix is the sum of the diagonal elements
 * @return - The trace of the Matrix3
 */
constexpr decimal_t trace(const Matrix3& mat) {
  return mat[0][0] + mat[1][1] + mat[2][2];
}

/**
 * @brief Gets the trace of a Matrix4
 * @param mat - The Matrix4 to get the trace of
 * @details The trace of a matrix is the sum of the diagonal elements
 * @return - The trace of the Matrix4
 */
constexpr decimal_t trace(const Matrix4& mat) {
  return mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3];
}


/**
 * @brief Gets the determinant of a Matrix2.
 * @param mat - The matrix to get the determinant of
 * @details A determinant is a value that can be computed from the elements of a
 * square matrix and encodes certain properties of the linear transformation 
 * described by the matrix.
 * @return - The determinant of the Matrix2
 */
constexpr decimal_t determinant(const Matrix2& mat) {
  return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

/**
 * @brief Gets the determinant of a Matrix3.
 * @param mat - The matrix to get the determinant of
 * @details A determinant is a value that can be computed from the elements of a
 * square matrix and encodes certain properties of the linear transformation 
 * described by the matrix.
 * @return - The determinant of the Matrix3
 */
constexpr decimal_t determinant(const Matrix3& mat) {
  return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
         mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
         mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

/**
 * @brief Gets the determinant of a Matrix4.
 * @param mat - The matrix to get the determinant of
 * @details A determinant is a value that can be computed from the elements of a
 * square matrix and encodes certain properties of the linear transformation 
 * described by the matrix.
 * @return - The determinant of the Matrix4
 */
constexpr decimal_t determinant(const Matrix4& mat) {
  return mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) -
                      mat[1][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) +
                      mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])) -
         mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) -
                      mat[1][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) +
                      mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])) +
         mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) -
                      mat[1][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) +
                      mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) -
         mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) -
                      mat[1][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]) +
                      mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
}


/**
 * @brief Gets the transpose of a Matrix2
 * @param mat - The Matrix2 to transpose
 * @details The transpose of a matrix is an operator which flips a matrix over its diagonal
 * @return - The transposed Matrix2
 */
constexpr void transpose(Matrix2& mat) {
  std::swap(mat[0][1], mat[1][0]);
}

/**
 * @brief Gets the transpose of a Matrix3
 * @param mat - The Matrix3 to transpose
 * @details The transpose of a matrix is an operator which flips a matrix over its diagonal
 * @return - The transposed Matrix3
 */
constexpr void transpose(Matrix3& mat) {
  std::swap(mat[0][1], mat[1][0]);
  std::swap(mat[0][2], mat[2][0]);
  std::swap(mat[1][2], mat[2][1]);
}

/**
 * @brief Gets the transpose of a Matrix4
 * @param mat - The Matrix4 to transpose
 * @details The transpose of a matrix is an operator which flips a matrix over its diagonal
 * @return - The transposed Matrix4
 */
constexpr void transpose(Matrix4& mat) {
  std::swap(mat[0][1], mat[1][0]);
  std::swap(mat[0][2], mat[2][0]);
  std::swap(mat[0][3], mat[3][0]);
  std::swap(mat[1][2], mat[2][1]);
  std::swap(mat[1][3], mat[3][1]);
  std::swap(mat[2][3], mat[3][2]);
}


/**
 * @brief Gets the cofactor of a Matrix2
 * @param mat - The Matrix2 to get the cofactor of
 * @param row - The row to get the cofactor of
 * @param col - The column to get the cofactor of
 * @details The cofactor of an element of a square matrix is the determinant of the
 * minor matrix obtained by deleting the row and column of the element.
 * @return - The cofactor of the Matrix2
 */
constexpr decimal_t cofactor(const Matrix2& mat, int row, int col) {
  return mat[(row + 1) % 2][(col + 1) % 2];
}

/**
 * @brief Gets the cofactor of a Matrix3
 * @param mat - The Matrix3 to get the cofactor of
 * @param row - The row to get the cofactor of
 * @param col - The column to get the cofactor of
 * @details The cofactor of an element of a square matrix is the determinant of the
 * minor matrix obtained by deleting the row and column of the element.
 * @return - The cofactor of the Matrix3
 */
constexpr decimal_t cofactor(const Matrix3& mat, int row, int col) {
  Matrix2 minor;
  int r = 0;
  for (int i = 0; i < 3; i++) {
    if (i == row) continue;
    int c = 0;
    for (int j = 0; j < 3; j++) {
      if (j == col) continue;
      minor[r][c] = mat[i][j];
      c++;
    }
    r++;
  }
  return determinant(minor);
}

/**
 * @brief Gets the cofactor of a Matrix4
 * @param mat - The Matrix4 to get the cofactor of
 * @param row - The row to get the cofactor of
 * @param col - The column to get the cofactor of
 * @details The cofactor of an element of a square matrix is the determinant of the
 * minor matrix obtained by deleting the row and column of the element.
 * @return - The cofactor of the Matrix4
 */
constexpr decimal_t cofactor(const Matrix4& mat, int row, int col) {
  Matrix3 minor;
  int r = 0;
  for (int i = 0; i < 4; i++) {
    if (i == row) continue;
    int c = 0;
    for (int j = 0; j < 4; j++) {
      if (j == col) continue;
      minor[r][c] = mat[i][j];
      c++;
    }
    r++;
  }
  return determinant(minor);
}


/**
 * @brief Gets the adjoint of a Matrix2
 * @param mat - The Matrix2 to get the adjoint of
 * @details The adjoint of a matrix is the transpose of the cofactor matrix
 * @return - The adjoint of the Matrix2
 */
constexpr Matrix2 adjoint(const Matrix2& mat) {
  Matrix2 result = Matrix2(
    cofactor(mat, 0, 0), -cofactor(mat, 0, 1),
    -cofactor(mat, 1, 0), cofactor(mat, 1, 1)
  );
  transpose(result);
  return result;
}

/**
 * @brief Gets the adjoint of a Matrix3
 * @param mat - The Matrix3 to get the adjoint of
 * @details The adjoint of a matrix is the transpose of the cofactor matrix
 * @return - The adjoint of the Matrix3
 */
constexpr Matrix3 adjoint(const Matrix3& mat) {
  Matrix3 result = Matrix3(
    cofactor(mat, 0, 0), -cofactor(mat, 0, 1), cofactor(mat, 0, 2),
    -cofactor(mat, 1, 0), cofactor(mat, 1, 1), -cofactor(mat, 1, 2),
    cofactor(mat, 2, 0), -cofactor(mat, 2, 1), cofactor(mat, 2, 2)
  );
  transpose(result);
  return result;
}

/**
 * @brief Gets the adjoint of a Matrix4
 * @param mat - The Matrix4 to get the adjoint of
 * @details The adjoint of a matrix is the transpose of the cofactor matrix
 * @return - The adjoint of the Matrix4
 */
constexpr Matrix4 adjoint(const Matrix4& mat) {
  Matrix4 result = Matrix4(
    cofactor(mat, 0, 0), -cofactor(mat, 0, 1), cofactor(mat, 0, 2), -cofactor(mat, 0, 3),
    -cofactor(mat, 1, 0), cofactor(mat, 1, 1), -cofactor(mat, 1, 2), cofactor(mat, 1, 3),
    cofactor(mat, 2, 0), -cofactor(mat, 2, 1), cofactor(mat, 2, 2), -cofactor(mat, 2, 3),
    -cofactor(mat, 3, 0), cofactor(mat, 3, 1), -cofactor(mat, 3, 2), cofactor(mat, 3, 3)
  );
  transpose(result);
  return result;
}


/**
 * @brief inverts a Matrix2
 * @param mat - the Matrix2 to invert
 * @details Inverts a matrix by finding the adjoint and dividing by the determinant
 * @return true if the Matrix2 was successfully inverted, false if determinant is 0
 */
[[maybe_unused]]
constexpr bool inverse(Matrix2& mat) {
  decimal_t det = determinant(mat);
  if (det == 0) {
    if (AMSExceptions)
      throw std::domain_error("Matrix2 is singular");
    else {
      mat = Matrix2(0);
      return false;
    }
  }
  mat = adjoint(mat) / det;
  return true;
}

/**
 * @brief inverts a Matrix3
 * @param mat - the matrix to invert
 * @return true if the matrix was successfully inverted, false if determinant is 0
 */
[[maybe_unused]]
constexpr bool inverse(Matrix3& mat) {
  decimal_t det = determinant(mat);
  if (det == 0) {
    if (AMSExceptions)
      throw std::domain_error("Matrix3 is singular");
    else {
      mat = Matrix3(0);
      return false;
    }
  }
  mat = adjoint(mat) / det;
  return true;
}

/**
 * @brief inverts a Matrix4
 * @param mat - the matrix to invert
 * @return true if the matrix was successfully inverted, false if determinant is 0
 */
[[maybe_unused]]
constexpr bool inverse(Matrix4& mat) {
  decimal_t det = determinant(mat);
  if (det == 0) {
    if (AMSExceptions)
      throw std::domain_error("Matrix4 is singular");
    else {
      mat = Matrix4(0);
      return false;
    }
  }
  mat = adjoint(mat) / det;
  return true;
}



constexpr void perspective(Matrix3& mat, decimal_t fovy, decimal_t aspect,
                           decimal_t near, decimal_t far) {
  decimal_t f = safe_div(1, tan(fovy / 2));
  mat[0][0] = safe_div(f, aspect);
  mat[1][1] = f;
  mat[2][2] = safe_div(far + near, far - near);
  mat[2][3] = -1;
  mat[3][2] = safe_div(2 * far * near, far - near);
  mat[3][3] = 0;
}

constexpr void perspective(Matrix4& mat, decimal_t fov, decimal_t aspect,
                           decimal_t near, decimal_t far) {
  decimal_t f = safe_div(1, tan(fov / 2));
  mat[0][0] = safe_div(f, aspect);
  mat[1][1] = f;
  mat[2][2] = safe_div(far + near, far - near);
  mat[2][3] = -1;
  mat[3][2] = safe_div(2 * far * near, far - near);
  mat[3][3] = 0;
}


constexpr void orthographic(Matrix3& mat, decimal_t left, decimal_t right, decimal_t bottom,
                            decimal_t top, decimal_t near, decimal_t far) {
  mat[0][0] = safe_div(2, right - left);
  mat[1][1] = safe_div(2, top - bottom);
  mat[2][2] = safe_div(-2, far - near);
  mat[3][0] = safe_div(-(right + left), right - left);
  mat[3][1] = safe_div(-(top + bottom), top - bottom);
  mat[3][2] = safe_div(-(far + near), far - near);
}

constexpr void orthographic(Matrix4& mat, decimal_t left, decimal_t right, decimal_t bottom,
                            decimal_t top, decimal_t near, decimal_t far) {
  mat[0][0] = safe_div(2, right - left);
  mat[1][1] = safe_div(2, top - bottom);
  mat[2][2] = safe_div(-2, far - near);
  mat[3][0] = safe_div(-(right + left), right - left);
  mat[3][1] = safe_div(-(top + bottom), top - bottom);
  mat[3][2] = safe_div(-(far + near), far - near);
}

/**
 * @brief Creates a look at matrix
 * @param mat - The matrix to modify
 * @param pos - The position of the camera
 * @param target - The target of the camera
 * @param up - The up vector of the camera
 * @param reversed - Whether the lookat is reversed
 */
constexpr void lookAt(Matrix3& mat, const Vec3<decimal_t>& pos, const Vec3<decimal_t>& target,
                      const Vec3<decimal_t>& up, bool reversed = false) {
  Vec3<decimal_t> f = normalize(target - pos); // f - forward
  Vec3<decimal_t> s = normalize(cross(f, up)); // s - side
  Vec3<decimal_t> u = cross(s, f); // u - up
  // row-major matrix3
  if (reversed) {
    mat[0][0] = s.x;
    mat[0][1] = u.x;
    mat[0][2] = -f.x;
    mat[1][0] = s.y;
    mat[1][1] = u.y;
    mat[1][2] = -f.y;
    mat[2][0] = s.z;
    mat[2][1] = u.z;
    mat[2][2] = -f.z;
  } else {
    mat[0][0] = s.x;
    mat[0][1] = u.x;
    mat[0][2] = f.x;
    mat[1][0] = s.y;
    mat[1][1] = u.y;
    mat[1][2] = f.y;
    mat[2][0] = s.z;
    mat[2][1] = u.z;
    mat[2][2] = f.z;
  }
}

constexpr void lookAt(Matrix4& mat, const Vec3<decimal_t>& pos, const Vec3<decimal_t>& target,
                      const Vec3<decimal_t>& up, bool reversed = false) {
  Vec3<decimal_t> f = normalize(target - pos);
  Vec3<decimal_t> s = normalize(cross(f, up));
  Vec3<decimal_t> u = cross(s, f);
  if (reversed) {
    mat[0][0] = s.x;
    mat[0][1] = s.y;
    mat[0][2] = s.z;
    mat[1][0] = u.x;
    mat[1][1] = u.y;
    mat[1][2] = u.z;
    mat[2][0] = -f.x;
    mat[2][1] = -f.y;
    mat[2][2] = -f.z;
  } else {
    mat[0][0] = s.x;
    mat[0][1] = u.x;
    mat[0][2] = -f.x;
    mat[1][0] = s.y;
    mat[1][1] = u.y;
    mat[1][2] = -f.y;
    mat[2][0] = s.z;
    mat[2][1] = u.z;
    mat[2][2] = -f.z;
  }
}


constexpr void frustum(Matrix3& mat, decimal_t left, decimal_t right, decimal_t bottom,
                       decimal_t top, decimal_t near, decimal_t far) {
  mat[0][0] = 2 * safe_div(near, right - left);
  mat[1][1] = 2 * safe_div(near, top - bottom);
  mat[2][0] = safe_div(right + left, right - left);
  mat[2][1] = safe_div(top + bottom, top - bottom);
  mat[2][2] = safe_div(far + near, far - near);
  mat[2][3] = -1;
  mat[3][2] = safe_div(2 * far * near, far - near);
  mat[3][3] = 0;
}

constexpr void frustum(Matrix4& mat, decimal_t left, decimal_t right, decimal_t bottom,
                       decimal_t top, decimal_t near, decimal_t far) {
  mat[0][0] = safe_div(2 * near, right - left);
  mat[1][1] = safe_div(2 * near, top - bottom);
  mat[2][0] = safe_div(right + left, right - left);
  mat[2][1] = safe_div(top + bottom, top - bottom);
  mat[2][2] = safe_div(far + near, far - near);
  mat[2][3] = -1;
  mat[3][2] = safe_div(2 * far * near, far - near);
  mat[3][3] = 0;
}


constexpr Matrix2 maketransform(const Vec2<decimal_t>& t, decimal_t r, const Vec2<decimal_t>& s,
                                const Vec2<decimal_t>& p, TRSOrder trsOrder);

constexpr Matrix3 maketransform(const Vec3<decimal_t>& r, const Vec3<decimal_t>& s,
                                TRSOrder trsOrder, EulerOrder eulerOrder);

constexpr Matrix4 maketransform(const Vec3<decimal_t>& t, const Vec3<decimal_t>& r,
                                const Vec3<decimal_t>& s, const Vec3<decimal_t>& p,
                                const Vec3<decimal_t>& pr, TRSOrder trsOrder, EulerOrder eulerOrder);

constexpr Matrix3 maketransform(const Vec3<decimal_t>& forward, const Vec3<decimal_t>& up);

constexpr Matrix4 maketransform(const Vec3<decimal_t>& t, const Vec3<decimal_t>& forward,
                                const Vec3<decimal_t>& up);


constexpr Vec3<decimal_t> ptransform(const Vec3<decimal_t>& pos, const Matrix3& mat);

constexpr Vec3<decimal_t> ptransform(const Vec3<decimal_t>& pos, const Matrix4& mat);

constexpr Vec3<decimal_t> ntransform(const Vec3<decimal_t>& normal, const Matrix3& mat);

constexpr Vec3<decimal_t> ntransform(const Vec3<decimal_t>& normal, const Matrix4& mat);

#pragma endregion Funcs

// end
} // namespace ams
