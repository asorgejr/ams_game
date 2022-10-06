export module ams.Vec;
import <concepts>;
import <cmath>;
import <type_traits>;
import ams.Math;

export namespace ams {

// This concept constrains a type requiring it to have a default constructor
// and public member fields x and y which are convertible to double.
template<typename TVec>
concept Vec2T = requires(TVec t) {
  // has default constructor
  { TVec() } -> std::same_as<TVec>;
  { t.x } -> std::convertible_to<double>;
  { t.y } -> std::convertible_to<double>;
};

/**
 * @brief A class that represents a 3D vector
 * @tparam TVec - the vector type
 */
template<typename TVec>
concept Vec3T = Vec2T<TVec> && requires(TVec t) {
  { t.z } -> std::convertible_to<double>;
  !requires { TVec::w; };
};

/**
 * @brief A class that represents a 4D vector
 * @tparam TVec - the vector type
 */
template<typename TVec>
concept Vec4T = Vec3T<TVec> && requires(TVec t) {
  { t.w } -> std::convertible_to<double>;
};


/**
 * 
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec2 {
  T x, y;

  constexpr Vec2() : x(0), y(0) {}

  constexpr explicit Vec2(T x) : x(x), y(x) {}

  constexpr Vec2(T x, T y) : x(x), y(y) {}

  constexpr Vec2(const Vec2& v) : x(v.x), y(v.y) {}

  template<Vec2T V2T> explicit Vec2(const V2T& v) : x(v.x), y(v.y) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    return (&x)[i];
  }
  
  // copy assignment operator
  template<Vec2T V2T> Vec2<T>& operator=(const V2T& v) {
    x = v.x;
    y = v.y;
    return *this;
  }

  // arithmetic operators
  constexpr Vec2<T> operator+(const Vec2<T>& v) const {
    return Vec2<T>(x + v.x, y + v.y);
  }
  
  constexpr Vec2<T> operator-(const Vec2<T>& v) const {
    return Vec2<T>(x - v.x, y - v.y);
  }
  
  constexpr Vec2<T> operator*(const Vec2<T>& v) const {
    return Vec2<T>(x * v.x, y * v.y);
  }
  
  constexpr Vec2<T> operator/(const Vec2<T>& v) const {
    return Vec2<T>(x / v.x, y / v.y);
  }
  
  constexpr Vec2<T> operator%(const Vec2<T>& v) const {
    return Vec2<T>(ams::mod(x, v.x), ams::mod(y, v.y));
  }
  
  template<Vec2T V2T> Vec2<T> operator+(const V2T& v) const {
    return Vec2<T>(x + v.x, y + v.y);
  }

  template<Vec2T V2T> Vec2<T> operator-(const V2T& v) const {
    return Vec2<T>(x - v.x, y - v.y);
  }

  template<Vec2T V2T> Vec2<T> operator*(const V2T& v) const {
    return Vec2<T>(x * v.x, y * v.y);
  }

  template<Vec2T V2T> Vec2<T> operator/(const V2T& v) const {
    return Vec2<T>(x / v.x, y / v.y);
  }

  template<Vec2T V2T> Vec2<T> operator%(const V2T& v) const {
    return Vec2<T>(mod<T>(x, v.x), mod<T>(y, v.y));
  }

  constexpr Vec2<T> operator+(const T& v) const {
    return Vec2<T>(x + v, y + v);
  }

  constexpr Vec2<T> operator-(const T& v) const {
    return Vec2<T>(x - v, y - v);
  }

  constexpr Vec2<T> operator*(const T& v) const {
    return Vec2<T>(x * v, y * v);
  }

  constexpr Vec2<T> operator/(const T& v) const {
    return Vec2<T>(x / v, y / v);
  }

  constexpr Vec2<T> operator%(const T& v) const {
    return Vec2<T>(mod<T>(x, v), mod<T>(y, v));
  }

  // compound assignment operators
  constexpr Vec2<T>& operator+=(const Vec2<T>& v) {
    return *this = *this + v;
  }
  
  constexpr Vec2<T>& operator-=(const Vec2<T>& v) {
    return *this = *this - v;
  }
  
  constexpr Vec2<T>& operator*=(const Vec2<T>& v) {
    return *this = *this * v;
  }
  
  constexpr Vec2<T>& operator/=(const Vec2<T>& v) {
    return *this = *this / v;
  }
  
  constexpr Vec2<T>& operator%=(const Vec2<T>& v) {
    return *this = *this % v;
  }
  
  template<Vec2T V2T> Vec2<T>& operator+=(const V2T& v) {
    return *this = *this + v;
  }

  template<Vec2T V2T> Vec2<T>& operator-=(const V2T& v) {
    return *this = *this - v;
  }

  template<Vec2T V2T> Vec2<T>& operator*=(const V2T& v) {
    return *this = *this * v;
  }

  template<Vec2T V2T> Vec2<T>& operator/=(const V2T& v) {
    return *this = *this / v;
  }
  
  template<Vec2T V2T> Vec2<T>& operator%=(const V2T& v) {
    return *this = *this % v;
  }

  constexpr Vec2<T>& operator+=(const T& v) {
    return *this = *this + v;
  }

  constexpr Vec2<T>& operator-=(const T& v) {
    return *this = *this - v;
  }

  constexpr Vec2<T>& operator*=(const T& v) {
    return *this = *this * v;
  }

  constexpr Vec2<T>& operator/=(const T& v) {
    return *this = *this / v;
  }

  constexpr Vec2<T>& operator%=(const T& v) {
    return *this = *this % v;
  }

  // urnary operators
  constexpr Vec2<T> operator-() const {
    return Vec2<T>(-x, -y);
  }

  constexpr Vec2<T> operator!() const {
    return Vec2<T>(!x, !y);
  }

  constexpr Vec2<T> operator~() const {
    return Vec2<T>(~x, ~y);
  }

  // lhs-rhs operators
  constexpr friend Vec2<T> operator+(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs + rhs.x, lhs + rhs.y);
  }

  constexpr friend Vec2<T> operator-(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs - rhs.x, lhs - rhs.y);
  }

  constexpr friend Vec2<T> operator*(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs * rhs.x, lhs * rhs.y);
  }

  constexpr friend Vec2<T> operator/(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs / rhs.x, lhs / rhs.y);
  }

  constexpr friend Vec2<T> operator%(const T& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs % rhs.x, lhs % rhs.y);
  }

  // comparison operators
  template<Vec2T V2T> bool operator==(const V2T& other) const {
    return x == other.x && y == other.y;
  }

  template<Vec2T V2T> bool operator!=(const V2T& other) const {
    return !(*this == other);
  }

  template<Vec2T V2T> bool operator<(const V2T& other) const {
    return x < other.x && y < other.y;
  }

  template<Vec2T V2T> bool operator>(const V2T& other) const {
    return x > other.x && y > other.y;
  }

  template<Vec2T V2T> bool operator<=(const V2T& other) const {
    return x <= other.x && y <= other.y;
  }

  template<Vec2T V2T> bool operator>=(const V2T& other) const {
    return x >= other.x && y >= other.y;
  }

#pragma region swizzle
#ifdef AMS_VEC_SWIZZLE_METHODS
  constexpr Vec2<T> xx() const {
    return Vec2<T>(x, x);
  }

  constexpr Vec2<T> xy() const {
    return Vec2<T>(x, y);
  }

  constexpr Vec2<T> yx() const {
    return Vec2<T>(y, x);
  }

  constexpr Vec2<T> yy() const {
    return Vec2<T>(y, y);
  }
#endif // AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle

};

/**
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec3 {
  T x, y, z;

  constexpr Vec3() : x(0), y(0), z(0) {}

  constexpr explicit Vec3(T x) : x(x), y(x), z(x) {}

  constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

  constexpr Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

  constexpr explicit Vec3(const Vec2<T>& v) : x(v.x), y(v.y), z(0) {}
  
  template<Vec3T V3T> explicit Vec3(const V3T& v) : x(v.x), y(v.y), z(v.z) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    return (&x)[i];
  }
  
  // copy assignment operator
  template<Vec3T V3T> Vec3<T>& operator=(const V3T& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  // arithmetic operators
  constexpr Vec3<T> operator+(const Vec3<T>& v) const {
    return Vec3<T>(x + v.x, y + v.y, z + v.z);
  }
  
  constexpr Vec3<T> operator-(const Vec3<T>& v) const {
    return Vec3<T>(x - v.x, y - v.y, z - v.z);
  }
  
  constexpr Vec3<T> operator*(const Vec3<T>& v) const {
    return Vec3<T>(x * v.x, y * v.y, z * v.z);
  }
  
  constexpr Vec3<T> operator/(const Vec3<T>& v) const {
    return Vec3<T>(x / v.x, y / v.y, z / v.z);
  }
  
  constexpr Vec3<T> operator%(const Vec3<T>& v) const {
    return Vec3<T>(x % v.x, y % v.y, z % v.z);
  }
  
  template<Vec3T V3T> Vec3<T> operator+(const V3T& other) const {
    return Vec3<T>(x + other.x, y + other.y, z + other.z);
  }

  template<Vec3T V3T> Vec3<T> operator-(const V3T& other) const {
    return Vec3<T>(x - other.x, y - other.y, z - other.z);
  }

  template<Vec3T V3T> Vec3<T> operator*(const V3T& other) const {
    return Vec3<T>(x * other.x, y * other.y, z * other.z);
  }

  template<Vec3T V3T> Vec3<T> operator/(const V3T& other) const {
    return Vec3<T>(x / other.x, y / other.y, z / other.z);
  }

  template<Vec3T V3T> Vec3<T> operator%(const V3T& other) const {
    return Vec3<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z));
  }

  constexpr Vec3<T> operator+(const T& other) const {
    return Vec3<T>(x + other, y + other, z + other);
  }

  constexpr Vec3<T> operator-(const T& other) const {
    return Vec3<T>(x - other, y - other, z - other);
  }

  constexpr Vec3<T> operator*(const T& other) const {
    return Vec3<T>(x * other, y * other, z * other);
  }

  constexpr Vec3<T> operator/(const T& other) const {
    return Vec3<T>(x / other, y / other, z / other);
  }

  constexpr Vec3<T> operator%(const T& other) const {
    return Vec3<T>(mod<T>(x, other), mod<T>(y, other), mod<T>(z, other));
  }

  // compound assignment operators
  constexpr Vec3<T>& operator+=(const Vec3<T>& v) {
    return *this = *this + v;
  }
  
  constexpr Vec3<T>& operator-=(const Vec3<T>& v) {
    return *this = *this - v;
  }
  
  constexpr Vec3<T>& operator*=(const Vec3<T>& v) {
    return *this = *this * v;
  }
  
  constexpr Vec3<T>& operator/=(const Vec3<T>& v) {
    return *this = *this / v;
  }
  
  constexpr Vec3<T>& operator%=(const Vec3<T>& v) {
    return *this = *this % v;
  }
  
  template<Vec3T V3T> Vec3<T>& operator+=(const V3T& other) {
    return *this = *this + other;
  }

  template<Vec3T V3T> Vec3<T>& operator-=(const V3T& other) {
    return *this = *this - other;
  }

  template<Vec3T V3T> Vec3<T>& operator*=(const V3T& other) {
    return *this = *this * other;
  }

  template<Vec3T V3T> Vec3<T>& operator/=(const V3T& other) {
    return *this = *this / other;
  }
  
  template<Vec3T V3T> Vec3<T>& operator%=(const V3T& other) {
    return *this = *this % other;
  }

  constexpr Vec3<T>& operator+=(const T& other) {
    return *this = *this + other;
  }

  constexpr Vec3<T>& operator-=(const T& other) {
    return *this = *this - other;
  }

  constexpr Vec3<T>& operator*=(const T& other) {
    return *this = *this * other;
  }

  constexpr Vec3<T>& operator/=(const T& other) {
    return *this = *this / other;
  }

  constexpr Vec3<T>& operator%=(const T& other) {
    return *this = *this % other;
  }

  // unary operators
  constexpr Vec3<T> operator-() const {
    return Vec3<T>(-x, -y, -z);
  }

  constexpr Vec3<T> operator!() const {
    return Vec3<T>(!x, !y, !z);
  }

  constexpr Vec3<T> operator~() const {
    return Vec3<T>(~x, ~y, ~z);
  }
  
  // lhs-rhs operators
  constexpr friend Vec3<T> operator+(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
  }

  constexpr friend Vec3<T> operator-(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
  }

  constexpr friend Vec3<T> operator*(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }

  constexpr friend Vec3<T> operator/(const T& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
  }
  
  // comparison operators
  template<Vec3T V3T> bool operator==(const V3T& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  template<Vec3T V3T> bool operator!=(const V3T& other) const {
    return !(*this == other);
  }

  template<Vec3T V3T> bool operator<(const V3T& other) const {
    return x < other.x && y < other.y && z < other.z;
  }

  template<Vec3T V3T> bool operator>(const V3T& other) const {
    return x > other.x && y > other.y && z > other.z;
  }

  template<Vec3T V3T> bool operator<=(const V3T& other) const {
    return x <= other.x && y <= other.y && z <= other.z;
  }

  template<Vec3T V3T> bool operator>=(const V3T& other) const {
    return x >= other.x && y >= other.y && z >= other.z;
  }

#pragma endregion operators
#pragma region swizzle
#ifdef AMS_VEC_SWIZZLE_METHODS
  constexpr Vec2<T> xx() const {
    return Vec2<T>(x, x);
  }
  constexpr Vec2<T> xy() const {
    return Vec2<T>(x, y);
  }
  constexpr Vec2<T> xz() const {
    return Vec2<T>(x, z);
  }
  constexpr Vec2<T> yx() const {
    return Vec2<T>(y, x);
  }
  constexpr Vec2<T> yy() const {
    return Vec2<T>(y, y);
  }
  constexpr Vec2<T> yz() const {
    return Vec2<T>(y, z);
  }
  constexpr Vec2<T> zx() const {
    return Vec2<T>(z, x);
  }
  constexpr Vec2<T> zy() const {
    return Vec2<T>(z, y);
  }
  constexpr Vec2<T> zz() const {
    return Vec2<T>(z, z);
  }
  constexpr Vec3<T> xxx() const {
    return Vec3<T>(x, x, x);
  }
  constexpr Vec3<T> xxy() const {
    return Vec3<T>(x, x, y);
  }
  constexpr Vec3<T> xxz() const {
    return Vec3<T>(x, x, z);
  }
  constexpr Vec3<T> xyx() const {
    return Vec3<T>(x, y, x);
  }
  constexpr Vec3<T> xyy() const {
    return Vec3<T>(x, y, y);
  }
  constexpr Vec3<T> xyz() const {
    return Vec3<T>(x, y, z);
  }
  constexpr Vec3<T> xzx() const {
    return Vec3<T>(x, z, x);
  }
  constexpr Vec3<T> xzy() const {
    return Vec3<T>(x, z, y);
  }
  constexpr Vec3<T> xzz() const {
    return Vec3<T>(x, z, z);
  }
  constexpr Vec3<T> yxx() const {
    return Vec3<T>(y, x, x);
  }
  constexpr Vec3<T> yxy() const {
    return Vec3<T>(y, x, y);
  }
  constexpr Vec3<T> yxz() const {
    return Vec3<T>(y, x, z);
  }
  constexpr Vec3<T> yyx() const {
    return Vec3<T>(y, y, x);
  }
  constexpr Vec3<T> yyy() const {
    return Vec3<T>(y, y, y);
  }
  constexpr Vec3<T> yyz() const {
    return Vec3<T>(y, y, z);
  }
  constexpr Vec3<T> yzx() const {
    return Vec3<T>(y, z, x);
  }
  constexpr Vec3<T> yzy() const {
    return Vec3<T>(y, z, y);
  }
  constexpr Vec3<T> yzz() const {
    return Vec3<T>(y, z, z);
  }
  constexpr Vec3<T> zxx() const {
    return Vec3<T>(z, x, x);
  }
  constexpr Vec3<T> zxy() const {
    return Vec3<T>(z, x, y);
  }
  constexpr Vec3<T> zxz() const {
    return Vec3<T>(z, x, z);
  }
  constexpr Vec3<T> zyx() const {
    return Vec3<T>(z, y, x);
  }
  constexpr Vec3<T> zyy() const {
    return Vec3<T>(z, y, y);
  }
  constexpr Vec3<T> zyz() const {
    return Vec3<T>(z, y, z);
  }
  constexpr Vec3<T> zzx() const {
    return Vec3<T>(z, z, x);
  }
  constexpr Vec3<T> zzy() const {
    return Vec3<T>(z, z, y);
  }
  constexpr Vec3<T> zzz() const {
    return Vec3<T>(z, z, z);
  }
#endif // AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle
};

/**
 * @tparam T - any numeric type
 */
template <NumericT T>
struct Vec4 {
  T x, y, z, w;

  constexpr Vec4() : x(0), y(0), z(0), w(0) {}

  constexpr explicit Vec4(T x) : x(x), y(x), z(x), w(x) {}

  constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

  constexpr Vec4(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
  
  template<Vec4T V4T> explicit Vec4(const V4T& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

#pragma region operators

  // subscript operator
  constexpr T operator[](int i) const {
    return (&x)[i];
  }
  
  // copy assignment operator
  template<Vec4T V4T> Vec4<T>& operator=(const V4T& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  // arithmetic operators
  constexpr Vec4<T> operator+(const Vec4<T>& other) const {
    return Vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
  }
  
  constexpr Vec4<T> operator-(const Vec4<T>& other) const {
    return Vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
  }
  
  constexpr Vec4<T> operator*(const Vec4<T>& other) const {
    return Vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
  }
  
  constexpr Vec4<T> operator/(const Vec4<T>& other) const {
    return Vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
  }
  
  constexpr Vec4<T> operator%(const Vec4<T>& other) const {
    return Vec4<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z), mod<T>(w, other.w));
  }
  
  template<Vec4T V4T> Vec4<T> operator+(const V4T& other) const {
    return Vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
  }

  template<Vec4T V4T> Vec4<T> operator-(const V4T& other) const {
    return Vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
  }

  template<Vec4T V4T> Vec4<T> operator*(const V4T& other) const {
    return Vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
  }

  template<Vec4T V4T> Vec4<T> operator/(const V4T& other) const {
    return Vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
  }

  template<Vec4T V4T> Vec4<T> operator%(const V4T& other) const {
    return Vec4<T>(mod<T>(x, other.x), mod<T>(y, other.y), mod<T>(z, other.z), mod<T>(w, other.w));
  }

  constexpr Vec4<T> operator+(T scalar) const {
    return Vec4<T>(x + scalar, y + scalar, z + scalar, w + scalar);
  }

  constexpr Vec4<T> operator-(T scalar) const {
    return Vec4<T>(x - scalar, y - scalar, z - scalar, w - scalar);
  }

  constexpr Vec4<T> operator*(T scalar) const {
    return Vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  constexpr Vec4<T> operator/(T scalar) const {
    return Vec4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
  }

  constexpr Vec4<T> operator%(T scalar) const {
    return Vec4<T>(mod<T>(x, scalar), mod<T>(y, scalar), mod<T>(z, scalar), mod<T>(w, scalar));
  }

  // compound assignment operators
  constexpr Vec4<T>& operator+=(const Vec4<T>& other) {
    return *this = *this + other;
  }
  
  constexpr Vec4<T>& operator-=(const Vec4<T>& other) {
    return *this = *this - other;
  }
  
  constexpr Vec4<T>& operator*=(const Vec4<T>& other) {
    return *this = *this * other;
  }
  
  constexpr Vec4<T>& operator/=(const Vec4<T>& other) {
    return *this = *this / other;
  }
  
  constexpr Vec4<T>& operator%=(const Vec4<T>& other) {
    return *this = *this % other;
  }
  
  template<Vec4T V4T> Vec4<T>& operator+=(const V4T& other) {
    return *this = *this + other;
  }

  template<Vec4T V4T> Vec4<T>& operator-=(const V4T& other) {
    return *this = *this - other;
  }

  template<Vec4T V4T> Vec4<T>& operator*=(const V4T& other) {
    return *this = *this * other;
  }

  template<Vec4T V4T> Vec4<T>& operator/=(const V4T& other) {
    return *this = *this / other;
  }

  template<Vec4T V4T> Vec4<T>& operator%=(const V4T& other) {
    return *this = *this % other;
  }

  constexpr Vec4<T>& operator+=(T scalar) {
    return *this = *this + scalar;
  }

  constexpr Vec4<T>& operator-=(T scalar) {
    return *this = *this - scalar;
  }

  constexpr Vec4<T>& operator*=(T scalar) {
    return *this = *this * scalar;
  }

  constexpr Vec4<T>& operator/=(T scalar) {
    return *this = *this / scalar;
  }

  constexpr Vec4<T>& operator%=(T scalar) {
    return *this = *this % scalar;
  }

  // unary operators
  constexpr Vec4<T> operator-() const {
    return Vec4<T>(-x, -y, -z, -w);
  }

  constexpr Vec4<T> operator!() const {
    return Vec4<T>(!x, !y, !z, !w);
  }

  constexpr Vec4<T> operator~() const {
    return Vec4<T>(~x, ~y, ~z, ~w);
  }
  
  // scalar lhs-rhs operators
  constexpr friend Vec4<T> operator+(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
  }

  constexpr friend Vec4<T> operator-(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
  }

  constexpr friend Vec4<T> operator*(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
  }

  constexpr friend Vec4<T> operator/(T lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
  }

  // comparison operators
  template<Vec4T V4T> bool operator==(const V4T& other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }
  
  template<Vec4T V4T> bool operator!=(const V4T& other) const {
    return !(*this == other);
  }
  
  template<Vec4T V4T> bool operator<(const V4T& other) const {
    return x < other.x && y < other.y && z < other.z && w < other.w;
  }
  
  template<Vec4T V4T> bool operator<=(const V4T& other) const {
    return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
  }
  
  template<Vec4T V4T> bool operator>(const V4T& other) const {
    return x > other.x && y > other.y && z > other.z && w > other.w;
  }
  
  template<Vec4T V4T> bool operator>=(const V4T& other) const {
    return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
  }


#pragma endregion operators
#pragma region swizzle
#ifdef AMS_VEC_SWIZZLE_METHODS
  constexpr Vec2<T> xx() const {
    return Vec2<T>(x, x);
  }
  constexpr Vec2<T> xy() const {
    return Vec2<T>(x, y);
  }
  constexpr Vec2<T> xz() const {
    return Vec2<T>(x, z);
  }
  constexpr Vec2<T> xw() const {
    return Vec2<T>(x, w);
  }
  constexpr Vec2<T> yx() const {
    return Vec2<T>(y, x);
  }
  constexpr Vec2<T> yy() const {
    return Vec2<T>(y, y);
  }
  constexpr Vec2<T> yz() const {
    return Vec2<T>(y, z);
  }
  constexpr Vec2<T> yw() const {
    return Vec2<T>(y, w);
  }
  constexpr Vec2<T> zx() const {
    return Vec2<T>(z, x);
  }
  constexpr Vec2<T> zy() const {
    return Vec2<T>(z, y);
  }
  constexpr Vec2<T> zz() const {
    return Vec2<T>(z, z);
  }
  constexpr Vec2<T> zw() const {
    return Vec2<T>(z, w);
  }
  constexpr Vec2<T> wx() const {
    return Vec2<T>(w, x);
  }
  constexpr Vec2<T> wy() const {
    return Vec2<T>(w, y);
  }
  constexpr Vec2<T> wz() const {
    return Vec2<T>(w, z);
  }
  constexpr Vec2<T> ww() const {
    return Vec2<T>(w, w);
  }
  constexpr Vec3<T> xxx() const {
    return Vec3<T>(x, x, x);
  }
  constexpr Vec3<T> xxy() const {
    return Vec3<T>(x, x, y);
  }
  constexpr Vec3<T> xxz() const {
    return Vec3<T>(x, x, z);
  }
  constexpr Vec3<T> xxw() const {
    return Vec3<T>(x, x, w);
  }
  constexpr Vec3<T> xyx() const {
    return Vec3<T>(x, y, x);
  }
  constexpr Vec3<T> xyy() const {
    return Vec3<T>(x, y, y);
  }
  constexpr Vec3<T> xyz() const {
    return Vec3<T>(x, y, z);
  }
  constexpr Vec3<T> xyw() const {
    return Vec3<T>(x, y, w);
  }
  constexpr Vec3<T> xzx() const {
    return Vec3<T>(x, z, x);
  }
  constexpr Vec3<T> xzy() const {
    return Vec3<T>(x, z, y);
  }
  constexpr Vec3<T> xzz() const {
    return Vec3<T>(x, z, z);
  }
  constexpr Vec3<T> xzw() const {
    return Vec3<T>(x, z, w);
  }
  constexpr Vec3<T> yxx() const {
    return Vec3<T>(y, x, x);
  }
  constexpr Vec3<T> yxy() const {
    return Vec3<T>(y, x, y);
  }
  constexpr Vec3<T> yxz() const {
    return Vec3<T>(y, x, z);
  }
  constexpr Vec3<T> yxw() const {
    return Vec3<T>(y, x, w);
  }
  constexpr Vec3<T> yyx() const {
    return Vec3<T>(y, y, x);
  }
  constexpr Vec3<T> yyy() const {
    return Vec3<T>(y, y, y);
  }
  constexpr Vec3<T> yyz() const {
    return Vec3<T>(y, y, z);
  }
  constexpr Vec3<T> yyw() const {
    return Vec3<T>(y, y, w);
  }
  constexpr Vec3<T> yzx() const {
    return Vec3<T>(y, z, x);
  }
  constexpr Vec3<T> yzy() const {
    return Vec3<T>(y, z, y);
  }
  constexpr Vec3<T> yzz() const {
    return Vec3<T>(y, z, z);
  }
  constexpr Vec3<T> yzw() const {
    return Vec3<T>(y, z, w);
  }
  constexpr Vec3<T> zxx() const {
    return Vec3<T>(z, x, x);
  }
  constexpr Vec3<T> zxy() const {
    return Vec3<T>(z, x, y);
  }
  constexpr Vec3<T> zxz() const {
    return Vec3<T>(z, x, z);
  }
  constexpr Vec3<T> zxw() const {
    return Vec3<T>(z, x, w);
  }
  constexpr Vec3<T> zyx() const {
    return Vec3<T>(z, y, x);
  }
  constexpr Vec3<T> zyy() const {
    return Vec3<T>(z, y, y);
  }
  constexpr Vec3<T> zyz() const {
    return Vec3<T>(z, y, z);
  }
  constexpr Vec3<T> zyw() const {
    return Vec3<T>(z, y, w);
  }
  constexpr Vec3<T> zzx() const {
    return Vec3<T>(z, z, x);
  }
  constexpr Vec3<T> zzy() const {
    return Vec3<T>(z, z, y);
  }
  constexpr Vec3<T> zzz() const {
    return Vec3<T>(z, z, z);
  }
  constexpr Vec3<T> zzw() const {
    return Vec3<T>(z, z, w);
  }
  constexpr Vec3<T> wxx() const {
    return Vec3<T>(w, x, x);
  }
  constexpr Vec3<T> wxy() const {
    return Vec3<T>(w, x, y);
  }
  constexpr Vec3<T> wxz() const {
    return Vec3<T>(w, x, z);
  }
  constexpr Vec3<T> wxw() const {
    return Vec3<T>(w, x, w);
  }
  constexpr Vec3<T> wyx() const {
    return Vec3<T>(w, y, x);
  }
  constexpr Vec3<T> wyy() const {
    return Vec3<T>(w, y, y);
  }
  constexpr Vec3<T> wyz() const {
    return Vec3<T>(w, y, z);
  }
  constexpr Vec3<T> wyw() const {
    return Vec3<T>(w, y, w);
  }
  constexpr Vec3<T> wzx() const {
    return Vec3<T>(w, z, x);
  }
  constexpr Vec3<T> wzy() const {
    return Vec3<T>(w, z, y);
  }
  constexpr Vec3<T> wzz() const {
    return Vec3<T>(w, z, z);
  }
  constexpr Vec3<T> wzw() const {
    return Vec3<T>(w, z, w);
  }
  constexpr Vec3<T> wwx() const {
    return Vec3<T>(w, w, x);
  }
  constexpr Vec3<T> wwy() const {
    return Vec3<T>(w, w, y);
  }
  constexpr Vec3<T> wwz() const {
    return Vec3<T>(w, w, z);
  }
  constexpr Vec3<T> www() const {
    return Vec3<T>(w, w, w);
  }
  constexpr Vec4<T> xxxx() const {
    return Vec4<T>(x, x, x, x);
  }
  constexpr Vec4<T> xxxy() const {
    return Vec4<T>(x, x, x, y);
  }
  constexpr Vec4<T> xxxz() const {
    return Vec4<T>(x, x, x, z);
  }
  constexpr Vec4<T> xxxw() const {
    return Vec4<T>(x, x, x, w);
  }
  constexpr Vec4<T> xxyx() const {
    return Vec4<T>(x, x, y, x);
  }
  constexpr Vec4<T> xxyy() const {
    return Vec4<T>(x, x, y, y);
  }
  constexpr Vec4<T> xxyz() const {
    return Vec4<T>(x, x, y, z);
  }
  constexpr Vec4<T> xxyw() const {
    return Vec4<T>(x, x, y, w);
  }
  constexpr Vec4<T> xxzx() const {
    return Vec4<T>(x, x, z, x);
  }
  constexpr Vec4<T> xxzy() const {
    return Vec4<T>(x, x, z, y);
  }
  constexpr Vec4<T> xxzz() const {
    return Vec4<T>(x, x, z, z);
  }
  constexpr Vec4<T> xxzw() const {
    return Vec4<T>(x, x, z, w);
  }
  constexpr Vec4<T> xxwx() const {
    return Vec4<T>(x, x, w, x);
  }
  constexpr Vec4<T> xxwy() const {
    return Vec4<T>(x, x, w, y);
  }
  constexpr Vec4<T> xxwz() const {
    return Vec4<T>(x, x, w, z);
  }
  constexpr Vec4<T> xxww() const {
    return Vec4<T>(x, x, w, w);
  }
  constexpr Vec4<T> xyxx() const {
    return Vec4<T>(x, y, x, x);
  }
  constexpr Vec4<T> xyxy() const {
    return Vec4<T>(x, y, x, y);
  }
  constexpr Vec4<T> xyxz() const {
    return Vec4<T>(x, y, x, z);
  }
  constexpr Vec4<T> xyxw() const {
    return Vec4<T>(x, y, x, w);
  }
  constexpr Vec4<T> xyyx() const {
    return Vec4<T>(x, y, y, x);
  }
  constexpr Vec4<T> xyyy() const {
    return Vec4<T>(x, y, y, y);
  }
  constexpr Vec4<T> xyyz() const {
    return Vec4<T>(x, y, y, z);
  }
  constexpr Vec4<T> xyyw() const {
    return Vec4<T>(x, y, y, w);
  }
  constexpr Vec4<T> xyzx() const {
    return Vec4<T>(x, y, z, x);
  }
  constexpr Vec4<T> xyzy() const {
    return Vec4<T>(x, y, z, y);
  }
  constexpr Vec4<T> xyzz() const {
    return Vec4<T>(x, y, z, z);
  }
  constexpr Vec4<T> xyzw() const {
    return Vec4<T>(x, y, z, w);
  }
  constexpr Vec4<T> xywx() const {
    return Vec4<T>(x, y, w, x);
  }
  constexpr Vec4<T> xywy() const {
    return Vec4<T>(x, y, w, y);
  }
  constexpr Vec4<T> xywz() const {
    return Vec4<T>(x, y, w, z);
  }
  constexpr Vec4<T> xyww() const {
    return Vec4<T>(x, y, w, w);
  }
  constexpr Vec4<T> xzxx() const {
    return Vec4<T>(x, z, x, x);
  }
  constexpr Vec4<T> xzxy() const {
    return Vec4<T>(x, z, x, y);
  }
  constexpr Vec4<T> xzxz() const {
    return Vec4<T>(x, z, x, z);
  }
  constexpr Vec4<T> xzxw() const {
    return Vec4<T>(x, z, x, w);
  }
  constexpr Vec4<T> xzyx() const {
    return Vec4<T>(x, z, y, x);
  }
  constexpr Vec4<T> xzyy() const {
    return Vec4<T>(x, z, y, y);
  }
  constexpr Vec4<T> xzyz() const {
    return Vec4<T>(x, z, y, z);
  }
  constexpr Vec4<T> xzyw() const {
    return Vec4<T>(x, z, y, w);
  }
  constexpr Vec4<T> xzzx() const {
    return Vec4<T>(x, z, z, x);
  }
  constexpr Vec4<T> xzzy() const {
    return Vec4<T>(x, z, z, y);
  }
  constexpr Vec4<T> xzzz() const {
    return Vec4<T>(x, z, z, z);
  }
  constexpr Vec4<T> xzzw() const {
    return Vec4<T>(x, z, z, w);
  }
  constexpr Vec4<T> xzwx() const {
    return Vec4<T>(x, z, w, x);
  }
  constexpr Vec4<T> xzwy() const {
    return Vec4<T>(x, z, w, y);
  }
  constexpr Vec4<T> xzwz() const {
    return Vec4<T>(x, z, w, z);
  }
  constexpr Vec4<T> xzww() const {
    return Vec4<T>(x, z, w, w);
  }
  constexpr Vec4<T> xwxx() const {
    return Vec4<T>(x, w, x, x);
  }
  constexpr Vec4<T> xwxy() const {
    return Vec4<T>(x, w, x, y);
  }
  constexpr Vec4<T> xwxz() const {
    return Vec4<T>(x, w, x, z);
  }
  constexpr Vec4<T> xwxw() const {
    return Vec4<T>(x, w, x, w);
  }
  constexpr Vec4<T> xwyx() const {
    return Vec4<T>(x, w, y, x);
  }
  constexpr Vec4<T> xwyy() const {
    return Vec4<T>(x, w, y, y);
  }
  constexpr Vec4<T> xwyz() const {
    return Vec4<T>(x, w, y, z);
  }
  constexpr Vec4<T> xwyw() const {
    return Vec4<T>(x, w, y, w);
  }
  constexpr Vec4<T> xwzx() const {
    return Vec4<T>(x, w, z, x);
  }
  constexpr Vec4<T> xwzy() const {
    return Vec4<T>(x, w, z, y);
  }
  constexpr Vec4<T> xwzz() const {
    return Vec4<T>(x, w, z, z);
  }
  constexpr Vec4<T> xwzw() const {
    return Vec4<T>(x, w, z, w);
  }
  constexpr Vec4<T> xwwx() const {
    return Vec4<T>(x, w, w, x);
  }
  constexpr Vec4<T> xwwy() const {
    return Vec4<T>(x, w, w, y);
  }
  constexpr Vec4<T> xwwz() const {
    return Vec4<T>(x, w, w, z);
  }
  constexpr Vec4<T> xwww() const {
    return Vec4<T>(x, w, w, w);
  }
  constexpr Vec4<T> yxxx() const {
    return Vec4<T>(y, x, x, x);
  }
  constexpr Vec4<T> yxxy() const {
    return Vec4<T>(y, x, x, y);
  }
  constexpr Vec4<T> yxxz() const {
    return Vec4<T>(y, x, x, z);
  }
  constexpr Vec4<T> yxxw() const {
    return Vec4<T>(y, x, x, w);
  }
  constexpr Vec4<T> yxyx() const {
    return Vec4<T>(y, x, y, x);
  }
  constexpr Vec4<T> yxyy() const {
    return Vec4<T>(y, x, y, y);
  }
  constexpr Vec4<T> yxyz() const {
    return Vec4<T>(y, x, y, z);
  }
  constexpr Vec4<T> yxyw() const {
    return Vec4<T>(y, x, y, w);
  }
  constexpr Vec4<T> yxzx() const {
    return Vec4<T>(y, x, z, x);
  }
  constexpr Vec4<T> yxzy() const {
    return Vec4<T>(y, x, z, y);
  }
  constexpr Vec4<T> yxzz() const {
    return Vec4<T>(y, x, z, z);
  }
  constexpr Vec4<T> yxzw() const {
    return Vec4<T>(y, x, z, w);
  }
  constexpr Vec4<T> yxwx() const {
    return Vec4<T>(y, x, w, x);
  }
  constexpr Vec4<T> yxwy() const {
    return Vec4<T>(y, x, w, y);
  }
  constexpr Vec4<T> yxwz() const {
    return Vec4<T>(y, x, w, z);
  }
  constexpr Vec4<T> yxww() const {
    return Vec4<T>(y, x, w, w);
  }
  constexpr Vec4<T> yyxx() const {
    return Vec4<T>(y, y, x, x);
  }
  constexpr Vec4<T> yyxy() const {
    return Vec4<T>(y, y, x, y);
  }
  constexpr Vec4<T> yyxz() const {
    return Vec4<T>(y, y, x, z);
  }
  constexpr Vec4<T> yyxw() const {
    return Vec4<T>(y, y, x, w);
  }
  constexpr Vec4<T> yyyx() const {
    return Vec4<T>(y, y, y, x);
  }
  constexpr Vec4<T> yyyy() const {
    return Vec4<T>(y, y, y, y);
  }
  constexpr Vec4<T> yyyz() const {
    return Vec4<T>(y, y, y, z);
  }
  constexpr Vec4<T> yyyw() const {
    return Vec4<T>(y, y, y, w);
  }
  constexpr Vec4<T> yyzx() const {
    return Vec4<T>(y, y, z, x);
  }
  constexpr Vec4<T> yyzy() const {
    return Vec4<T>(y, y, z, y);
  }
  constexpr Vec4<T> yyzz() const {
    return Vec4<T>(y, y, z, z);
  }
  constexpr Vec4<T> yyzw() const {
    return Vec4<T>(y, y, z, w);
  }
  constexpr Vec4<T> yywx() const {
    return Vec4<T>(y, y, w, x);
  }
  constexpr Vec4<T> yywy() const {
    return Vec4<T>(y, y, w, y);
  }
  constexpr Vec4<T> yywz() const {
    return Vec4<T>(y, y, w, z);
  }
  constexpr Vec4<T> yyww() const {
    return Vec4<T>(y, y, w, w);
  }
  constexpr Vec4<T> yzxx() const {
    return Vec4<T>(y, z, x, x);
  }
  constexpr Vec4<T> yzxy() const {
    return Vec4<T>(y, z, x, y);
  }
  constexpr Vec4<T> yzxz() const {
    return Vec4<T>(y, z, x, z);
  }
  constexpr Vec4<T> yzxw() const {
    return Vec4<T>(y, z, x, w);
  }
  constexpr Vec4<T> yzyx() const {
    return Vec4<T>(y, z, y, x);
  }
  constexpr Vec4<T> yzyy() const {
    return Vec4<T>(y, z, y, y);
  }
  constexpr Vec4<T> yzyz() const {
    return Vec4<T>(y, z, y, z);
  }
  constexpr Vec4<T> yzyw() const {
    return Vec4<T>(y, z, y, w);
  }
  constexpr Vec4<T> yzzx() const {
    return Vec4<T>(y, z, z, x);
  }
  constexpr Vec4<T> yzzy() const {
    return Vec4<T>(y, z, z, y);
  }
  constexpr Vec4<T> yzzz() const {
    return Vec4<T>(y, z, z, z);
  }
  constexpr Vec4<T> yzzw() const {
    return Vec4<T>(y, z, z, w);
  }
  constexpr Vec4<T> yzwx() const {
    return Vec4<T>(y, z, w, x);
  }
  constexpr Vec4<T> yzwy() const {
    return Vec4<T>(y, z, w, y);
  }
  constexpr Vec4<T> yzwz() const {
    return Vec4<T>(y, z, w, z);
  }
  constexpr Vec4<T> yzww() const {
    return Vec4<T>(y, z, w, w);
  }
  constexpr Vec4<T> ywxx() const {
    return Vec4<T>(y, w, x, x);
  }
  constexpr Vec4<T> ywxy() const {
    return Vec4<T>(y, w, x, y);
  }
  constexpr Vec4<T> ywxz() const {
    return Vec4<T>(y, w, x, z);
  }
  constexpr Vec4<T> ywxw() const {
    return Vec4<T>(y, w, x, w);
  }
  constexpr Vec4<T> ywyx() const {
    return Vec4<T>(y, w, y, x);
  }
  constexpr Vec4<T> ywyy() const {
    return Vec4<T>(y, w, y, y);
  }
  constexpr Vec4<T> ywyz() const {
    return Vec4<T>(y, w, y, z);
  }
  constexpr Vec4<T> ywyw() const {
    return Vec4<T>(y, w, y, w);
  }
  constexpr Vec4<T> ywzx() const {
    return Vec4<T>(y, w, z, x);
  }
  constexpr Vec4<T> ywzy() const {
    return Vec4<T>(y, w, z, y);
  }
  constexpr Vec4<T> ywzz() const {
    return Vec4<T>(y, w, z, z);
  }
  constexpr Vec4<T> ywzw() const {
    return Vec4<T>(y, w, z, w);
  }
  constexpr Vec4<T> ywwx() const {
    return Vec4<T>(y, w, w, x);
  }
  constexpr Vec4<T> ywwy() const {
    return Vec4<T>(y, w, w, y);
  }
  constexpr Vec4<T> ywwz() const {
    return Vec4<T>(y, w, w, z);
  }
  constexpr Vec4<T> ywww() const {
    return Vec4<T>(y, w, w, w);
  }
  constexpr Vec4<T> zxxx() const {
    return Vec4<T>(z, x, x, x);
  }
  constexpr Vec4<T> zxxy() const {
    return Vec4<T>(z, x, x, y);
  }
  constexpr Vec4<T> zxxz() const {
    return Vec4<T>(z, x, x, z);
  }
  constexpr Vec4<T> zxxw() const {
    return Vec4<T>(z, x, x, w);
  }
  constexpr Vec4<T> zxyx() const {
    return Vec4<T>(z, x, y, x);
  }
  constexpr Vec4<T> zxyy() const {
    return Vec4<T>(z, x, y, y);
  }
  constexpr Vec4<T> zxyz() const {
    return Vec4<T>(z, x, y, z);
  }
  constexpr Vec4<T> zxyw() const {
    return Vec4<T>(z, x, y, w);
  }
  constexpr Vec4<T> zxzx() const {
    return Vec4<T>(z, x, z, x);
  }
  constexpr Vec4<T> zxzy() const {
    return Vec4<T>(z, x, z, y);
  }
  constexpr Vec4<T> zxzz() const {
    return Vec4<T>(z, x, z, z);
  }
  constexpr Vec4<T> zxzw() const {
    return Vec4<T>(z, x, z, w);
  }
  constexpr Vec4<T> zxwx() const {
    return Vec4<T>(z, x, w, x);
  }
  constexpr Vec4<T> zxwy() const {
    return Vec4<T>(z, x, w, y);
  }
  constexpr Vec4<T> zxwz() const {
    return Vec4<T>(z, x, w, z);
  }
  constexpr Vec4<T> zxww() const {
    return Vec4<T>(z, x, w, w);
  }
  constexpr Vec4<T> zyxx() const {
    return Vec4<T>(z, y, x, x);
  }
  constexpr Vec4<T> zyxy() const {
    return Vec4<T>(z, y, x, y);
  }
  constexpr Vec4<T> zyxz() const {
    return Vec4<T>(z, y, x, z);
  }
  constexpr Vec4<T> zyxw() const {
    return Vec4<T>(z, y, x, w);
  }
  constexpr Vec4<T> zyyx() const {
    return Vec4<T>(z, y, y, x);
  }
  constexpr Vec4<T> zyyy() const {
    return Vec4<T>(z, y, y, y);
  }
  constexpr Vec4<T> zyyz() const {
    return Vec4<T>(z, y, y, z);
  }
  constexpr Vec4<T> zyyw() const {
    return Vec4<T>(z, y, y, w);
  }
  constexpr Vec4<T> zyzx() const {
    return Vec4<T>(z, y, z, x);
  }
  constexpr Vec4<T> zyzy() const {
    return Vec4<T>(z, y, z, y);
  }
  constexpr Vec4<T> zyzz() const {
    return Vec4<T>(z, y, z, z);
  }
  constexpr Vec4<T> zyzw() const {
    return Vec4<T>(z, y, z, w);
  }
  constexpr Vec4<T> zywx() const {
    return Vec4<T>(z, y, w, x);
  }
  constexpr Vec4<T> zywy() const {
    return Vec4<T>(z, y, w, y);
  }
  constexpr Vec4<T> zywz() const {
    return Vec4<T>(z, y, w, z);
  }
  constexpr Vec4<T> zyww() const {
    return Vec4<T>(z, y, w, w);
  }
  constexpr Vec4<T> zzxx() const {
    return Vec4<T>(z, z, x, x);
  }
  constexpr Vec4<T> zzxy() const {
    return Vec4<T>(z, z, x, y);
  }
  constexpr Vec4<T> zzxz() const {
    return Vec4<T>(z, z, x, z);
  }
  constexpr Vec4<T> zzxw() const {
    return Vec4<T>(z, z, x, w);
  }
  constexpr Vec4<T> zzyx() const {
    return Vec4<T>(z, z, y, x);
  }
  constexpr Vec4<T> zzyy() const {
    return Vec4<T>(z, z, y, y);
  }
  constexpr Vec4<T> zzyz() const {
    return Vec4<T>(z, z, y, z);
  }
  constexpr Vec4<T> zzyw() const {
    return Vec4<T>(z, z, y, w);
  }
  constexpr Vec4<T> zzzx() const {
    return Vec4<T>(z, z, z, x);
  }
  constexpr Vec4<T> zzzy() const {
    return Vec4<T>(z, z, z, y);
  }
  constexpr Vec4<T> zzzz() const {
    return Vec4<T>(z, z, z, z);
  }
  constexpr Vec4<T> zzzw() const {
    return Vec4<T>(z, z, z, w);
  }
  constexpr Vec4<T> zzwx() const {
    return Vec4<T>(z, z, w, x);
  }
  constexpr Vec4<T> zzwy() const {
    return Vec4<T>(z, z, w, y);
  }
  constexpr Vec4<T> zzwz() const {
    return Vec4<T>(z, z, w, z);
  }
  constexpr Vec4<T> zzww() const {
    return Vec4<T>(z, z, w, w);
  }
  constexpr Vec4<T> zwxx() const {
    return Vec4<T>(z, w, x, x);
  }
  constexpr Vec4<T> zwxy() const {
    return Vec4<T>(z, w, x, y);
  }
  constexpr Vec4<T> zwxz() const {
    return Vec4<T>(z, w, x, z);
  }
  constexpr Vec4<T> zwxw() const {
    return Vec4<T>(z, w, x, w);
  }
  constexpr Vec4<T> zwyx() const {
    return Vec4<T>(z, w, y, x);
  }
  constexpr Vec4<T> zwyy() const {
    return Vec4<T>(z, w, y, y);
  }
  constexpr Vec4<T> zwyz() const {
    return Vec4<T>(z, w, y, z);
  }
  constexpr Vec4<T> zwyw() const {
    return Vec4<T>(z, w, y, w);
  }
  constexpr Vec4<T> zwzx() const {
    return Vec4<T>(z, w, z, x);
  }
  constexpr Vec4<T> zwzy() const {
    return Vec4<T>(z, w, z, y);
  }
  constexpr Vec4<T> zwzz() const {
    return Vec4<T>(z, w, z, z);
  }
  constexpr Vec4<T> zwzw() const {
    return Vec4<T>(z, w, z, w);
  }
  constexpr Vec4<T> zwwx() const {
    return Vec4<T>(z, w, w, x);
  }
  constexpr Vec4<T> zwwy() const {
    return Vec4<T>(z, w, w, y);
  }
  constexpr Vec4<T> zwwz() const {
    return Vec4<T>(z, w, w, z);
  }
  constexpr Vec4<T> zwww() const {
    return Vec4<T>(z, w, w, w);
  }
  constexpr Vec4<T> wxxx() const {
    return Vec4<T>(w, x, x, x);
  }
  constexpr Vec4<T> wxxy() const {
    return Vec4<T>(w, x, x, y);
  }
  constexpr Vec4<T> wxxz() const {
    return Vec4<T>(w, x, x, z);
  }
  constexpr Vec4<T> wxxw() const {
    return Vec4<T>(w, x, x, w);
  }
  constexpr Vec4<T> wxyx() const {
    return Vec4<T>(w, x, y, x);
  }
  constexpr Vec4<T> wxyy() const {
    return Vec4<T>(w, x, y, y);
  }
  constexpr Vec4<T> wxyz() const {
    return Vec4<T>(w, x, y, z);
  }
  constexpr Vec4<T> wxyw() const {
    return Vec4<T>(w, x, y, w);
  }
  constexpr Vec4<T> wxzx() const {
    return Vec4<T>(w, x, z, x);
  }
  constexpr Vec4<T> wxzy() const {
    return Vec4<T>(w, x, z, y);
  }
  constexpr Vec4<T> wxzz() const {
    return Vec4<T>(w, x, z, z);
  }
  constexpr Vec4<T> wxzw() const {
    return Vec4<T>(w, x, z, w);
  }
  constexpr Vec4<T> wxwx() const {
    return Vec4<T>(w, x, w, x);
  }
  constexpr Vec4<T> wxwy() const {
    return Vec4<T>(w, x, w, y);
  }
  constexpr Vec4<T> wxwz() const {
    return Vec4<T>(w, x, w, z);
  }
  constexpr Vec4<T> wxww() const {
    return Vec4<T>(w, x, w, w);
  }
  constexpr Vec4<T> wyxx() const {
    return Vec4<T>(w, y, x, x);
  }
  constexpr Vec4<T> wyxy() const {
    return Vec4<T>(w, y, x, y);
  }
  constexpr Vec4<T> wyxz() const {
    return Vec4<T>(w, y, x, z);
  }
  constexpr Vec4<T> wyxw() const {
    return Vec4<T>(w, y, x, w);
  }
  constexpr Vec4<T> wyyx() const {
    return Vec4<T>(w, y, y, x);
  }
  constexpr Vec4<T> wyyy() const {
    return Vec4<T>(w, y, y, y);
  }
  constexpr Vec4<T> wyyz() const {
    return Vec4<T>(w, y, y, z);
  }
  constexpr Vec4<T> wyyw() const {
    return Vec4<T>(w, y, y, w);
  }
  constexpr Vec4<T> wyzx() const {
    return Vec4<T>(w, y, z, x);
  }
  constexpr Vec4<T> wyzy() const {
    return Vec4<T>(w, y, z, y);
  }
  constexpr Vec4<T> wyzz() const {
    return Vec4<T>(w, y, z, z);
  }
  constexpr Vec4<T> wyzw() const {
    return Vec4<T>(w, y, z, w);
  }
  constexpr Vec4<T> wywx() const {
    return Vec4<T>(w, y, w, x);
  }
  constexpr Vec4<T> wywy() const {
    return Vec4<T>(w, y, w, y);
  }
  constexpr Vec4<T> wywz() const {
    return Vec4<T>(w, y, w, z);
  }
  constexpr Vec4<T> wyww() const {
    return Vec4<T>(w, y, w, w);
  }
  constexpr Vec4<T> wzxx() const {
    return Vec4<T>(w, z, x, x);
  }
  constexpr Vec4<T> wzxy() const {
    return Vec4<T>(w, z, x, y);
  }
  constexpr Vec4<T> wzxz() const {
    return Vec4<T>(w, z, x, z);
  }
  constexpr Vec4<T> wzxw() const {
    return Vec4<T>(w, z, x, w);
  }
  constexpr Vec4<T> wzyx() const {
    return Vec4<T>(w, z, y, x);
  }
  constexpr Vec4<T> wzyy() const {
    return Vec4<T>(w, z, y, y);
  }
  constexpr Vec4<T> wzyz() const {
    return Vec4<T>(w, z, y, z);
  }
  constexpr Vec4<T> wzyw() const {
    return Vec4<T>(w, z, y, w);
  }
  constexpr Vec4<T> wzzx() const {
    return Vec4<T>(w, z, z, x);
  }
  constexpr Vec4<T> wzzy() const {
    return Vec4<T>(w, z, z, y);
  }
  constexpr Vec4<T> wzzz() const {
    return Vec4<T>(w, z, z, z);
  }
  constexpr Vec4<T> wzzw() const {
    return Vec4<T>(w, z, z, w);
  }
  constexpr Vec4<T> wzwx() const {
    return Vec4<T>(w, z, w, x);
  }
  constexpr Vec4<T> wzwy() const {
    return Vec4<T>(w, z, w, y);
  }
  constexpr Vec4<T> wzwz() const {
    return Vec4<T>(w, z, w, z);
  }
  constexpr Vec4<T> wzww() const {
    return Vec4<T>(w, z, w, w);
  }
  constexpr Vec4<T> wwxx() const {
    return Vec4<T>(w, w, x, x);
  }
  constexpr Vec4<T> wwxy() const {
    return Vec4<T>(w, w, x, y);
  }
  constexpr Vec4<T> wwxz() const {
    return Vec4<T>(w, w, x, z);
  }
  constexpr Vec4<T> wwxw() const {
    return Vec4<T>(w, w, x, w);
  }
  constexpr Vec4<T> wwyx() const {
    return Vec4<T>(w, w, y, x);
  }
  constexpr Vec4<T> wwyy() const {
    return Vec4<T>(w, w, y, y);
  }
  constexpr Vec4<T> wwyz() const {
    return Vec4<T>(w, w, y, z);
  }
  constexpr Vec4<T> wwyw() const {
    return Vec4<T>(w, w, y, w);
  }
  constexpr Vec4<T> wwzx() const {
    return Vec4<T>(w, w, z, x);
  }
  constexpr Vec4<T> wwzy() const {
    return Vec4<T>(w, w, z, y);
  }
  constexpr Vec4<T> wwzz() const {
    return Vec4<T>(w, w, z, z);
  }
  constexpr Vec4<T> wwzw() const {
    return Vec4<T>(w, w, z, w);
  }
  constexpr Vec4<T> wwwx() const {
    return Vec4<T>(w, w, w, x);
  }
  constexpr Vec4<T> wwwy() const {
    return Vec4<T>(w, w, w, y);
  }
  constexpr Vec4<T> wwwz() const {
    return Vec4<T>(w, w, w, z);
  }
  constexpr Vec4<T> wwww() const {
    return Vec4<T>(w, w, w, w);
  }
#endif //AMS_VEC_SWIZZLE_METHODS
#pragma endregion swizzle
};


#pragma region Vec Functions

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to remap
 * @param imin - the minimum value of the input range
 * @param imax - the maximum value of the input range
 * @param omin - the minimum value of the output range
 * @param omax - the maximum value of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec2T TVec>
TVec remap(TVec val, TNum imin, TNum imax, TNum omin, TNum omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin, imax, omin, omax);
  ret.y = remap<TNum>(val.y, imin, imax, omin, omax);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec2T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin.x, imax.x, omin.x, omax.x);
  ret.y = remap<TNum>(val.y, imin.y, imax.y, omin.y, omax.y);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TVec - any 2d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<Vec2T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  return remap<double>(val, imin, imax, omin, omax);
}

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to remap
 * @param imin - the minimum value of the input range
 * @param imax - the maximum value of the input range
 * @param omin - the minimum value of the output range
 * @param omax - the maximum value of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec3T TVec>
TVec remap(TVec val, TNum imin, TNum imax, TNum omin, TNum omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin, imax, omin, omax);
  ret.y = remap<TNum>(val.y, imin, imax, omin, omax);
  ret.z = remap<TNum>(val.z, imin, imax, omin, omax);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec3T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin.x, imax.x, omin.x, omax.x);
  ret.y = remap<TNum>(val.y, imin.y, imax.y, omin.y, omax.y);
  ret.z = remap<TNum>(val.z, imin.z, imax.z, omin.z, omax.z);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TVec - any 3d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<Vec3T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  return remap<double>(val, imin, imax, omin, omax);
}

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to remap
 * @param imin - the minimum value of the input range
 * @param imax - the maximum value of the input range
 * @param omin - the minimum value of the output range
 * @param omax - the maximum value of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec4T TVec>
TVec remap(TVec val, TNum imin, TNum imax, TNum omin, TNum omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin, imax, omin, omax);
  ret.y = remap<TNum>(val.y, imin, imax, omin, omax);
  ret.z = remap<TNum>(val.z, imin, imax, omin, omax);
  ret.w = remap<TNum>(val.w, imin, imax, omin, omax);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<NumericT TNum, Vec4T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  TVec ret = TVec();
  ret.x = remap<TNum>(val.x, imin.x, imax.x, omin.x, omax.x);
  ret.y = remap<TNum>(val.y, imin.y, imax.y, omin.y, omax.y);
  ret.z = remap<TNum>(val.z, imin.z, imax.z, omin.z, omax.z);
  ret.w = remap<TNum>(val.w, imin.w, imax.w, omin.w, omax.w);
  return ret;
}

/**
 * @brief remaps a value from one range to another
 * @tparam TVec - any 4d vector type
 * @param val - the value to remap
 * @param imin - the minimum values of the input range
 * @param imax - the maximum values of the input range
 * @param omin - the minimum values of the output range
 * @param omax - the maximum values of the output range
 * @return the remapped value
 */
template<Vec4T TVec>
TVec remap(TVec val, TVec imin, TVec imax, TVec omin, TVec omax) {
  return remap<double>(val, imin, imax, omin, omax);
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to clamp
 * @param low = the minimum value
 * @param high - the maximum value
 * @return 
 */
template<NumericT TNum, Vec2T TVec>
TVec clamp(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low, high);
  ret.y = clamp<TNum>(val.y, low, high);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<NumericT TNum, Vec2T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low.x, high.x);
  ret.y = clamp<TNum>(val.y, low.y, high.y);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TVec - any 2d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<Vec2T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  return clamp<double>(val, low, high);
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to clamp
 * @param low = the minimum value
 * @param high - the maximum value
 * @return 
 */
template<NumericT TNum, Vec3T TVec>
TVec clamp(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low, high);
  ret.y = clamp<TNum>(val.y, low, high);
  ret.z = clamp<TNum>(val.z, low, high);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<NumericT TNum, Vec3T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low.x, high.x);
  ret.y = clamp<TNum>(val.y, low.y, high.y);
  ret.z = clamp<TNum>(val.z, low.z, high.z);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TVec - any 3d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<Vec3T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  return clamp<double>(val, low, high);
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to clamp
 * @param low = the minimum value
 * @param high - the maximum value
 * @return 
 */
template<NumericT TNum, Vec4T TVec>
TVec clamp(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low, high);
  ret.y = clamp<TNum>(val.y, low, high);
  ret.z = clamp<TNum>(val.z, low, high);
  ret.w = clamp<TNum>(val.w, low, high);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<NumericT TNum, Vec4T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = clamp<TNum>(val.x, low.x, high.x);
  ret.y = clamp<TNum>(val.y, low.y, high.y);
  ret.z = clamp<TNum>(val.z, low.z, high.z);
  ret.w = clamp<TNum>(val.w, low.w, high.w);
  return ret;
}

/**
 * @brief clamp a value between a minimum and maximum value
 * @tparam TVec - any 4d vector type
 * @param val - the value to clamp
 * @param low = the minimum values
 * @param high - the maximum values
 * @return 
 */
template<Vec4T TVec>
TVec clamp(TVec val, TVec low, TVec high) {
  return clamp<double>(val, low, high);
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to wrap
 * @param low = the minimum value
 * @param high - the maximum value
 * @return the wrapped value
 */
template<NumericT TNum, Vec2T TVec>
TVec wrap(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low, high);
  ret.y = wrap<TNum>(val.y, low, high);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<NumericT TNum, Vec2T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low.x, high.x);
  ret.y = wrap<TNum>(val.y, low.y, high.y);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TVec - any 2d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<Vec2T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  return wrap<double>(val, low, high);
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to wrap
 * @param low = the minimum value
 * @param high - the maximum value
 * @return the wrapped value
 */
template<NumericT TNum, Vec3T TVec>
TVec wrap(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low, high);
  ret.y = wrap<TNum>(val.y, low, high);
  ret.z = wrap<TNum>(val.z, low, high);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<NumericT TNum, Vec3T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low.x, high.x);
  ret.y = wrap<TNum>(val.y, low.y, high.y);
  ret.z = wrap<TNum>(val.z, low.z, high.z);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TVec - any 3d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<Vec3T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  return wrap<double>(val, low, high);
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to wrap
 * @param low = the minimum value
 * @param high - the maximum value
 * @return the wrapped value
 */
template<NumericT TNum, Vec4T TVec>
TVec wrap(TVec val, TNum low, TNum high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low, high);
  ret.y = wrap<TNum>(val.y, low, high);
  ret.z = wrap<TNum>(val.z, low, high);
  ret.w = wrap<TNum>(val.w, low, high);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<NumericT TNum, Vec4T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  TVec ret = TVec();
  ret.x = wrap<TNum>(val.x, low.x, high.x);
  ret.y = wrap<TNum>(val.y, low.y, high.y);
  ret.z = wrap<TNum>(val.z, low.z, high.z);
  ret.w = wrap<TNum>(val.w, low.w, high.w);
  return ret;
}

/**
 * @brief wrap a value between a minimum and maximum value
 * @tparam TVec - any 4d vector type
 * @param val - the value to wrap
 * @param low = the minimum values
 * @param high - the maximum values
 * @return the wrapped value
 */
template<Vec4T TVec>
TVec wrap(TVec val, TVec low, TVec high) {
  return wrap<double>(val, low, high);
}

/**
 * @brief get the distance squared between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<NumericT TNum, Vec2T T1Vec, Vec2T T2Vec>
constexpr TNum distance2(T1Vec a, T2Vec b) {
  return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

/**
 * @brief get the distance squared between two points
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<Vec2T T1Vec, Vec2T T2Vec>
constexpr double distance2(T1Vec a, T2Vec b) {
  return distance2<double>(a, b);
}

/**
 * @brief get the distance squared between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<NumericT TNum, Vec3T T1Vec, Vec3T T2Vec>
constexpr TNum distance2(T1Vec a, T2Vec b) {
  return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
}

/**
 * @brief get the distance squared between two points
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<Vec3T T1Vec, Vec3T T2Vec>
constexpr double distance2(T1Vec a, T2Vec b) {
  return distance2<double>(a, b);
}

/**
 * @brief get the distance squared between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<NumericT TNum, Vec4T T1Vec, Vec4T T2Vec>
constexpr TNum distance2(T1Vec a, T2Vec b) {
  return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2) + pow(a.w - b.w, 2);
}

/**
 * @brief get the distance squared between two points
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance squared between two points
 */
template<Vec4T T1Vec, Vec4T T2Vec>
constexpr double distance2(T1Vec a, T2Vec b) {
  return distance2<double>(a, b);
}

/**
 * @brief get the distance between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance between the two points
 */
template<NumericT TNum, Vec2T T1Vec, Vec2T T2Vec>
constexpr TNum distance(T1Vec a, T2Vec b) {
  return sqrt(distance2<TNum>(a, b));
}

/**
 * @brief get the distance between two points
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first point
 * @param b - the second point
 * @return the distance between the two points
 */
template<Vec2T T1Vec, Vec2T T2Vec>
constexpr double distance(T1Vec a, T2Vec b) {
  return distance<double>(a, b);
}

/**
 * @brief get the distance between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first point
 * @param b - the second point
 * @return 
 */
template<NumericT TNum, Vec3T T1Vec, Vec3T T2Vec>
constexpr TNum distance(T1Vec a, T2Vec b) {
  return sqrt(distance2<TNum>(a, b));
}

/**
 * @brief get the distance between two points
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first point
 * @param b - the second point
 * @return 
 */
template<Vec3T T1Vec, Vec3T T2Vec>
constexpr double distance(T1Vec a, T2Vec b) {
  return distance<double>(a, b);
}

/**
 * @brief get the distance between two points
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first point
 * @param b - the second point
 * @return 
 */
template<NumericT TNum, Vec4T T1Vec, Vec4T T2Vec>
constexpr TNum distance(T1Vec a, T2Vec b) {
  return sqrt(distance2<TNum>(a, b));
}

/**
 * @brief get the distance between two points
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first point
 * @param b - the second point
 * @return 
 */
template<Vec4T T1Vec, Vec4T T2Vec>
constexpr double distance(T1Vec a, T2Vec b) {
  return distance<double>(a, b);
}

/**
 * @brief get the length squared of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */
template<NumericT TNum, Vec2T TVec>
constexpr TNum length2(TVec a) {
  return pow(a.x, 2) + pow(a.y, 2);
}

/**
 * @brief get the length squared of a vector
 * @tparam TVec - any 2d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */

template<Vec2T TVec>
constexpr double length2(TVec a) {
  return length2<double>(a);
}

/**
 * @brief get the length squared of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */
template<NumericT TNum, Vec3T TVec>
constexpr TNum length2(TVec a) {
  return pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2);
}

/**
 * @brief get the length squared of a vector
 * @tparam TVec - any 3d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */
template<Vec3T TVec>
constexpr double length2(TVec a) {
  return length2<double>(a);
}

/**
 * @brief get the length squared of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */
template<NumericT TNum, Vec4T TVec>
constexpr TNum length2(TVec a) {
  return pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2);
}

/**
 * @brief get the length squared of a vector
 * @tparam TVec - any 4d vector type
 * @param a - the vector
 * @return the length squared of the vector
 */
template<Vec4T TVec>
constexpr double length2(TVec a) {
  return length2<double>(a);
}

/**
 * @brief get the length of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<NumericT TNum, Vec2T TVec>
constexpr TNum length(TVec a) {
  return sqrt(length2<TNum>(a));
}

/**
 * @brief get the length of a vector
 * @tparam TVec - any 2d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<Vec2T TVec>
constexpr double length(TVec a) {
  return length<double>(a);
}

/**
 * @brief get the length of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<NumericT TNum, Vec3T TVec>
constexpr TNum length(TVec a) {
  return sqrt(length2<TNum>(a));
}

/**
 * @brief get the length of a vector
 * @tparam TVec - any 3d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<Vec3T TVec>
constexpr double length(TVec a) {
  return length<double>(a);
}

/**
 * @brief get the length of a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 4d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<NumericT TNum, Vec4T TVec>
constexpr TNum length(TVec a) {
  return sqrt(length2<TNum>(a));
}

/**
 * @brief get the length of a vector
 * @tparam TVec - any 4d vector type
 * @param a - the vector
 * @return the length of the vector
 */
template<Vec4T TVec>
constexpr double length(TVec a) {
  return length<double>(a);
}

/**
 * @brief get the dot product of two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<NumericT TNum, Vec2T T1Vec, Vec2T T2Vec>
constexpr TNum dot(T1Vec a, T2Vec b) {
  return a.x * b.x + a.y * b.y;
}

/**
 * @brief get the dot product of two vectors
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<Vec2T T1Vec, Vec2T T2Vec>
constexpr double dot(T1Vec a, T2Vec b) {
  return dot<double>(a, b);
}

/**
 * @brief get the dot product of two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<NumericT TNum, Vec3T T1Vec, Vec3T T2Vec>
constexpr TNum dot(T1Vec a, T2Vec b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief get the dot product of two vectors
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<Vec3T T1Vec, Vec3T T2Vec>
constexpr double dot(T1Vec a, T2Vec b) {
  return dot<double>(a, b);
}

/**
 * @brief get the dot product of two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<NumericT TNum, Vec4T T1Vec, Vec4T T2Vec>
constexpr TNum dot(T1Vec a, T2Vec b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief get the dot product of two vectors
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the dot product of the two vectors
 */
template<Vec4T T1Vec, Vec4T T2Vec>
constexpr double dot(T1Vec a, T2Vec b) {
  return dot<double>(a, b);
}

/**
 * @brief get the cross product of two vectors
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<Vec2T T1Vec, Vec2T T2Vec>
T1Vec cross(T1Vec a, T2Vec b) {
  T1Vec ret = T1Vec();
  ret.x = a.x * b.y - a.y * b.x;
  ret.y = a.x * b.y - a.y * b.x;
  return ret;
}

/**
 * @brief get the cross product of two vectors
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<Vec3T T1Vec, Vec3T T2Vec>
T1Vec cross(T1Vec a, T2Vec b) {
  T1Vec ret = T1Vec();
  ret.x = a.y * b.z - a.z * b.y;
  ret.y = a.z * b.x - a.x * b.z;
  ret.z = a.x * b.y - a.y * b.x;
  return ret;
}

/**
 * @brief get the cross product of two vectors
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<Vec4T T1Vec, Vec4T T2Vec>
T1Vec cross(T1Vec a, T2Vec b) {
  T1Vec ret = T1Vec();
  ret.x = a.y * b.z - a.z * b.y;
  ret.y = a.z * b.x - a.x * b.z;
  ret.z = a.x * b.y - a.y * b.x;
  ret.w = 0;
  return ret;
}

/**
 * @brief get the angle between two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the angle between the two vectors
 */
template<NumericT TNum, Vec2T T1Vec, Vec2T T2Vec>
constexpr TNum angle(T1Vec a, T2Vec b) {
  return acos(dot<TNum>(a, b) / (length(a) * length(b)));
}

/**
 * @brief get the angle between two vectors
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the angle between the two vectors
 */
template<Vec2T T1Vec, Vec2T T2Vec>
constexpr double angle(T1Vec a, T2Vec b) {
  return angle<double>(a, b);
}

/**
 * @brief get the angle between two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the angle between the two vectors
 */
template<NumericT TNum, Vec3T T1Vec, Vec3T T2Vec>
constexpr TNum angle(T1Vec a, T2Vec b) {
  return acos(dot<TNum>(a, b) / (length<TNum>(a) * length<TNum>(b)));
}

/**
 * @brief get the angle between two vectors
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the angle between the two vectors
 */
template<Vec3T T1Vec, Vec3T T2Vec>
constexpr double angle(T1Vec a, T2Vec b) {
  return angle<double>(a, b);
}

/**
 * @brief get the angle between two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @return the angle between the two vectors
 */
template<NumericT TNum, Vec4T T1Vec, Vec4T T2Vec>
constexpr TNum angle(T1Vec a, T2Vec b) {
  return acos(dot<TNum>(a, b) / (length<TNum>(a) * length<TNum>(b)));
}

/**
 * @brief normalize a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 2d vector type
 * @param a - the vector
 * @return the normalized vector
 */
template<Vec2T TVec>
TVec normalize(TVec a) {
  auto l = length<double>(a);
  TVec ret = TVec();
  ret.x = a.x / l;
  ret.y = a.y / l;
  return ret;
}

/**
 * @brief normalize a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam TVec - any 3d vector type
 * @param a - the vector
 * @return the normalized vector
 */
template<Vec3T TVec>
TVec normalize(TVec a) {
  auto l = length<double>(a);
  TVec ret = TVec();
  ret.x = a.x / l;
  ret.y = a.y / l;
  ret.z = a.z / l;
  return ret;
}

/**
 * @brief normalize a vector
 * @tparam TVec - any 4d vector type
 * @param a - the vector
 * @return the normalized vector
 */
template<Vec4T TVec>
TVec normalize(TVec a) {
  auto l = length<double>(a);
  TVec ret = TVec();
  ret.x = a.x / l;
  ret.y = a.y / l;
  ret.z = a.z / l;
  ret.w = a.w / l;
  return ret;
}

/**
 * @brief linearly interpolate between two vectors
 * @tparam T1Vec - any 2d vector type
 * @tparam T2Vec - any 2d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @param t - the interpolation factor
 * @return the interpolated vector
 */
template<Vec2T T1Vec, Vec2T T2Vec>
T1Vec lerp(T1Vec a, T2Vec b, double t) {
  T1Vec ret = T1Vec();
  ret.x = lerp<double>(a.x, b.x, t);
  ret.y = lerp<double>(a.y, b.y, t);
  return ret;
}

/**
 * @brief linearly interpolate between two vectors
 * @tparam T1Vec - any 3d vector type
 * @tparam T2Vec - any 3d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @param t - the interpolation factor
 * @return the interpolated vector
 */
template<Vec3T T1Vec, Vec3T T2Vec>
T1Vec lerp(T1Vec a, T2Vec b, double t) {
  T1Vec ret = T1Vec();
  ret.x = lerp<double>(a.x, b.x, t);
  ret.y = lerp<double>(a.y, b.y, t);
  ret.z = lerp<double>(a.z, b.z, t);
  return ret;
}

/**
 * @brief linearly interpolate between two vectors
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @param t - the interpolation factor
 * @return the interpolated vector
 */
template<Vec4T T1Vec, Vec4T T2Vec>
T1Vec lerp(T1Vec a, T2Vec b, double t) {
  T1Vec ret = T1Vec();
  ret.x = lerp<double>(a.x, b.x, t);
  ret.y = lerp<double>(a.y, b.y, t);
  ret.z = lerp<double>(a.z, b.z, t);
  ret.w = lerp<double>(a.w, b.w, t);
  return ret;
}


/**
 * @brief spherical linear interpolation between two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @tparam T1Vec - any 4d vector type
 * @tparam T2Vec - any 4d vector type
 * @param a - the first vector
 * @param b - the second vector
 * @param t - the interpolation factor
 * @return the interpolated vector
 */
template<Vec4T T1Vec, Vec4T T2Vec>
T1Vec slerp(T1Vec a, T2Vec b, double t) {
  // quaternion to return
  auto qm = T1Vec();
  // Calculate angle between them.
  double cosHalfTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
  // if qa=qb or qa=-qb then theta = 0 and we can return qa
  if (abs(cosHalfTheta) >= 1.0){
    qm.w = a.w; qm.x = a.x; qm.y = a.y; qm.z = a.z;
    return qm;
  }
  // Calculate temporary values.
  double halfTheta = acos(cosHalfTheta);
  double sinHalfTheta = sqrt(1.0 - cosHalfTheta*cosHalfTheta);
  // if theta = 180 degrees then result is not fully defined
  // we could rotate around any axis normal to qa or qb
  if (abs(sinHalfTheta) < 0.001){
    qm.w = a.w * 0.5 + b.w * 0.5;
    qm.x = a.x * 0.5 + b.x * 0.5;
    qm.y = a.y * 0.5 + b.y * 0.5;
    qm.z = a.z * 0.5 + b.z * 0.5;
    return qm;
  }
  double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
  double ratioB = sin(t * halfTheta) / sinHalfTheta;
  //calculate Quaternion.
  qm.w = a.w * ratioA + b.w * ratioB;
  qm.x = a.x * ratioA + b.x * ratioB;
  qm.y = a.y * ratioA + b.y * ratioB;
  qm.z = a.z * ratioA + b.z * ratioB;
  return qm;
}

#pragma endregion Vec Functions


}
