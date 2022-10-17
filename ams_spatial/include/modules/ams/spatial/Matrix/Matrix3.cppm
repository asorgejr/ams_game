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

export module ams.spatial.Matrix3;
import <concepts>;
import <stdexcept>;
import ams;
import ams.Array;
import ams.spatial.internal;
import ams.spatial.Vec;

export namespace ams {

template<typename T>
concept Matrix3T = requires(T m) {
  { m[0][0] } -> std::convertible_to<decimal_t>;
  { m[0][1] } -> std::convertible_to<decimal_t>;
  { m[0][2] } -> std::convertible_to<decimal_t>;
  { m[1][0] } -> std::convertible_to<decimal_t>;
  { m[1][1] } -> std::convertible_to<decimal_t>;
  { m[1][2] } -> std::convertible_to<decimal_t>;
  { m[2][0] } -> std::convertible_to<decimal_t>;
  { m[2][1] } -> std::convertible_to<decimal_t>;
  { m[2][2] } -> std::convertible_to<decimal_t>;
};

struct Quaternion;
struct Matrix2;
struct Matrix4;

/**
 * @brief a row-major 3x3 Matrix. Y is up, X is right, and Z is forward.
 */
struct Matrix3 {
protected:
  Array<Array<decimal_t, 3>, 3> m{0};
public:
  /**
   * @brief Construct a new Matrix3 object
   * All elements are set to 0
   */
  constexpr Matrix3() = default;

  /**
   * @brief Construct a new Matrix3 object
   * @param other - Matrix3 to copy
   */
  constexpr Matrix3(const Matrix3& other) = default;

  /**
   * @brief Construct a new Matrix3 object
   * @param other - Matrix3 to move
   */
  constexpr Matrix3(Matrix3&& other) noexcept = default;

  /**
   * @brief Construct a new Matrix3 object
   * @param fill - The value to set all elements to
   */
  constexpr explicit Matrix3(decimal_t fill) : m{fill} {}

  constexpr Matrix3(decimal_t d00, decimal_t d01, decimal_t d02,
                    decimal_t d10, decimal_t d11, decimal_t d12,
                    decimal_t d20, decimal_t d21, decimal_t d22)
    : m{d00, d01, d02,
        d10, d11, d12,
        d20, d21, d22} {}

  ~Matrix3() = default;

  template<Matrix3T M3T>
  constexpr explicit Matrix3(const M3T& m3)
    : m{m3[0][0], m3[0][1], m3[0][2],
        m3[1][0], m3[1][1], m3[1][2],
        m3[2][0], m3[2][1], m3[2][2]} {}

  template<Vec3T V3T>
  constexpr Matrix3(const V3T& row1, const V3T& row2, const V3T& row3)
    : m{row1.x, row1.y, row1.z,
        row2.x, row2.y, row2.z,
        row3.x, row3.y, row3.z} {}
        
  
  constexpr explicit Matrix3(const Matrix4& m4);
  
  constexpr explicit Matrix3(const Quaternion& q);

  constexpr Array<decimal_t, 3>& operator[](int i) {
    return m[i];
  }

  constexpr Array<decimal_t, 3> operator[](int i) const {
    return m[i];
  }

  constexpr decimal_t operator()(int i, int j) const {
    return m[i][j];
  }

  constexpr Matrix3& operator=(const Matrix3& m) = default;

  constexpr Matrix3& operator=(Matrix3&& m) noexcept = default;

  template<Matrix3T M3T>
  constexpr Matrix3& operator=(const M3T& m3) {
    m[0][0] = m3[0][0];
    m[0][1] = m3[0][1];
    m[0][2] = m3[0][2];
    m[1][0] = m3[1][0];
    m[1][1] = m3[1][1];
    m[1][2] = m3[1][2];
    m[2][0] = m3[2][0];
    m[2][1] = m3[2][1];
    m[2][2] = m3[2][2];
    return *this;
  }

  constexpr Matrix3 operator*(const Matrix3& other) const {
    Matrix3 result;
    result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0];
    result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1];
    result.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2];
    result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0];
    result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1];
    result.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2];
    result.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0];
    result.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1];
    result.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2];
    return result;
  }

  constexpr Matrix3& operator*=(const Matrix3& other) {
    *this = *this * other;
    return *this;
  }
  
  constexpr Matrix3 operator*(decimal_t scalar) const {
    Matrix3 result;
    result.m[0][0] = m[0][0] * scalar;
    result.m[0][1] = m[0][1] * scalar;
    result.m[0][2] = m[0][2] * scalar;
    result.m[1][0] = m[1][0] * scalar;
    result.m[1][1] = m[1][1] * scalar;
    result.m[1][2] = m[1][2] * scalar;
    result.m[2][0] = m[2][0] * scalar;
    result.m[2][1] = m[2][1] * scalar;
    result.m[2][2] = m[2][2] * scalar;
    return result;
  }

  constexpr Matrix3& operator*=(decimal_t scalar) {
    *this = *this * scalar;
    return *this;
  }

  constexpr Matrix3 operator/(decimal_t scalar) const {
    Matrix3 result;
    result.m[0][0] = m[0][0] / scalar;
    result.m[0][1] = m[0][1] / scalar;
    result.m[0][2] = m[0][2] / scalar;
    result.m[1][0] = m[1][0] / scalar;
    result.m[1][1] = m[1][1] / scalar;
    result.m[1][2] = m[1][2] / scalar;
    result.m[2][0] = m[2][0] / scalar;
    result.m[2][1] = m[2][1] / scalar;
    result.m[2][2] = m[2][2] / scalar;
    return result;
  }

  constexpr Matrix3& operator/=(decimal_t scalar) {
    *this = *this / scalar;
    return *this;
  }

  template<Matrix3T M3T>
  constexpr Matrix3 operator*(const M3T& m3) const {
    Matrix3 result;
    result.m[0][0] = m[0][0] * m3[0][0] + m[0][1] * m3[1][0] + m[0][2] * m3[2][0];
    result.m[0][1] = m[0][0] * m3[0][1] + m[0][1] * m3[1][1] + m[0][2] * m3[2][1];
    result.m[0][2] = m[0][0] * m3[0][2] + m[0][1] * m3[1][2] + m[0][2] * m3[2][2];
    result.m[1][0] = m[1][0] * m3[0][0] + m[1][1] * m3[1][0] + m[1][2] * m3[2][0];
    result.m[1][1] = m[1][0] * m3[0][1] + m[1][1] * m3[1][1] + m[1][2] * m3[2][1];
    result.m[1][2] = m[1][0] * m3[0][2] + m[1][1] * m3[1][2] + m[1][2] * m3[2][2];
    result.m[2][0] = m[2][0] * m3[0][0] + m[2][1] * m3[1][0] + m[2][2] * m3[2][0];
    result.m[2][1] = m[2][0] * m3[0][1] + m[2][1] * m3[1][1] + m[2][2] * m3[2][1];
    result.m[2][2] = m[2][0] * m3[0][2] + m[2][1] * m3[1][2] + m[2][2] * m3[2][2];
    return result;
  }

  template<Matrix3T M3T>
  constexpr Matrix3& operator*=(const M3T& m3) {
    *this = *this * m3;
    return *this;
  }


  template<Vec3T V3T>
  constexpr friend Matrix3 operator*(const Matrix3& mat, const V3T& v) {
    // row-major operation. Y is up.
    return {
      mat.m[0][0] * v[0] + mat.m[0][1] * v[1] + mat.m[0][2] * v[2],
      mat.m[1][0] * v[0] + mat.m[1][1] * v[1] + mat.m[1][2] * v[2],
      mat.m[2][0] * v[0] + mat.m[2][1] * v[1] + mat.m[2][2] * v[2]
    };
  }

  template<Vec3T V3T>
  friend V3T operator*(const V3T& v, const Matrix3& mat) {
    // row-major operation. Y is up. v is lhs
    return {
      v[0] * mat.m[0][0] + v[1] * mat.m[1][0] + v[2] * mat.m[2][0],
      v[0] * mat.m[0][1] + v[1] * mat.m[1][1] + v[2] * mat.m[2][1],
      v[0] * mat.m[0][2] + v[1] * mat.m[1][2] + v[2] * mat.m[2][2]
    };
  }

  [[nodiscard]] constexpr Vec3<decimal_t> row(int i) const {
    return {m[i][0], m[i][1], m[i][2]};
  }

  [[nodiscard]] constexpr Vec3<decimal_t> col(int i) const {
    return {m[0][i], m[1][i], m[2][i]};
  }

  /**
   * @brief transposes a matrix in place
   */
  constexpr void transpose();

  /**
   * @brief transposes a Matrix3
   * @return the transposed matrix
   */
  [[nodiscard]] constexpr Matrix3 transposed() const;

  [[nodiscard]] constexpr decimal_t determinant() const;

  /**
   * @brief inverts a matrix in place
   * @return 
   */
  constexpr bool invert();

  /**
   * @brief inverts a Matrix3
   * @return the inverted matrix
   */
  [[nodiscard]] constexpr Matrix3 inverted() const;
  
  constexpr void scale(decimal_t x, decimal_t y, decimal_t z) {
    // row-major operation. Y is up.
    m[0][0] *= x;
    m[0][1] *= y;
    m[0][2] *= z;
    m[1][0] *= x;
    m[1][1] *= y;
    m[1][2] *= z;
    m[2][0] *= x;
    m[2][1] *= y;
    m[2][2] *= z;
  }
  
  constexpr void scale(const Vec3<decimal_t>& v) {
    scale(v.x, v.y, v.z);
  }
  
  constexpr void scale(decimal_t s) {
    scale(s, s, s);
  }

  constexpr void rotatex(decimal_t angle) {
    // row-major operation. Y is up.
    decimal_t s = sin(angle);
    decimal_t c = cos(angle);
    decimal_t m1 = m[1][0];
    decimal_t m2 = m[2][0];
    m[1][0] = m1 * c + m2 * s;
    m[2][0] = m2 * c - m1 * s;
    m1 = m[1][1];
    m2 = m[2][1];
    m[1][1] = m1 * c + m2 * s;
    m[2][1] = m2 * c - m1 * s;
    m1 = m[1][2];
    m2 = m[2][2];
    m[1][2] = m1 * c + m2 * s;
    m[2][2] = m2 * c - m1 * s;
  }

  constexpr void rotatey(decimal_t angle) {
    // row-major operation. Y is up.
    decimal_t s = sin(angle);
    decimal_t c = cos(angle);
    decimal_t m0 = m[0][0];
    decimal_t m2 = m[2][0];
    m[0][0] = m0 * c - m2 * s;
    m[2][0] = m2 * c + m0 * s;
    m0 = m[0][1];
    m2 = m[2][1];
    m[0][1] = m0 * c - m2 * s;
    m[2][1] = m2 * c + m0 * s;
    m0 = m[0][2];
    m2 = m[2][2];
    m[0][2] = m0 * c - m2 * s;
    m[2][2] = m2 * c + m0 * s;
  }

  constexpr void rotatez(decimal_t angle) {
    // row-major operation. Y is up, Z is forward.
    decimal_t s = sin(angle);
    decimal_t c = cos(angle);
    decimal_t m0 = m[0][0];
    decimal_t m1 = m[1][0];
    m[0][0] = m0 * c + m1 * s;
    m[1][0] = m1 * c - m0 * s;
    m0 = m[0][1];
    m1 = m[1][1];
    m[0][1] = m0 * c + m1 * s;
    m[1][1] = m1 * c - m0 * s;
    m0 = m[0][2];
    m1 = m[1][2];
    m[0][2] = m0 * c + m1 * s;
    m[1][2] = m1 * c - m0 * s;
  }

  constexpr void rotate(decimal_t axis_x, decimal_t axis_y, decimal_t axis_z, decimal_t angle) {
    // row-major operation. X is right, Y is up, Z is forward. 
    decimal_t s = sin(angle);
    decimal_t c = cos(angle);
    decimal_t k = 1 - c;
    decimal_t m0 = m[0][0];
    decimal_t m1 = m[1][0];
    decimal_t m2 = m[2][0];
    decimal_t m3 = m[0][1];
    decimal_t m4 = m[1][1];
    decimal_t m5 = m[2][1];
    decimal_t m6 = m[0][2];
    decimal_t m7 = m[1][2];
    decimal_t m8 = m[2][2];
    decimal_t t0 = axis_x * axis_x * k + c;
    decimal_t t1 = axis_y * axis_x * k + axis_z * s;
    decimal_t t2 = axis_z * axis_x * k - axis_y * s;
    decimal_t t3 = axis_x * axis_y * k - axis_z * s;
    decimal_t t4 = axis_y * axis_y * k + c;
    decimal_t t5 = axis_z * axis_y * k + axis_x * s;
    decimal_t t6 = axis_x * axis_z * k + axis_y * s;
    decimal_t t7 = axis_y * axis_z * k - axis_x * s;
    decimal_t t8 = axis_z * axis_z * k + c;
    m[0][0] = m0 * t0 + m1 * t3 + m2 * t6;
    m[1][0] = m0 * t1 + m1 * t4 + m2 * t7;
    m[2][0] = m0 * t2 + m1 * t5 + m2 * t8;
    m[0][1] = m3 * t0 + m4 * t3 + m5 * t6;
    m[1][1] = m3 * t1 + m4 * t4 + m5 * t7;
    m[2][1] = m3 * t2 + m4 * t5 + m5 * t8;
    m[0][2] = m6 * t0 + m7 * t3 + m8 * t6;
    m[1][2] = m6 * t1 + m7 * t4 + m8 * t7;
  }

  constexpr void rotate(const Vec3 <decimal_t>& axis, decimal_t angle) {
    this->rotate(axis.x, axis.y, axis.z, angle);
  }
  
  constexpr void rotate(const Quaternion& q) {
    *this *= Matrix3(q);
  }

  [[nodiscard]] constexpr static Matrix3 identity() {
    return {1, 0, 0, 0, 1, 0, 0, 0, 1};
  }
  
  [[nodiscard]] static constexpr Matrix3 fromaxes(const Vec3<decimal_t>& forward, const Vec3<decimal_t>& up) {
    Vec3<decimal_t> right = cross(forward, up);
    return {right.x, right.y, right.z, up.x, up.y, up.z, forward.x, forward.y, forward.z};
  }


  friend Matrix2;
  friend Matrix4;
  //
};

} // ams
