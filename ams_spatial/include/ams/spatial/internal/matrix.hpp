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
#include "ams/Math.hpp"
#include "ams/Array.hpp"
/*[exclude end]*/
/*[export module ams.spatial.internal.matrix]*/
/*[import ams.Math]*/
/*[import ams.Array]*/

/*[export]*/ namespace ams {

/**
 * @brief base class for all matrix types
 * @tparam T - any decimal type
 * @tparam R - number of rows
 * @tparam C - number of columns
 */
template<DecimalT T, size_t R, size_t C>
struct matrix {
protected:
  Array<Array<T, C>, R> m{0};
};

} // ams
