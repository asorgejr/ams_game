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
#include <ams/List.hpp>
#include <ams/config.hpp>
#else
import ams.List;
import ams.config;
#endif

using std::cout;
using std::endl;

using namespace ams;

TEST(List, Init) {
  List<int> list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.empty(), true);
}

TEST(List, BeginEnd) {
  List<int> list(1);
  EXPECT_EQ(*list.begin(), 0);
  EXPECT_EQ(*(list.end()-1), 0);
}

TEST(List, InitWithSize) {
  List<int> list(10);
  EXPECT_EQ(list.size(), 10);
  EXPECT_EQ(list.empty(), false);
  EXPECT_NE(list.begin(), list.end());
  EXPECT_NE(list.cbegin(), list.cend());
}

TEST(List, InitWithSizeAndValue) {
  List<int> list(10, 5);
  EXPECT_EQ(list.size(), 10);
  EXPECT_EQ(list.empty(), false);
  EXPECT_NE(list.begin(), list.end());
  EXPECT_NE(list.cbegin(), list.cend());
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(*it, 5);
  }
}

TEST(List, InitializerList) {
  List<int> list{1, 2, 3};
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(list.begin(), list.end() - 3);
  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*list.begin()+1, 2);
  EXPECT_EQ(*list.begin()+2, 3);
}

TEST(List, Subscript) {
  List<int> list{1, 2};
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
}

TEST(List, PushBack) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
}

TEST(List, PushFront) {
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list[0], 2);
  EXPECT_EQ(list[1], 1);
}

TEST(List, PopBack) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.pop_back();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list[0], 1);
}

TEST(List, PopFront) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list[0], 2);
}

TEST(List, Copy) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  List<int> list2 = list;
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

TEST(List, Move) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  List<int> list2 = std::move(list);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

TEST(List, CopyAssignment) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  List<int> list2;
  list2 = list;
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

TEST(List, MoveAssignment) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  List<int> list2;
  list2 = std::move(list);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

TEST(List, Iterator) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  int i = 1;
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(List, ConstIterator) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  int i = 1;
  for (auto it = list.cbegin(); it != list.cend(); ++it) {
    EXPECT_EQ(*it, i);
    i++;
  }
}

TEST(List, ReverseIterator) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  int i = 2;
  for (auto it = list.rbegin(); it != list.rend(); ++it) {
    EXPECT_EQ(*it, i);
    i--;
  }
}

TEST(List, ConstReverseIterator) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  int i = 2;
  for (auto it = list.crbegin(); it != list.crend(); ++it) {
    EXPECT_EQ(*it, i);
    i--;
  }
}

TEST(List, Front) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.front(), 1);
}

TEST(List, Back) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.back(), 2);
}

TEST(List, Erase) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.size(), 3);
  list.erase(list.begin());
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list[0], 2);
  EXPECT_EQ(list[1], 3);
}

TEST(List, Insert) {
  List<int> list;
  list.push_back(1);
  list.insert(list.begin(), 2);
}

TEST(List, Clear) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

TEST(List, Swap) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  List<int> list2;
  list2.push_back(3);
  list2.push_back(4);
  list.swap(list2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list[0], 3);
  EXPECT_EQ(list[1], 4);
  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

TEST(List, Empty) {
  List<int> list;
  EXPECT_EQ(list.empty(), true);
  list.push_back(1);
  EXPECT_EQ(list.empty(), false);
}

TEST(List, Resize) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.size(), 2);
  list.resize(4, 3);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
  EXPECT_EQ(list[3], 3);
}

TEST(List, ResizeLess) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(list.size(), 2);
  list.resize(1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list[0], 1);
}

TEST(List, NegativeIndex) {
  List<int, std::allocator<int>, true> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list[-1], 3);
  EXPECT_EQ(list[-2], 2);
  EXPECT_EQ(list[-3], 1);
}

TEST(List, ShrinkToFit) {
  List<int> list;
  list.reserve(100);
  EXPECT_EQ(list.capacity(), 100);
  list.push_back(1);
  list.push_back(2);
  list.shrink_to_fit();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.capacity(), 2);
}

TEST(List, Slice) {
  List<int> list{1, 2, 3, 4, 5};
  auto slice = list.slice(1, 3);
  EXPECT_EQ(slice.size(), 2);
  EXPECT_EQ(slice[0], 2);
  EXPECT_EQ(slice[1], 3);
}

TEST(List, SliceNegative) {
  List<int, std::allocator<int>, true> list{1, 2, 3, 4, 5};
  auto slice = list.slice(-3, -1);
  EXPECT_EQ(slice.size(), 2);
  EXPECT_EQ(slice[0], 3);
  EXPECT_EQ(slice[1], 4);
}

TEST(List, SliceBackwards) {
  List<int> list{1, 2, 3, 4, 5};
  auto slice = list.slice(3, 1);
  EXPECT_EQ(slice.size(), 2);
  EXPECT_EQ(slice[0], 4);
  EXPECT_EQ(slice[1], 3);
}


#ifdef AMS_EXCEPTIONS

TEST(List, IteratorRangeCtorFirstGTLastException) {
  List<int> list{1, 2, 3, 4, 5};
  EXPECT_THROW(List<int> list2(list.begin() + 3, list.begin() + 1), std::invalid_argument);
}

TEST(List, SubscriptException) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_THROW(list[2], std::out_of_range);
}

TEST(List, AtException) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_THROW(list.at(2), std::out_of_range);
}

TEST(List, NegativeIndexWithNegativeIndexingException) {
  List<int, std::allocator<int>, true> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_NO_THROW(list[-2]);
  EXPECT_THROW(list[-4], std::out_of_range);
}

TEST(List, NegativeIndexWithoutNegativeIndexingException) {
  List<int, std::allocator<int>, false> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_THROW(list[-1], std::out_of_range);
}

TEST(List, AtNegativeIndexWithNegativeIndexingException) {
  List<int, std::allocator<int>, true> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_NO_THROW(list.at(-2));
  EXPECT_THROW(list.at(-4), std::out_of_range);
}

TEST(List, AtNegativeIndexWithoutNegativeIndexingException) {
  List<int, std::allocator<int>, false> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_THROW(list.at(-1), std::out_of_range);
}

#endif
