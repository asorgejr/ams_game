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
#include "ams_spatial_export.hpp"
#include "../Vec.hpp"
/*[exclude end]*/
/*[ignore begin]*/
#include "ams_spatial_export.hpp"
/*[ignore end]*/
/*[export module ams.spatial.Matrix4]*/
/*[import <concepts>]*/
/*[import <stdexcept>]*/
/*[import ams]*/
/*[import ams.Array]*/
/*[import ams.spatial.internal]*/
/*[import ams.spatial.Vec]*/

/*[export]*/ namespace ams {

template<typename T>
concept Matrix4T = requires(T m) {
  { m[0][0] } -> std::convertible_to<decimal_t>;
  { m[0][1] } -> std::convertible_to<decimal_t>;
  { m[0][2] } -> std::convertible_to<decimal_t>;
  { m[0][3] } -> std::convertible_to<decimal_t>;
  { m[1][0] } -> std::convertible_to<decimal_t>;
  { m[1][1] } -> std::convertible_to<decimal_t>;
  { m[1][2] } -> std::convertible_to<decimal_t>;
  { m[1][3] } -> std::convertible_to<decimal_t>;
  { m[2][0] } -> std::convertible_to<decimal_t>;
  { m[2][1] } -> std::convertible_to<decimal_t>;
  { m[2][2] } -> std::convertible_to<decimal_t>;
  { m[2][3] } -> std::convertible_to<decimal_t>;
  { m[3][0] } -> std::convertible_to<decimal_t>;
  { m[3][1] } -> std::convertible_to<decimal_t>;
  { m[3][2] } -> std::convertible_to<decimal_t>;
  { m[3][3] } -> std::convertible_to<decimal_t>;
};

struct Quaternion;
struct Matrix2;
struct Matrix3;

/**
 * @brief 4x4 matrix. This is a row-major matrix.
 */
struct AMS_SPATIAL_EXPORT Matrix4 {
protected:
  Array<Array<decimal_t, 4>, 4> m{0};
public:
  constexpr Matrix4() = default;

  constexpr Matrix4(const Matrix4& m) = default;

  constexpr Matrix4(Matrix4&& m) noexcept = default;

  constexpr explicit Matrix4(decimal_t init) {
    m[0][0] = init;
    m[1][1] = init;
    m[2][2] = init;
    m[3][3] = init;
  }

  constexpr Matrix4(decimal_t d00, decimal_t d01, decimal_t d02, decimal_t d03,
                    decimal_t d10, decimal_t d11, decimal_t d12, decimal_t d13,
                    decimal_t d20, decimal_t d21, decimal_t d22, decimal_t d23,
                    decimal_t d30, decimal_t d31, decimal_t d32, decimal_t d33)
    : m{d00, d01, d02, d03,
        d10, d11, d12, d13,
        d20, d21, d22, d23,
        d30, d31, d32, d33} {}

  ~Matrix4() = default;

  template<Matrix4T M4T>
  constexpr explicit Matrix4(const M4T& m4)
    : m{m4[0][0], m4[0][1], m4[0][2], m4[0][3],
        m4[1][0], m4[1][1], m4[1][2], m4[1][3],
        m4[2][0], m4[2][1], m4[2][2], m4[2][3],
        m4[3][0], m4[3][1], m4[3][2], m4[3][3]} {}

  template<Vec4T V4T>
  constexpr Matrix4(const V4T& row1, const V4T& row2, const V4T& row3, const V4T& row4)
    : m{row1.x, row1.y, row1.z, row1.w,
        row2.x, row2.y, row2.z, row2.w,
        row3.x, row3.y, row3.z, row3.w,
        row4.x, row4.y, row4.z, row4.w} {}


  [[nodiscard]] constexpr Vec4<decimal_t> row(int i) const {
    return {m[i][0], m[i][1], m[i][2], m[i][3]};
  }

  [[nodiscard]] constexpr Vec4<decimal_t> col(int i) const {
    return {m[0][i], m[1][i], m[2][i], m[3][i]};
  }

  constexpr Array<decimal_t, 4>& operator[](int i) {
    return m[i];
  }

  constexpr Array<decimal_t, 4> operator[](int i) const {
    return m[i];
  }

  constexpr decimal_t operator()(int i, int j) const {
    return m[i][j];
  }

  constexpr Matrix4& operator=(const Matrix4& m) = default;

  constexpr Matrix4& operator=(Matrix4&& m) noexcept = default;

  constexpr Matrix4 operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.m[i][j] = this->m[i][0] * other.m[0][j] +
                         this->m[i][1] * other.m[1][j] +
                         this->m[i][2] * other.m[2][j] +
                         this->m[i][3] * other.m[3][j];
      }
    }
    return result;
  }

  constexpr Matrix4& operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
  }

  template<Matrix4T M4T>
  constexpr Matrix4 operator*(const M4T& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.m[i][j] = this->m[i][0] * other[0][j] +
                         this->m[i][1] * other[1][j] +
                         this->m[i][2] * other[2][j] +
                         this->m[i][3] * other[3][j];
      }
    }
    return result;
  }

  constexpr Matrix4 operator*(const Matrix3& other) const;

  constexpr Matrix4& operator*=(const Matrix3& other) {
    *this = *this * other;
    return *this;
  }

  constexpr Matrix4 operator*(decimal_t scalar) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.m[i][j] = this->m[i][j] * scalar;
      }
    }
    return result;
  }

  constexpr Matrix4& operator*=(decimal_t scalar) {
    *this = *this * scalar;
    return *this;
  }

  constexpr Matrix4 operator/(decimal_t scalar) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.m[i][j] = this->m[i][j] / scalar;
      }
    }
    return result;
  }

  constexpr Matrix4& operator/=(decimal_t scalar) {
    *this = *this / scalar;
    return *this;
  }

  template<Matrix4T M4T>
  constexpr Matrix4& operator*=(const M4T& other) {
    *this = *this * other;
    return *this;
  }

  template<Vec3T V3T>
  friend V3T operator*(const V3T& v, const Matrix4& mat) {
    V3T ret = V3T();
    ret.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.z * mat.m[0][2] + mat.m[0][3];
    ret.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.z * mat.m[1][2] + mat.m[1][3];
    ret.z = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.z * mat.m[2][2] + mat.m[2][3];
    return ret;
  }

  template<Vec4T V4T>
  friend V4T operator*(const V4T& v, const Matrix4& mat) {
    V4T ret = V4T();
    ret.x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + v.w * mat.m[3][0];
    ret.y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + v.w * mat.m[3][1];
    ret.z = v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + v.w * mat.m[3][2];
    ret.w = v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + v.w * mat.m[3][3];
    return ret;
  }

  template<Vec2T V2T>
  constexpr Matrix4& operator*=(const V2T& v) {
    *this = *this * v;
    return *this;
  }

  template<Vec3T V3T>
  constexpr Matrix4& operator*=(const V3T& v) {
    *this = *this * v;
    return *this;
  }

  template<Vec4T V4T>
  constexpr Matrix4& operator*=(const V4T& v) {
    *this = *this * v;
    return *this;
  }

  constexpr friend Vec2<decimal_t> operator*(const Vec2<decimal_t>& v2, const Matrix4& mat) {
    return {dot<decimal_t>(v2, mat.col(0).xy()), dot<decimal_t>(v2, mat.col(1).xy())};
  }

  constexpr friend Vec3<decimal_t> operator*(const Vec3<decimal_t>& v3, const Matrix4& mat) {
    return {dot<decimal_t>(v3, mat.col(0)), dot<decimal_t>(v3, mat.col(1)), dot<decimal_t>(v3, mat.col(2))};
  }

  constexpr friend Vec4<decimal_t> operator*(const Vec4<decimal_t>& v4, const Matrix4& mat) {
    return {dot<decimal_t>(v4, mat.col(0)), dot<decimal_t>(v4, mat.col(1)), dot<decimal_t>(v4, mat.col(2)),
            dot<decimal_t>(v4, mat.col(3))};
  }

  constexpr friend Matrix4 operator*(const Matrix4& mat, const Vec2<decimal_t>& v2) {
    auto r0 = mat.row(0);
    auto r1 = mat.row(1);
    auto r2 = mat.row(2);
    auto r3 = mat.row(3);
    return {r0.x * v2.x, r0.y * v2.y, r0.z, r0.w,
            r1.x * v2.x, r1.y * v2.y, r1.z, r1.w,
            r2.x * v2.x, r2.y * v2.y, r2.z, r2.w,
            r3.x * v2.x, r3.y * v2.y, r3.z, r3.w};
  }

  constexpr void transpose();

  [[nodiscard]] constexpr Matrix4 transposed() const;

  [[nodiscard]] constexpr decimal_t determinant() const;

  /**
   * @brief Inverts the Matrix4 in place.
   * @return true if the matrix was successfully inverted
   */
  [[maybe_unused]] constexpr bool invert();

  /**
   * @brief Inverts the Matrix4.
   * @return The inverse of the Matrix4
   */
  [[nodiscard]] constexpr Matrix4 inverted() const;

  /**
  * @brief Scales the matrix
  * @param x - x scale
  * @param y - y scale
  * @param z - z scale
  */
  constexpr void scale(decimal_t x, decimal_t y, decimal_t z) {
    // row-major operation. X is right, Y is up, Z is forward.
    m[0][0] *= x;
    m[1][1] *= y;
    m[2][2] *= z;
  }

  /**
   * @brief Scales the matrix
   * @param v - scale vector
   */
  constexpr void scale(const Vec3<decimal_t>& v) {
    scale(v.x, v.y, v.z);
  }

  /**
   * @brief Scales the matrix
   * @param s - uniform scale
   */
  constexpr void scale(decimal_t s) {
    scale(s, s, s);
  }
  
  /**
   * @brief Rotates the x axis of the matrix
   * @param angle - angle in radians
   */
  constexpr void rotatex(decimal_t angle) {
    // row-major operation. X is right, Y is up, Z is forward.
    decimal_t c = cos(angle);
    decimal_t s = sin(angle);
    decimal_t m10 = m[1][0];
    decimal_t m11 = m[1][1];
    decimal_t m12 = m[1][2];
    decimal_t m13 = m[1][3];
    decimal_t m20 = m[2][0];
    decimal_t m21 = m[2][1];
    decimal_t m22 = m[2][2];
    decimal_t m23 = m[2][3];
    m[1][0] = m10 * c + m20 * s;
    m[1][1] = m11 * c + m21 * s;
    m[1][2] = m12 * c + m22 * s;
    m[1][3] = m13 * c + m23 * s;
    m[2][0] = m20 * c - m10 * s;
    m[2][1] = m21 * c - m11 * s;
    m[2][2] = m22 * c - m12 * s;
    m[2][3] = m23 * c - m13 * s;
  }
  
  /**
   * @brief Rotates the y axis of the matrix
   * @param angle - angle in radians
   */
  constexpr void rotatey(decimal_t angle) {
    // row-major operation. X is right, Y is up, Z is forward.
    decimal_t c = cos(angle);
    decimal_t s = sin(angle);
    decimal_t m00 = m[0][0];
    decimal_t m01 = m[0][1];
    decimal_t m02 = m[0][2];
    decimal_t m03 = m[0][3];
    decimal_t m20 = m[2][0];
    decimal_t m21 = m[2][1];
    decimal_t m22 = m[2][2];
    decimal_t m23 = m[2][3];
    m[0][0] = m00 * c - m20 * s;
    m[0][1] = m01 * c - m21 * s;
    m[0][2] = m02 * c - m22 * s;
    m[0][3] = m03 * c - m23 * s;
    m[2][0] = m00 * s + m20 * c;
    m[2][1] = m01 * s + m21 * c;
    m[2][2] = m02 * s + m22 * c;
    m[2][3] = m03 * s + m23 * c;
  }
  
  /**
   * @brief Rotates the z axis of the matrix
   * @param angle - angle in radians
   */
  constexpr void rotatez(decimal_t angle) {
    // row-major operation. X is right, Y is up, Z is forward.
    decimal_t c = cos(angle);
    decimal_t s = sin(angle);
    decimal_t m00 = m[0][0];
    decimal_t m01 = m[0][1];
    decimal_t m02 = m[0][2];
    decimal_t m03 = m[0][3];
    decimal_t m10 = m[1][0];
    decimal_t m11 = m[1][1];
    decimal_t m12 = m[1][2];
    decimal_t m13 = m[1][3];
    m[0][0] = m00 * c + m10 * s;
    m[0][1] = m01 * c + m11 * s;
    m[0][2] = m02 * c + m12 * s;
    m[0][3] = m03 * c + m13 * s;
    m[1][0] = m10 * c - m00 * s;
    m[1][1] = m11 * c - m01 * s;
    m[1][2] = m12 * c - m02 * s;
    m[1][3] = m13 * c - m03 * s;
  }
  
  /**
   * @brief Rotates the matrix using an axis and angle
   * @param axis_x - x component of the axis
   * @param axis_y - y component of the axis
   * @param axis_z - z component of the axis
   * @param angle - angle in radians
   */
  constexpr void rotate(decimal_t axis_x, decimal_t axis_y, decimal_t axis_z, decimal_t angle) {
    // row-major operation. X is right, Y is up, Z is forward.
    decimal_t c = cos(angle);
    decimal_t s = sin(angle);
    decimal_t t = 1 - c;
    decimal_t x = axis_x;
    decimal_t y = axis_y;
    decimal_t z = axis_z;
    decimal_t tx = t * x;
    decimal_t ty = t * y;
    decimal_t m00 = m[0][0];
    decimal_t m01 = m[0][1];
    decimal_t m02 = m[0][2];
    decimal_t m03 = m[0][3];
    decimal_t m10 = m[1][0];
    decimal_t m11 = m[1][1];
    decimal_t m12 = m[1][2];
    decimal_t m13 = m[1][3];
    decimal_t m20 = m[2][0];
    decimal_t m21 = m[2][1];
    decimal_t m22 = m[2][2];
    decimal_t m23 = m[2][3];
    m[0][0] = tx * x + c;
    m[0][1] = tx * y + s * z;
    m[0][2] = tx * z - s * y;
    m[0][3] = 0;
    m[1][0] = tx * y - s * z;
    m[1][1] = ty * y + c;
    m[1][2] = ty * z + s * x;
    m[1][3] = 0;
    m[2][0] = tx * z + s * y;
    m[2][1] = ty * z - s * x;
    m[2][2] = t * z * z + c;
    m[2][3] = 0;
    m[3][0] = m00 * m[0][0] + m10 * m[0][1] + m20 * m[0][2];
    m[3][1] = m01 * m[0][0] + m11 * m[0][1] + m21 * m[0][2];
    m[3][2] = m02 * m[0][0] + m12 * m[0][1] + m22 * m[0][2];
    m[3][3] = m03 * m[0][0] + m13 * m[0][1] + m23 * m[0][2];
  }
  
  /**
   * @brief Rotates the matrix using an axis and angle
   * @param axis - axis
   * @param angle - angle in radians
   */
  constexpr void rotate(const Vec3<decimal_t>& axis, decimal_t angle) {
    rotate(axis.x, axis.y, axis.z, angle);
  }
  
  /**
   * @brief Rotates the matrix using a quaternion
   * @param q - quaternion
   */
  constexpr void rotate(const Quaternion& q);
  
  /**
   * @brief Translates the matrix
   * @param x - x component of the translation
   * @param y - y component of the translation
   * @param z - z component of the translation
   */
  constexpr void translate(decimal_t x, decimal_t y, decimal_t z) {
    m[3][0] += x;
    m[3][1] += y;
    m[3][2] += z;
  }
  
  /**
   * @brief Translates the matrix
   * @param v - translation vector
   */
  constexpr void translate(const Vec3<decimal_t>& v) {
    translate(v.x, v.y, v.z);
  }
  
  /**
   * @brief Shears the matrix
   * @param x - x component of the shear
   * @param y - y component of the shear
   * @param z - z component of the shear
   */
  constexpr void shear(decimal_t x, decimal_t y, decimal_t z) {
    // row-major operation. X is right, Y is up, Z is forward.
    decimal_t m00 = m[0][0];
    decimal_t m01 = m[0][1];
    decimal_t m02 = m[0][2];
    decimal_t m03 = m[0][3];
    decimal_t m10 = m[1][0];
    decimal_t m11 = m[1][1];
    decimal_t m12 = m[1][2];
    decimal_t m13 = m[1][3];
    m[0][0] += m10 * x;
    m[0][1] += m11 * x;
    m[0][2] += m12 * x;
    m[0][3] += m13 * x;
    m[1][0] += m00 * y;
    m[1][1] += m01 * y;
    m[1][2] += m02 * y;
    m[1][3] += m03 * y;
    m[2][0] += m00 * z;
    m[2][1] += m01 * z;
    m[2][2] += m02 * z;
    m[2][3] += m03 * z;
  }
  
  /**
   * @brief Shears the matrix
   * @param v - shear vector
   */
  constexpr void shear(const Vec3<decimal_t>& v) {
    shear(v.x, v.y, v.z);
  }

  constexpr static Matrix4 identity() {
    return {1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
  }

  friend Matrix2;
  friend Matrix3;
};

} // ams
