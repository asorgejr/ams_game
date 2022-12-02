

#include <gtest/gtest.h>

import ams;

struct Dummy {
  int member = 42;
};

TEST(NotifyingUniquePtr, Init) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  EXPECT_NE(ptr, nullptr);
  EXPECT_NE(ptr.get(), nullptr);
  EXPECT_EQ(*ptr, 5);
}

TEST(NotifyingUniquePtr, Move) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  auto&& ptr2 = std::move(ptr);
  EXPECT_EQ(*ptr2, 5);
}


TEST(NotifyingUniquePtr, MoveAssign) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  auto ptr2 = ams::makeNotifyingUnique<int>(6);
  ptr2 = std::move(ptr);
  EXPECT_EQ(*ptr2, 5);
}

TEST(NotifyingUniquePtr, MoveAssignNull) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  auto ptr2 = ams::makeNotifyingUnique<int>(6);
  ptr2 = std::move(ptr);
  EXPECT_EQ(ptr, nullptr);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(NotifyingUniquePtr, DerefNullThrowsException) {
  auto ptr = ams::makeNotifyingUnique<Dummy>();
  ptr = nullptr;
  if constexpr (ams::AMSExceptions) {
    EXPECT_THROW(*ptr, ams::NullPointerException);
  }
}

TEST(NotifyingUniquePtr, ArrowNullThrowsException) {
  auto ptr = ams::makeNotifyingUnique<Dummy>();
  ptr = nullptr;
  if constexpr (ams::AMSExceptions) {
    EXPECT_THROW(ptr->member, ams::NullPointerException);
  }
}

TEST(PtrToUnique, ConstructFromNUP) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  auto ptr2 = ams::PtrToUnique<int>(ptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(*ptr2, 5);
}

TEST(PtrToUnique, ConstructFromNUPNull) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  ptr = nullptr;
  auto ptr2 = ams::PtrToUnique<int>(ptr);
  EXPECT_EQ(ptr2, nullptr);
}

TEST(PtrToUnique, DerefNullThrowsException) {
  auto ptr = ams::makeNotifyingUnique<Dummy>();
  ptr = nullptr;
  auto ptr2 = ams::PtrToUnique<Dummy>(ptr);
  if constexpr (ams::AMSExceptions) {
    EXPECT_THROW(*ptr2, ams::NullPointerException);
  }
}

TEST(PtrToUnique, ArrowNullThrowsException) {
  auto ptr = ams::makeNotifyingUnique<Dummy>();
  ptr = nullptr;
  auto ptr2 = ams::PtrToUnique<Dummy>(ptr);
  if constexpr (ams::AMSExceptions) {
    EXPECT_THROW(ptr2->member, ams::NullPointerException);
  }
}

TEST(PtrToUnique, NoDangling) {
  auto ptr = ams::makeNotifyingUnique<int>(5);
  auto ptr2 = ams::PtrToUnique<int>(ptr);
  ptr = nullptr;
  EXPECT_EQ(ptr2, nullptr);
}

TEST(PtrToUnique, NoDanglingOutOfScope) {
  auto ptr = ams::PtrToUnique<int>();
  {
    auto ptr2 = ams::makeNotifyingUnique<int>(5);
    ptr = ams::PtrToUnique<int>(ptr2);
    EXPECT_EQ(*ptr, 5);
  }
  EXPECT_EQ(ptr, nullptr);
}
