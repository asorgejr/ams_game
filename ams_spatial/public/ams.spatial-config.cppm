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
#include "ams/spatial/config.hpp"
export module ams.spatial:config;


export namespace ams {

using decimal_t = double;

// This concept constrains a type requiring it to have a default constructor
// and public member fields x and y which are convertible to double.
template<typename TVec>
concept Vec2T = requires(TVec t) {
  // has default constructor
  { TVec() } -> std::same_as<TVec>;
  { t.x } -> std::convertible_to<decimal_t>;
  { t.y } -> std::convertible_to<decimal_t>;
};

/**
 * @brief A class that represents a 3D vector
 * @tparam TVec - the vector type
 */
template<typename TVec>
concept Vec3T = Vec2T<TVec> && requires(TVec t) {
  { t.z } -> std::convertible_to<decimal_t>;
  !requires { TVec::w; };
};

/**
 * @brief A class that represents a 4D vector
 * @tparam TVec - the vector type
 */
template<typename TVec>
concept Vec4T = Vec3T<TVec> && requires(TVec t) {
  { t.w } -> std::convertible_to<decimal_t>;
};


}