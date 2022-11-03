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

#include <gtest/gtest.h>

#ifndef AMS_MODULES
#include <ams/Array.hpp>
#else
import ams;
#endif

using namespace ams;

TEST(array, array) {
  ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(array, ArrayCopy) {
  ams::Array<int, 3> arr{1, 2, 3};
  ams::Array<int, 3> arr2 = arr;
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array, ArrayMove) {
  ams::Array<int, 3> arr{1, 2, 3};
  ams::Array<int, 3> arr2 = std::move(arr);
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array, ArrayCopyAssignment) {
  ams::Array<int, 3> arr{1, 2, 3};
  ams::Array<int, 3> arr2;
  arr2 = arr;
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array, ArrayMoveAssignment) {
  ams::Array<int, 3> arr{1, 2, 3};
  ams::Array<int, 3> arr2;
  arr2 = std::move(arr);
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array, ArrayIterator) {
  ams::Array<int, 3> arr{1, 2, 3};
  int i = 0;
  for (auto& element : arr) {
    EXPECT_EQ(element, ++i);
  }
}

TEST(array, ArrayConstIterator) {
  const ams::Array<int, 3> arr{1, 2, 3};
  int i = 0;
  for (auto& element : arr) {
    EXPECT_EQ(element, ++i);
  }
}

TEST(array, ArrayReverseIterator) {
  ams::Array<int, 3> arr{1, 2, 3};
  int i = 3;
  for (auto& element : arr.reversed()) {
    EXPECT_EQ(element, i--);
  }
}

TEST(array, ArrayConstReverseIterator) {
  const ams::Array<int, 3> arr{1, 2, 3};
  int i = 3;
  for (auto& element : arr.reversed()) {
    EXPECT_EQ(element, i--);
  }
}

TEST(array, ArrayPointer) {
  ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.data(), &arr[0]);
}

TEST(array, ArrayPointerConst) {
  const ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.data(), &arr[0]);
}

TEST(array, ArrayPointerIterator) {
  ams::Array<int, 3> arr{1, 2, 3};
  int i = 0;
  for (auto* element = arr.data(); element != arr.data() + arr.size(); ++element) {
    EXPECT_EQ(*element, ++i);
  }
}

TEST(array, ArrayPointerConstIterator) {
  const ams::Array<int, 3> arr{1, 2, 3};
  int i = 0;
  for (auto* element = arr.data(); element != arr.data() + arr.size(); ++element) {
    EXPECT_EQ(*element, ++i);
  }
}

#ifdef AMS_EXCEPTIONS

TEST(array, ArrayOutOfBounds) {
  ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_THROW(arr[3], std::out_of_range);
}

TEST(array, ArrayOutOfBoundsConst) {
  const ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_THROW(arr[3], std::out_of_range);
}

TEST(array, ArrayOutOfBoundsAt) {
  ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(array, ArrayOutOfBoundsAtConst) {
  const ams::Array<int, 3> arr{1, 2, 3};
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(array, ArrayOutOfBoundsFront) {
  ams::Array<int, 0> arr{};
  EXPECT_THROW(arr.front(), std::out_of_range);
}

TEST(array, ArrayOutOfBoundsFrontConst) {
  const ams::Array<int, 0> arr{};
  EXPECT_THROW(arr.front(), std::out_of_range);
}

TEST(array, ArrayOutOfBoundsBack) {
  ams::Array<int, 0> arr{};
  EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(array, ArrayOutOfBoundsBackConst) {
  const ams::Array<int, 0> arr{};
  EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(array, ArraySlice) {
  ams::Array<int, 7> arr{1, 2, 3, 4, 5, 6, 7};
  auto slice = arr.slice(1, 5);
  auto size = slice.size();
  EXPECT_EQ(size, 4);
  EXPECT_EQ(slice[0], 2);
  EXPECT_EQ(slice[1], 3);
  EXPECT_EQ(slice[2], 4);
  EXPECT_EQ(slice[3], 5);
}

TEST(array, ArraySliceConst) {
  const ams::Array<int, 7> arr{1, 2, 3, 4, 5, 6, 7};
  auto slice = arr.slice(1, 5);
  auto size = slice.size();
  EXPECT_EQ(size, 4);
  EXPECT_EQ(slice[0], 2);
  EXPECT_EQ(slice[1], 3);
  EXPECT_EQ(slice[2], 4);
  EXPECT_EQ(slice[3], 5);
}

TEST(array, ArraySliceOutOfBounds) {
  ams::Array<int, 7> arr{1, 2, 3, 4, 5, 6, 7};
  EXPECT_THROW(arr.slice(1, 8), std::out_of_range);
}

TEST(array, ArraySliceOutOfBoundsConst) {
  const ams::Array<int, 7> arr{1, 2, 3, 4, 5, 6, 7};
  EXPECT_THROW(arr.slice(1, 8), std::out_of_range);
}

#endif
