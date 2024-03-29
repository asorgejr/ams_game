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
#include <ams/StringExtensions.hpp>
#else
import ams.StringExtensions;
#endif

using namespace ams;
using namespace std;

TEST(StringExtensions, Split) {
  string str = "Hello,World";
  auto arr = split(str, ",");
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr[0], "Hello");
  EXPECT_EQ(arr[1], "World");
}

TEST(StringExtensions, SplitWithSpaces) {
  string str = "Hello, World";
  auto arr = split(str, ",");
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr[0], "Hello");
  EXPECT_EQ(arr[1], " World");
}

TEST(StringExtensions, SplitMultiDelim) {
  string str = "Hello, World";
  auto arr = split(str, ", ");
  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr[0], "Hello");
  EXPECT_EQ(arr[1], "World");
}

TEST(StringExtensions, SplitTooShort) {
  string str = "Hello, World";
  auto arr = split(str, ", World");
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr[0], "Hello");
}

TEST(StringExtensions, SplitOverlapping) {
  string str = "Hello, World";
  auto arr = split(str, ", World ");
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr[0], "Hello, World");
}

