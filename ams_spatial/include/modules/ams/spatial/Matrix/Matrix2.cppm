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

export module ams.spatial.Matrix2;
import <concepts>;
import <stdexcept>;
import ams;
import ams.spatial.internal;
import ams.spatial.Vec;

export namespace ams {

template<typename T>
concept Matrix2T = requires(T m) {
  { m[0][0] } -> std::convertible_to<decimal_t>;
  { m[0][1] } -> std::convertible_to<decimal_t>;
  { m[1][0] } -> std::convertible_to<decimal_t>;
  { m[1][1] } -> std::convertible_to<decimal_t>;
};

struct Matrix3;
struct Matrix4;

/**
 * @brief A 2x2 matrix. This is a row-major matrix.
 */
struct Matrix2 {
protected:
  Array<Array<decimal_t, 2>, 2> m{0};
public:
  /**
   * @brief Construct a new Matrix2 object.
   * All values are initialized to 0
   */
  constexpr Matrix2() = default;

  /**
   * @brief Construct a new Matrix2 object.
   * @param other - Matrix2 to copy
   */
  constexpr Matrix2(const Matrix2& other) = default;

  /**
   * @brief Construct a new Matrix2 object.
   * @param other - Matrix2 to move
   */
  constexpr Matrix2(Matrix2&& other) noexcept = default;

  /**
   * @brief Construct a new Matrix2 object
   * @param fill - The value to set all elements to
   */
  constexpr explicit Matrix2(decimal_t fill) : m{fill} {}

  /**
   * @brief Construct a new Matrix2 object
   * @param d00 - The value to set the first row, first column to
   * @param d01 - The value to set the first row, second column to
   * @param d10 - The value to set the second row, first column to
   * @param d11 - The value to set the second row, second column to
   */
  constexpr Matrix2(decimal_t d00, decimal_t d01, decimal_t d10, decimal_t d11)
    : m{d00, d01, d10, d11} {}

  ~Matrix2() = default;

  /**
   * @brief Construct a new Matrix2 object
   * @tparam M2T - Matrix2T type
   * @param m2 - Matrix2T to copy
   */
  template<Matrix2T M2T>
  constexpr explicit Matrix2(const M2T& m2)
    : m{m2[0][0], m2[0][1], m2[1][0], m2[1][1]} {}

  /**
   * @brief Construct a new Matrix2 object
   * @tparam V2T - Vec2T type
   * @param v1 - Vec2T to set the first row to
   * @param v2 - Vec2T to set the second row to
   */
  template<Vec2T V2T>
  constexpr Matrix2(const V2T& row1, const V2T& row2)
    : m{row1.x, row1.y, row2.x, row2.y} {}

  constexpr Array<decimal_t, 2>& operator[](int i) {
    return m[i];
  }

  constexpr const Array<decimal_t, 2>& operator[](int i) const {
    return m[i];
  }

  constexpr decimal_t operator()(int i, int j) const {
    if constexpr (AMSExceptions)
      if (i < 0 || i > 1 || j < 0 || j > 1)
        throw std::out_of_range("Matrix2 index out of range");
    return m[i][j];
  }

  constexpr Matrix2& operator=(const Matrix2& other) = default;

  constexpr Matrix2& operator=(Matrix2&& other) noexcept = default;

  template<Matrix2T M2T>
  constexpr Matrix2& operator=(const M2T& m2) {
    m[0][0] = m2[0][0];
    m[0][1] = m2[0][1];
    m[1][0] = m2[1][0];
    m[1][1] = m2[1][1];
    return *this;
  }

  constexpr Matrix2 operator*(const Matrix2& other) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0];
    result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1];
    result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0];
    result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1];
    return result;
  }

  constexpr Matrix2& operator*=(const Matrix2& other) {
    *this = *this * other;
    return *this;
  }

  template<Matrix2T M2T>
  constexpr Matrix2 operator*(const M2T& m2) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] * m2[0][0] + m[0][1] * m2[1][0];
    result.m[0][1] = m[0][0] * m2[0][1] + m[0][1] * m2[1][1];
    result.m[1][0] = m[1][0] * m2[0][0] + m[1][1] * m2[1][0];
    result.m[1][1] = m[1][0] * m2[0][1] + m[1][1] * m2[1][1];
    return result;
  }

  constexpr Matrix2 operator*(decimal_t scalar) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] * scalar;
    result.m[0][1] = m[0][1] * scalar;
    result.m[1][0] = m[1][0] * scalar;
    result.m[1][1] = m[1][1] * scalar;
    return result;
  }

  constexpr Matrix2& operator*=(decimal_t scalar) {
    m[0][0] *= scalar;
    m[0][1] *= scalar;
    m[1][0] *= scalar;
    m[1][1] *= scalar;
    return *this;
  }

  constexpr Matrix2 operator/(decimal_t scalar) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] / scalar;
    result.m[0][1] = m[0][1] / scalar;
    result.m[1][0] = m[1][0] / scalar;
    result.m[1][1] = m[1][1] / scalar;
    return result;
  }

  constexpr Matrix2& operator/=(decimal_t scalar) {
    *this = *this / scalar;
    return *this;
  }

  // vector operators

  template<Vec2T V2T>
  constexpr friend Matrix2 operator*(const Matrix2& mat, const V2T& row2) {
    return {mat.row(0) * row2, mat.row(1) * row2};
  }

  template<Vec2T V2T>
  friend V2T operator*(const V2T& v, const Matrix2& mat) {
    V2T ret = V2T();
    ret = dot<decimal_t>(v, mat.col(0)), dot(v, mat.col(1));
    return ret;
  }

  [[nodiscard]] constexpr Vec2<decimal_t> row(int i) const {
    return {m[i][0], m[i][1]};
  }

  [[nodiscard]] constexpr Vec2<decimal_t> col(int i) const {
    return {m[0][i], m[1][i]};
  }

  /**
   * @brief transposes the matrix in place
   */
  constexpr void transpose();

  /**
 * @brief transposes a Matrix2
 * @return the transposed matrix
 */
  [[nodiscard]] constexpr Matrix2 transposed() const;

  [[nodiscard]] constexpr decimal_t determinant() const;

  /**
   * @brief inverts the matrix in place
   * @return true if the matrix was successfully inverted
   * @return false if the matrix was not successfully inverted
   */
  constexpr bool invert();

  /**
   * @brief inverts a Matrix2
   * @return the inverted matrix
   */
  [[nodiscard]] constexpr Matrix2 inverted() const;
  
  constexpr void scale(decimal_t x, decimal_t y) {
    m[0][0] *= x;
    m[0][1] *= y;
    m[1][0] *= x;
    m[1][1] *= y;
  }
  
  constexpr void scale(const Vec2<decimal_t>& v) {
    scale(v.x, v.y);
  }
  
  constexpr void scale(decimal_t s) {
    scale(s, s);
  }
  
  constexpr void rotate(decimal_t angle) {
    decimal_t c = cos(angle);
    decimal_t s = sin(angle);
    decimal_t t = m[0][0];
    m[0][0] = c * t - s * m[1][0];
    m[1][0] = s * t + c * m[1][0];
    t = m[0][1];
    m[0][1] = c * t - s * m[1][1];
    m[1][1] = s * t + c * m[1][1];
  }
  
  constexpr void translate(decimal_t x, decimal_t y) {
    m[0][0] += m[1][0] * x;
    m[0][1] += m[1][1] * x;
    m[1][0] += m[1][0] * y;
    m[1][1] += m[1][1] * y;
  }

  static constexpr Matrix2 identity() {
    return {1, 0, 0, 1};
  }

  friend Matrix3;
  friend Matrix4;
};

} // ams
