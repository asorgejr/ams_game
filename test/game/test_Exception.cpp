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

#ifndef AMS_MODULES
#include "ams/game/Exceptions.hpp"
#else
import ams.game.Exceptions
#endif
#include <filesystem>
#include <gtest/gtest.h>

using std::string;
namespace fs = std::filesystem;

TEST(Exception, DefaultConstructor) {
  ams::Exception e;
  EXPECT_STREQ(e.what(), "An exception has occurred");
}

TEST(Exception, What) {
  try {
    throw ams::Exception("Test Exception");
  } catch (ams::Exception& e) {
    EXPECT_STREQ(e.what(), "Test Exception");
  }
}

TEST(Exception, GetTrace) {
  try {
    throw ams::Exception("Test Exception");
  } catch (ams::Exception& e) {
    EXPECT_STREQ(fs::path(e.getTrace().file_name()).filename().string().c_str(), "test_Exception.cpp");
  }
}

TEST(Exception, ToString) {
  int line=0;
  int col = 0;
  try {
    line = __LINE__ + 1;
/*|||||||1|||||||||2|||||||||3|||||||||4|||||||||5|||||||||6|||||||||7|||||||||8|||||||*/
    throw ams::Exception("Test Exception");
  } catch (ams::Exception& e) {
    string expected = string("Test Exception: ") + __FILE__ + ":" + std::to_string(line) + ":25";
    EXPECT_STREQ(e.toString().c_str(), expected.c_str());
  }
}