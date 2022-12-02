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

import ams;


TEST(Function, DefaultConstructor) {
  ams::Function<void> f;
  EXPECT_FALSE(f);
}

TEST(Function, Constructor) {
  ams::Function<void> f([]() {});
  EXPECT_TRUE(f);
}

TEST(Function, CopyConstructor) {
  ams::Function<void> f([]() {});
  ams::Function<void> f2(f);
  EXPECT_EQ(f, f2);
}

TEST(Function, MoveConstructor) {
  ams::Function<void> f([]() {});
  ams::Function<void> f2(std::move(f));
  EXPECT_TRUE(f2);
}

TEST(Function, CopyAssignment) {
  ams::Function<void> f([]() {});
  ams::Function<void> f2;
  f2 = f;
  EXPECT_EQ(f, f2);
}

TEST(Function, MoveAssignment) {
  ams::Function<void> f([]() {});
  ams::Function<void> f2;
  f2 = std::move(f);
  EXPECT_TRUE(f2);
}

TEST(Function, Invoke) {
  ams::Function<void> f([]() {});
  f();
}

TEST(Function, InvokeWithArgs) {
  ams::Function<void, int, int> f([](int a, int b) {
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
  });
  f(1, 2);
}

TEST(Function, InvokeWithArgsAndReturn) {
  ams::Function<int, int, int> f([](int a, int b) {
    return a + b;
  });
  EXPECT_EQ(f(1, 2), 3);
}

TEST(Function, InvokeWithArgsAndReturnAndCapture) {
  int a = 1;
  int b = 2;
  ams::Function<int> f([&]() {
    return a + b;
  });
  EXPECT_EQ(f(), 3);
}

TEST(Function, InvokeWithArgsAndReturnAndCaptureAndMutable) {
  int a = 1;
  int b = 2;
  ams::Function<int> f([&]() mutable {
    return a + b;
  });
  EXPECT_EQ(f(), 3);
}

TEST(Function, InvokeWithArgsAndReturnWithCaptureAndMutableLambdaWithArgs) {
  int a = 1;
  int b = 2;
  ams::Function<int, int, int> f([&](int c, int d) mutable {
    return a + b + c + d;
  });
  EXPECT_EQ(f(3, 4), 10);
}

TEST(Function, FunctionLambdaCopyAssignment) {
  ams::Function<void> f;
  f = []() {};
  EXPECT_TRUE(f);
}

TEST(Function, FunctionLambdaMoveAssignment) {
  ams::Function<void> f;
  f = std::move([]() {});
  EXPECT_TRUE(f);
}

TEST(Function, FunctionArgumentPassAsLambdaExpression) {
  auto fn = [](ams::Function<void> f) {
    f();
  };
  fn({[]() {}});
}

