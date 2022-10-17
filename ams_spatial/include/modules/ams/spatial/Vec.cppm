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

export module ams.spatial.Vec;
// import <cmath>;
import <type_traits>;
import <stdexcept>;
import ams;
import ams.spatial.internal.config;
export import ams.spatial.Vec2;
export import ams.spatial.Vec3;
export import ams.spatial.Vec4;

export namespace ams {


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
  return pow<TNum>(a.x, 2) + pow<TNum>(a.y, 2) + pow<TNum>(a.z, 2);
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
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<NumericT TNum>
constexpr Vec2<TNum> cross(Vec2<TNum> a, Vec2<TNum> b) {
  Vec2<TNum> ret = Vec2<TNum>();
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
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<NumericT TNum>
constexpr Vec3<TNum> cross(Vec3<TNum> a, Vec3<TNum> b) {
  Vec3<TNum> ret = Vec3<TNum>();
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
 * @brief get the cross product of two vectors
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @param a - the first vector
 * @param b - the second vector
 * @return the cross product of the two vectors
 */
template<NumericT TNum>
constexpr Vec4<TNum> cross(Vec4<TNum> a, Vec4<TNum> b) {
  Vec4<TNum> ret = Vec4<TNum>();
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
 * @param a - the vector
 * @return the normalized vector
 */
template<NumericT TNum>
constexpr Vec2<TNum> normalize(Vec2<TNum> a) {
  auto l = length<TNum>(a);
  Vec2<TNum> ret = Vec2<TNum>();
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
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @param a - the vector
 * @return the normalized vector
 */
template<NumericT TNum>
constexpr Vec3<TNum> normalize(Vec3<TNum> a) {
  auto l = length<TNum>(a);
  Vec3<TNum> ret = Vec3<TNum>();
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
 * @brief normalize a vector
 * @tparam TNum - the vector component type (i.e.: float, double, int, etc.)
 * @param a - the vector
 * @return the normalized vector
 */
template<NumericT TNum>
constexpr Vec4<TNum> normalize(Vec4<TNum> a) {
  auto l = length<TNum>(a);
  Vec4<TNum> ret = Vec4<TNum>();
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

}
