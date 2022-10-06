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
/*[exclude begin]*/
#pragma once
#include "Vec.hpp"
/*[exclude end]*/
/*[export module ams.Matrix]*/
/*[import <concepts>]*/
/*[import ams.Vec]*/

/*[export]*/namespace ams {

// Concepts for Matrix types
// Requirements are the type must have a double-bracket operator: [][]

template <typename T>
concept Matrix2T = requires(T m) {
  { m[0][0] } -> std::convertible_to<double>;
  { m[0][1] } -> std::convertible_to<double>;
  { m[1][0] } -> std::convertible_to<double>;
  { m[1][1] } -> std::convertible_to<double>;
};

template <typename T>
concept Matrix3T = requires(T m) {
  { m[0][0] } -> std::convertible_to<double>;
  { m[0][1] } -> std::convertible_to<double>;
  { m[0][2] } -> std::convertible_to<double>;
  { m[1][0] } -> std::convertible_to<double>;
  { m[1][1] } -> std::convertible_to<double>;
  { m[1][2] } -> std::convertible_to<double>;
  { m[2][0] } -> std::convertible_to<double>;
  { m[2][1] } -> std::convertible_to<double>;
  { m[2][2] } -> std::convertible_to<double>;
};

template <typename T>
concept Matrix4T = requires(T m) {
  { m[0][0] } -> std::convertible_to<double>;
  { m[0][1] } -> std::convertible_to<double>;
  { m[0][2] } -> std::convertible_to<double>;
  { m[0][3] } -> std::convertible_to<double>;
  { m[1][0] } -> std::convertible_to<double>;
  { m[1][1] } -> std::convertible_to<double>;
  { m[1][2] } -> std::convertible_to<double>;
  { m[1][3] } -> std::convertible_to<double>;
  { m[2][0] } -> std::convertible_to<double>;
  { m[2][1] } -> std::convertible_to<double>;
  { m[2][2] } -> std::convertible_to<double>;
  { m[2][3] } -> std::convertible_to<double>;
  { m[3][0] } -> std::convertible_to<double>;
  { m[3][1] } -> std::convertible_to<double>;
  { m[3][2] } -> std::convertible_to<double>;
  { m[3][3] } -> std::convertible_to<double>;
};


struct Matrix3;
struct Matrix4;

struct Matrix2 {
protected:
  double m[2][2] = {0};
public:
  Matrix2() = default;
  
  Matrix2(const Matrix2& other) = default;

  Matrix2(Matrix2&& m2) noexcept = default;

  explicit Matrix2(double d) {
    m[0][0] = d;
    m[1][1] = d;
  }

  Matrix2(double d1, double d2, double d3, double d4) {
    m[0][0] = d1;
    m[0][1] = d2;
    m[1][0] = d3;
    m[1][1] = d4;
  }

  ~Matrix2() = default;

  template<Matrix2T M2T> explicit Matrix2(const M2T& m2) {
    m[0][0] = m2[0][0];
    m[0][1] = m2[0][1];
    m[1][0] = m2[1][0];
    m[1][1] = m2[1][1];
  }

  template<Vec2T V2T> Matrix2(const V2T& v1, const V2T& v2) {
    m[0][0] = v1.x;
    m[0][1] = v1.y;
    m[1][0] = v2.x;
    m[1][1] = v2.y;
  }

  [[nodiscard]] Vec2<double> row(int i) const {
    return {m[i][0], m[i][1]};
  }

  [[nodiscard]] Vec2<double> col(int i) const {
    return {m[0][i], m[1][i]};
  }

  double *operator[](int i) {
    return m[i];
  }

  double operator()(int i, int j) const {
    return m[i][j];
  }

  Matrix2& operator=(const Matrix2& other) = default;

  Matrix2& operator=(Matrix2&& other) noexcept = default;
  
  template<Matrix2T M2T> Matrix2& operator=(const M2T& m2) {
    m[0][0] = m2[0][0];
    m[0][1] = m2[0][1];
    m[1][0] = m2[1][0];
    m[1][1] = m2[1][1];
    return *this;
  }

  Matrix2 operator*(const Matrix2& other) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0];
    result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1];
    result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0];
    result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1];
    return result;
  }

  Matrix2& operator*=(const Matrix2& other) {
    *this = *this * other;
    return *this;
  }
  
  template<Matrix2T M2T> Matrix2 operator*(const M2T& m2) const {
    Matrix2 result;
    result.m[0][0] = m[0][0] * m2[0][0] + m[0][1] * m2[1][0];
    result.m[0][1] = m[0][0] * m2[0][1] + m[0][1] * m2[1][1];
    result.m[1][0] = m[1][0] * m2[0][0] + m[1][1] * m2[1][0];
    result.m[1][1] = m[1][0] * m2[0][1] + m[1][1] * m2[1][1];
    return result;
  }
  
  // vector operators

  template<Vec2T V2T> friend Matrix2 operator*(const Matrix2& mat, const V2T& v2) {
    return {mat.row(0) * v2, mat.row(1) * v2};
  }

  template<Vec2T V2T> friend V2T operator*(const V2T& v, const Matrix2& mat) {
    V2T ret = V2T();
    ret = dot<double>(v, mat.col(0)), dot(v, mat.col(1));
    return ret;
  }

  friend Matrix3;
  friend Matrix4;
};

struct Matrix3 {
protected:
  double m[3][3] = {0};
public:
  Matrix3() = default;

  Matrix3(const Matrix3& m) = default;

  Matrix3(Matrix3&& m) noexcept = default;
  
  explicit Matrix3(double init) {
    m[0][0] = init;
    m[1][1] = init;
    m[2][2] = init;
  }
  
  Matrix3(double m00, double m01, double m02,
          double m10, double m11, double m12,
          double m20, double m21, double m22)
  {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
  }

  ~Matrix3() = default;
  
  template<Matrix3T M3T> explicit Matrix3(const M3T& m3) {
    m[0][0] = m3[0][0];
    m[0][1] = m3[0][1];
    m[0][2] = m3[0][2];
    m[1][0] = m3[1][0];
    m[1][1] = m3[1][1];
    m[1][2] = m3[1][2];
    m[2][0] = m3[2][0];
    m[2][1] = m3[2][1];
    m[2][2] = m3[2][2];
  }
  
  template<Vec3T V3T> Matrix3(const V3T& v1, const V3T& v2, const V3T& v3) {
    m[0][0] = v1.x;
    m[0][1] = v1.y;
    m[0][2] = v1.z;
    m[1][0] = v2.x;
    m[1][1] = v2.y;
    m[1][2] = v2.z;
    m[2][0] = v3.x;
    m[2][1] = v3.y;
    m[2][2] = v3.z;
  }

  
  [[nodiscard]] Vec3<double> row(int i) const {
    return {m[i][0], m[i][1], m[i][2]};
  }

  [[nodiscard]] Vec3<double> col(int i) const {
    return {m[0][i], m[1][i], m[2][i]};
  }

  double *operator[](int i) {
    return m[i];
  }

  double operator()(int i, int j) const {
    return m[i][j];
  }
  
  Matrix3& operator=(const Matrix3& m) = default;
  
  Matrix3& operator=(Matrix3&& m) noexcept = default;
  
  template<Matrix3T M3T> Matrix3& operator=(const M3T& m3) {
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
  
  Matrix3 operator*(const Matrix3& other) const {
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

  Matrix3& operator*=(const Matrix3& other) {
    *this = *this * other;
    return *this;
  }
  
  template<Matrix3T M3T> Matrix3 operator*(const M3T& m3) const {
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
  
  template<Matrix3T M3T> Matrix3& operator*=(const M3T& m3) {
    *this = *this * m3;
    return *this;
  }

  
  template<Vec3T V3T> friend Matrix3 operator*(const Matrix3& mat, const V3T& v3) {
    return {mat.row(0) * v3, mat.row(1) * v3, mat.row(2) * v3};
  }
  
  template<Vec3T V3T> friend V3T operator*(const V3T& v, const Matrix3& mat) {
    V3T ret = V3T();
    ret = dot<double>(v, mat.col(0)), dot<double>(v, mat.col(1)), dot<double>(v, mat.col(2));
    return ret;
  }

  friend Matrix2;
  friend Matrix4;
  //
};


struct Matrix4 {
protected:
  double m[4][4] = {0};
public:
  Matrix4() = default;

  Matrix4(const Matrix4& m) = default;

  Matrix4(Matrix4&& m) noexcept = default;
  
  explicit Matrix4(double init) {
    m[0][0] = init;
    m[1][1] = init;
    m[2][2] = init;
    m[3][3] = init;
  }
  
  Matrix4(double m00, double m01, double m02, double m03,
          double m10, double m11, double m12, double m13,
          double m20, double m21, double m22, double m23,
          double m30, double m31, double m32, double m33)
  {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
  }

  ~Matrix4() = default;
  
  template<Matrix4T M4T> explicit Matrix4(const M4T& m4) {
    m[0][0] = m4[0][0];
    m[0][1] = m4[0][1];
    m[0][2] = m4[0][2];
    m[0][3] = m4[0][3];
    m[1][0] = m4[1][0];
    m[1][1] = m4[1][1];
    m[1][2] = m4[1][2];
    m[1][3] = m4[1][3];
    m[2][0] = m4[2][0];
    m[2][1] = m4[2][1];
    m[2][2] = m4[2][2];
    m[2][3] = m4[2][3];
    m[3][0] = m4[3][0];
    m[3][1] = m4[3][1];
    m[3][2] = m4[3][2];
    m[3][3] = m4[3][3];
  }
  
  template<Vec4T V4T> Matrix4(const V4T& v1, const V4T& v2, const V4T& v3, const V4T& v4) {
    m[0][0] = v1.x;
    m[0][1] = v1.y;
    m[0][2] = v1.z;
    m[0][3] = v1.w;
    m[1][0] = v2.x;
    m[1][1] = v2.y;
    m[1][2] = v2.z;
    m[1][3] = v2.w;
    m[2][0] = v3.x;
    m[2][1] = v3.y;
    m[2][2] = v3.z;
    m[2][3] = v3.w;
    m[3][0] = v4.x;
    m[3][1] = v4.y;
    m[3][2] = v4.z;
    m[3][3] = v4.w;
  }


  [[nodiscard]] Vec4<double> row(int i) const {
    return {m[i][0], m[i][1], m[i][2], m[i][3]};
  }

  [[nodiscard]] Vec4<double> col(int i) const {
    return {m[0][i], m[1][i], m[2][i], m[3][i]};
  }
  
  double *operator[](int i) {
    return m[i];
  }
  
  double operator()(int i, int j) const {
    return m[i][j];
  }

  Matrix4& operator=(const Matrix4& m) = default;

  Matrix4& operator=(Matrix4&& m) noexcept = default;
  
  Matrix4 operator*(const Matrix4& other) const {
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
  
  Matrix4& operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
  }
  
  template<Matrix4T M4T> Matrix4 operator*(const M4T& other) const {
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
  
  template<Matrix4T M4T> Matrix4& operator*=(const M4T& other) {
    *this = *this * other;
    return *this;
  }

  template<Vec3T V3T> friend V3T operator*(const V3T& v, const Matrix4& mat) {
    V3T ret = V3T();
    ret.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.z * mat.m[0][2] + mat.m[0][3];
    ret.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.z * mat.m[1][2] + mat.m[1][3];
    ret.z = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.z * mat.m[2][2] + mat.m[2][3];
    return ret;
  }
  
  template<Vec4T V4T> friend V4T operator*(const V4T& v, const Matrix4& mat) {
    V4T ret = V4T();
    ret.x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + v.w * mat.m[3][0];
    ret.y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + v.w * mat.m[3][1];
    ret.z = v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + v.w * mat.m[3][2];
    ret.w = v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + v.w * mat.m[3][3];
    return ret;
  }
  
  template<Vec2T V2T> Matrix4& operator*=(const V2T& v) {
    *this = *this * v;
    return *this;
  }
  
  template<Vec3T V3T> Matrix4& operator*=(const V3T& v) {
    *this = *this * v;
    return *this;
  }
  
  template<Vec4T V4T> Matrix4& operator*=(const V4T& v) {
    *this = *this * v;
    return *this;
  }
  
  friend Vec2<double> operator*(const Vec2<double>& v2, const Matrix4& mat) {
    return {dot<double>(v2, mat.col(0).xy()), dot<double>(v2, mat.col(1).xy())}; 
  }

  friend Vec3<double> operator*(const Vec3<double>& v3, const Matrix4& mat) {
    return {dot<double>(v3, mat.col(0)), dot<double>(v3, mat.col(1)), dot<double>(v3, mat.col(2))};
  }
  
  friend Vec4<double> operator*(const Vec4<double>& v4, const Matrix4& mat) {
    return {dot<double>(v4, mat.col(0)), dot<double>(v4, mat.col(1)), dot<double>(v4, mat.col(2)), dot<double>(v4, mat.col(3))};
  }
  
  friend Matrix4 operator*(const Matrix4& mat, const Vec2<double>& v2) {
    auto r0 = mat.row(0);
    auto r1 = mat.row(1);
    auto r2 = mat.row(2);
    auto r3 = mat.row(3);
    return {r0.x * v2.x, r0.y * v2.y, r0.z, r0.w,
            r1.x * v2.x, r1.y * v2.y, r1.z, r1.w,
            r2.x * v2.x, r2.y * v2.y, r2.z, r2.w,
            r3.x * v2.x, r3.y * v2.y, r3.z, r3.w};
  }
  
  friend Matrix2;
  friend Matrix3;
};

// end
} // namespace ams