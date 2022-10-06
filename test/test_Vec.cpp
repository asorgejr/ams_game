//
// Created by asorgejr on 9/25/2022.
//

#include <gtest/gtest.h>

#ifndef AMS_MODULES
#include "ams/Vec.hpp"
#else
import ams.Vec;
#endif

struct V2Tst {
  double x = 0;
  double y = 0;
};

struct V3Tst {
  double x = 0;
  double y = 0;
  double z = 0;
};

struct V4Tst {
  double x = 0;
  double y = 0;
  double z = 0;
  double w = 0;
};

#pragma region Vec2
TEST(Vec2, Vec2) {
  ams::Vec2<int> v{1, 2};
  EXPECT_EQ(v.x, 1);
  EXPECT_EQ(v.y, 2);
}

TEST(Vec2, CopyAssignment) {
  ams::Vec2<int> v{1, 2};
  ams::Vec2<int> v2 = v;
  EXPECT_EQ(v2.x, 1);
  EXPECT_EQ(v2.y, 2);
}

TEST(Vec2, Subscript) {
  ams::Vec2<int> v{1, 2};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(Vec2, Add) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  auto v3 = v1 + v2;
  EXPECT_EQ(v3.x, 4);
  EXPECT_EQ(v3.y, 6);
}

TEST(Vec2, Sub) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  auto v3 = v1 - v2;
  EXPECT_EQ(v3.x, -2);
  EXPECT_EQ(v3.y, -2);
}

TEST(Vec2, Mul) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  auto v3 = v1 * v2;
  EXPECT_EQ(v3.x, 3);
  EXPECT_EQ(v3.y, 8);
}

TEST(Vec2, Div) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  auto v3 = v1 / v2;
  EXPECT_EQ(v3.x, 1 / 3);
  EXPECT_EQ(v3.y, 2 / 4);
}

TEST(Vec2, Mod) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  auto v3 = v1 % v2;
  EXPECT_EQ(v3.x, 1 % 3);
  EXPECT_EQ(v3.y, 2 % 4);
}

TEST(Vec2, AddAssign) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  v1 += v2;
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 6);
}

TEST(Vec2, SubAssign) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  v1 -= v2;
  EXPECT_EQ(v1.x, -2);
  EXPECT_EQ(v1.y, -2);
}

TEST(Vec2, MulAssign) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  v1 *= v2;
  EXPECT_EQ(v1.x, 3);
  EXPECT_EQ(v1.y, 8);
}

TEST(Vec2, DivAssign) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  v1 /= v2;
  EXPECT_EQ(v1.x, 1 / 3);
  EXPECT_EQ(v1.y, 2 / 4);
}

TEST(Vec2, ModAssign) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{3, 4};
  v1 %= v2;
  EXPECT_EQ(v1.x, 1 % 3);
  EXPECT_EQ(v1.y, 2 % 4);
}

TEST(Vec2, AddScalar) {
  ams::Vec2<int> v1{1, 2};
  auto v3 = v1 + 2;
  EXPECT_EQ(v3.x, 3);
  EXPECT_EQ(v3.y, 4);
}

TEST(Vec2, SubScalar) {
  ams::Vec2<int> v1{1, 2};
  auto v3 = v1 - 2;
  EXPECT_EQ(v3.x, -1);
  EXPECT_EQ(v3.y, 0);
}

TEST(Vec2, MulScalar) {
  ams::Vec2<int> v1{1, 2};
  auto v3 = v1 * 2;
  EXPECT_EQ(v3.x, 2);
  EXPECT_EQ(v3.y, 4);
}

TEST(Vec2, DivScalar) {
  ams::Vec2<int> v1{1, 2};
  auto v3 = v1 / 2;
  EXPECT_EQ(v3.x, 1 / 2);
  EXPECT_EQ(v3.y, 2 / 2);
}

TEST(Vec2, ModScalar) {
  ams::Vec2<int> v1{1, 2};
  auto v3 = v1 % 2;
  EXPECT_EQ(v3.x, 1 % 2);
  EXPECT_EQ(v3.y, 2 % 2);
}

TEST(Vec2, AddAssignScalar) {
  ams::Vec2<int> v1{1, 2};
  v1 += 2;
  EXPECT_EQ(v1.x, 3);
  EXPECT_EQ(v1.y, 4);
}

TEST(Vec2, SubAssignScalar) {
  ams::Vec2<int> v1{1, 2};
  v1 -= 2;
  EXPECT_EQ(v1.x, -1);
  EXPECT_EQ(v1.y, 0);
}

TEST(Vec2, MulAssignScalar) {
  ams::Vec2<int> v1{1, 2};
  v1 *= 2;
  EXPECT_EQ(v1.x, 2);
  EXPECT_EQ(v1.y, 4);
}

TEST(Vec2, DivAssignScalar) {
  ams::Vec2<int> v1{1, 2};
  v1 /= 2;
  EXPECT_EQ(v1.x, 1 / 2);
  EXPECT_EQ(v1.y, 2 / 2);
}

TEST(Vec2, ModAssignScalar) {
  ams::Vec2<int> v1{1, 2};
  v1 %= 2;
  EXPECT_EQ(v1.x, 1 % 2);
  EXPECT_EQ(v1.y, 2 % 2);
}

TEST(Vec2, CustomVecEq) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{2, 4};
  v1 = v2;
  EXPECT_EQ(v1.x, 2);
  EXPECT_EQ(v1.y, 4);
}

TEST(Vec2, CustomVecAdd) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{3, 4};
  auto v3 = v1 + v2;
  v1 += v2;
  EXPECT_EQ(v3.x, 4);
  EXPECT_EQ(v3.y, 6);
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 6);
}

TEST(Vec2, CustomVecSub) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{3, 4};
  auto v3 = v1 - v2;
  v1 -= v2;
  EXPECT_EQ(v3.x, -2);
  EXPECT_EQ(v3.y, -2);
  EXPECT_EQ(v1.x, -2);
  EXPECT_EQ(v1.y, -2);
}

TEST(Vec2, CustomVecMul) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{3, 4};
  auto v3 = v1 * v2;
  v1 *= v2;
  EXPECT_EQ(v3.x, 3);
  EXPECT_EQ(v3.y, 8);
  EXPECT_EQ(v1.x, 3);
  EXPECT_EQ(v1.y, 8);
}

TEST(Vec2, CustomVecDiv) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{3, 4};
  auto v3 = v1 / v2;
  v1 /= v2;
  EXPECT_EQ(v3.x, 1 / 3);
  EXPECT_EQ(v3.y, 2 / 4);
  EXPECT_EQ(v1.x, 1 / 3);
  EXPECT_EQ(v1.y, 2 / 4);
}

TEST(Vec2, CustomVecMod) {
  ams::Vec2<int> v1{1, 2};
  V2Tst v2{3, 4};
  auto v3 = v1 % v2;
  v1 %= v2;
  EXPECT_EQ(v3.x, 1 % 3);
  EXPECT_EQ(v3.y, 2 % 4);
  EXPECT_EQ(v1.x, 1 % 3);
  EXPECT_EQ(v1.y, 2 % 4);
}

TEST(Vec2, EQOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
}

TEST(Vec2, NEQOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
}

TEST(Vec2, GTOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v1 > v3);
  EXPECT_TRUE(v3 > v1);
}

TEST(Vec2, GTEOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_TRUE(v1 >= v2);
  EXPECT_FALSE(v1 >= v3);
  EXPECT_TRUE(v3 >= v1);
}

TEST(Vec2, LTOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_FALSE(v1 < v2);
  EXPECT_TRUE(v1 < v3);
  EXPECT_FALSE(v3 < v1);
}

TEST(Vec2, LTEOperator) {
  ams::Vec2<int> v1{1, 2};
  ams::Vec2<int> v2{1, 2};
  ams::Vec2<int> v3{3, 4};
  EXPECT_TRUE(v1 <= v2);
  EXPECT_TRUE(v1 <= v3);
  EXPECT_FALSE(v3 <= v1);
}

TEST(Vec2, SupportFunction_RemapScalar) {
  ams::Vec2<float> v{1.0f, 2.0f};
  auto v2 = ams::remap(v, 0.0f, 1.0f, 0.0f, 10.0f);
  EXPECT_FLOAT_EQ(v2.x, 10.0f);
  EXPECT_FLOAT_EQ(v2.y, 20.0f);
}

TEST(Vec2, SupportFunction_RemapVec) {
  ams::Vec2<float> v{1.0f, 2.0f};
  auto v2 = ams::remap<float>(v, ams::Vec2{0.0f, 0.0f}, ams::Vec2{1.0f, 1.0f}, ams::Vec2{0.0f, 0.0f}, ams::Vec2{10.0f, 10.0f});
  EXPECT_FLOAT_EQ(v2.x, 10.0f);
  EXPECT_FLOAT_EQ(v2.y, 20.0f);
}

TEST(Vec2, SupportFunction_ClampScalar) {
  ams::Vec2<float> v{-1.0f, 2.0f};
  auto v2 = ams::clamp(v, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(v2.x, 0.0f);
  EXPECT_FLOAT_EQ(v2.y, 1.0f);
}

TEST(Vec2, SupportFunction_ClampVec) {
  ams::Vec2<float> v{-1.0f, 2.0f};
  auto v2 = ams::clamp<float>(v, ams::Vec2{0.0f, 0.0f}, ams::Vec2{1.0f, 1.0f});
  EXPECT_FLOAT_EQ(v2.x, 0.0f);
  EXPECT_FLOAT_EQ(v2.y, 1.0f);
}

TEST(Vec2, SupportFunction_WrapScalar) {
  ams::Vec2<float> v{0.5f, 1.5f};
  auto v2 = ams::wrap(v, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
}

TEST(Vec2, SupportFunction_WrapVec) {
  ams::Vec2<float> v{0.5f, 1.5f};
  auto v2 = ams::wrap<float>(v, ams::Vec2<float>{0.0f, 0.0f}, ams::Vec2<float>{1.0f, 1.0f});
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
}

TEST(Vec2, SupportFunction_Distance) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  ams::Vec2<float> v2{1.0f, 1.0f};
  auto d = ams::distance<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, std::sqrt(2.0f));
}

TEST(Vec2, SupportFunction_DistanceAmbiguousReturn) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  V2Tst v2{1.0f, 1.0f};
  auto d = ams::distance(v1, v2);
  EXPECT_DOUBLE_EQ(d, std::sqrt(2.0));
}

TEST(Vec2, SupportFunction_DistanceT2) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  V2Tst v2{1.0f, 1.0f};
  auto d = ams::distance<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, std::sqrt(2.0f));
}

TEST(Vec2, SupportFunction_Distance2) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  ams::Vec2<float> v2{1.0f, 1.0f};
  auto d = ams::distance2<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec2, SupportFunction_Distance2AmbiguousReturn) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  V2Tst v2{1.0f, 1.0f};
  auto d = ams::distance2(v1, v2);
  EXPECT_DOUBLE_EQ(d, 2.0);
}

TEST(Vec2, SupportFunction_Distance2T2) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  V2Tst v2{1.0f, 1.0f};
  auto d = ams::distance2<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec2, SupportFunction_Length) {
  ams::Vec2<float> v{1.0f, 1.0f};
  auto l = ams::length<float>(v);
  EXPECT_FLOAT_EQ(l, std::sqrt(2.0f));
}

TEST(Vec2, SupportFunction_LengthAmbiguousReturn) {
  ams::Vec2<float> v{1.0f, 1.0f};
  auto l = ams::length(v);
  EXPECT_DOUBLE_EQ(l, std::sqrt(2.0));
}

TEST(Vec2, SupportFunction_Length2) {
  ams::Vec2<float> v{1.0f, 1.0f};
  auto l = ams::length2<float>(v);
  EXPECT_FLOAT_EQ(l, 2.0f);
}

TEST(Vec2, SupportFunction_Length2AmbiguousReturn) {
  ams::Vec2<float> v{1.0f, 1.0f};
  auto l = ams::length2(v);
  EXPECT_DOUBLE_EQ(l, 2.0);
}

TEST(Vec2, SupportFunction_Dot) {
  ams::Vec2<float> v1{1.0f, 1.0f};
  ams::Vec2<float> v2{1.0f, 1.0f};
  auto d = ams::dot<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec2, SupportFunction_DotAmbiguousReturn) {
  ams::Vec2<float> v1{1.0f, 1.0f};
  ams::Vec2<float> v2{1.0f, 1.0f};
  auto d = ams::dot(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec2, SupportFunction_DotT2) {
  ams::Vec2<float> v1{1.0f, 1.0f};
  V2Tst v2{1.0f, 1.0f};
  auto d = ams::dot<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec2, SupportFunction_Cross) {
  ams::Vec2<float> v1{1.0f, 0.0f};
  ams::Vec2<float> v2{1.0f, 0.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 0.0f);
  EXPECT_FLOAT_EQ(v3.y, 0.0f);
}

TEST(Vec2, SupportFunction_CrossT2) {
  ams::Vec2<float> v1{1.0f, 1.0f};
  V2Tst v2{1.0f, 1.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 0.0f);
  EXPECT_FLOAT_EQ(v3.y, 0.0f);
}

TEST(Vec2, SupportFunction_Normalize) {
  ams::Vec2<float> v{2.0f, 2.0f};
  auto v2 = ams::normalize(v);
  EXPECT_FLOAT_EQ(v2.x, 1.0f / std::sqrt(2.0f));
  EXPECT_FLOAT_EQ(v2.y, 1.0f / std::sqrt(2.0f));
}

TEST(Vec2, SupportFunction_Lerp) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  ams::Vec2<float> v2{1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
}

TEST(Vec2, SupportFunction_LerpT2) {
  ams::Vec2<float> v1{0.0f, 0.0f};
  V2Tst v2{1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
}

#pragma endregion Vec2


#pragma region Vec3
TEST(Vec3, Vec3) {
  ams::Vec3<int> v{1, 2, 3};
  EXPECT_EQ(v.x, 1);
  EXPECT_EQ(v.y, 2);
  EXPECT_EQ(v.z, 3);
}

TEST(Vec3, CopyAssignment) {
  ams::Vec3<int> v{1, 2, 3};
  ams::Vec3<int> v2 = v;
  EXPECT_EQ(v2.x, 1);
  EXPECT_EQ(v2.y, 2);
  EXPECT_EQ(v2.z, 3);
}

TEST(Vec3, Subscript) {
  ams::Vec3<int> v{1, 2, 3};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(Vec3, Add) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  auto v3 = v1 + v2;
  EXPECT_EQ(v3.x, 5);
  EXPECT_EQ(v3.y, 7);
  EXPECT_EQ(v3.z, 9);
}

TEST(Vec3, Sub) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  auto v3 = v1 - v2;
  EXPECT_EQ(v3.x, -3);
  EXPECT_EQ(v3.y, -3);
  EXPECT_EQ(v3.z, -3);
}

TEST(Vec3, Mul) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  auto v3 = v1 * v2;
  EXPECT_EQ(v3.x, 4);
  EXPECT_EQ(v3.y, 10);
  EXPECT_EQ(v3.z, 18);
}

TEST(Vec3, Div) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  auto v3 = v1 / v2;
  EXPECT_EQ(v3.x, 1 / 4);
  EXPECT_EQ(v3.y, 2 / 5);
  EXPECT_EQ(v3.z, 3 / 6);
}

TEST(Vec3, Mod) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  auto v3 = v1 % v2;
  EXPECT_EQ(v3.x, 1 % 4);
  EXPECT_EQ(v3.y, 2 % 5);
  EXPECT_EQ(v3.z, 3 % 6);
}

TEST(Vec3, AddAssign) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  v1 += v2;
  EXPECT_EQ(v1.x, 5);
  EXPECT_EQ(v1.y, 7);
  EXPECT_EQ(v1.z, 9);
}

TEST(Vec3, SubAssign) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  v1 -= v2;
  EXPECT_EQ(v1.x, -3);
  EXPECT_EQ(v1.y, -3);
  EXPECT_EQ(v1.z, -3);
}

TEST(Vec3, MulAssign) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  v1 *= v2;
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 10);
  EXPECT_EQ(v1.z, 18);
}

TEST(Vec3, DivAssign) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  v1 /= v2;
  EXPECT_EQ(v1.x, 1 / 4);
  EXPECT_EQ(v1.y, 2 / 5);
  EXPECT_EQ(v1.z, 3 / 6);
}

TEST(Vec3, ModAssign) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{4, 5, 6};
  v1 %= v2;
  EXPECT_EQ(v1.x, 1 % 4);
  EXPECT_EQ(v1.y, 2 % 5);
  EXPECT_EQ(v1.z, 3 % 6);
}

TEST(Vec3, AddScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  auto v3 = v1 + 2;
  EXPECT_EQ(v3.x, 3);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v3.z, 5);
}

TEST(Vec3, SubScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  auto v3 = v1 - 2;
  EXPECT_EQ(v3.x, -1);
  EXPECT_EQ(v3.y, 0);
  EXPECT_EQ(v3.z, 1);
}

TEST(Vec3, MulScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  auto v3 = v1 * 2;
  EXPECT_EQ(v3.x, 2);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v3.z, 6);
}

TEST(Vec3, DivScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  auto v3 = v1 / 2;
  EXPECT_EQ(v3.x, 1 / 2);
  EXPECT_EQ(v3.y, 2 / 2);
  EXPECT_EQ(v3.z, 3 / 2);
}

TEST(Vec3, ModScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  auto v3 = v1 % 2;
  EXPECT_EQ(v3.x, 1 % 2);
  EXPECT_EQ(v3.y, 2 % 2);
  EXPECT_EQ(v3.z, 3 % 2);
}

TEST(Vec3, AddAssignScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  v1 += 2;
  EXPECT_EQ(v1.x, 3);
  EXPECT_EQ(v1.y, 4);
  EXPECT_EQ(v1.z, 5);
}

TEST(Vec3, SubAssignScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  v1 -= 2;
  EXPECT_EQ(v1.x, -1);
  EXPECT_EQ(v1.y, 0);
  EXPECT_EQ(v1.z, 1);
}

TEST(Vec3, MulAssignScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  v1 *= 2;
  EXPECT_EQ(v1.x, 2);
  EXPECT_EQ(v1.y, 4);
  EXPECT_EQ(v1.z, 6);
}

TEST(Vec3, DivAssignScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  v1 /= 2;
  EXPECT_EQ(v1.x, 1 / 2);
  EXPECT_EQ(v1.y, 2 / 2);
  EXPECT_EQ(v1.z, 3 / 2);
}

TEST(Vec3, ModAssignScalar) {
  ams::Vec3<int> v1{1, 2, 3};
  v1 %= 2;
  EXPECT_EQ(v1.x, 1 % 2);
  EXPECT_EQ(v1.y, 2 % 2);
  EXPECT_EQ(v1.z, 3 % 2);
}

TEST(Vec3, CustomVecEq) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{1, 2, 3};
  EXPECT_EQ(v1.x, v2.x);
  EXPECT_EQ(v1.y, v2.y);
  EXPECT_EQ(v1.z, v2.z);
}

TEST(Vec3, CustomVecAdd) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{4, 5, 6};
  auto v3 = v1 + v2;
  v1 += v2;
  EXPECT_EQ(v3.x, 5);
  EXPECT_EQ(v3.y, 7);
  EXPECT_EQ(v3.z, 9);
  EXPECT_EQ(v1.x, 5);
  EXPECT_EQ(v1.y, 7);
  EXPECT_EQ(v1.z, 9);
}

TEST(Vec3, CustomVecSub) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{4, 5, 6};
  auto v3 = v1 - v2;
  v1 -= v2;
  EXPECT_EQ(v3.x, -3);
  EXPECT_EQ(v3.y, -3);
  EXPECT_EQ(v3.z, -3);
  EXPECT_EQ(v1.x, -3);
  EXPECT_EQ(v1.y, -3);
  EXPECT_EQ(v1.z, -3);
}

TEST(Vec3, CustomVecMul) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{4, 5, 6};
  auto v3 = v1 * v2;
  v1 *= v2;
  EXPECT_EQ(v3.x, 4);
  EXPECT_EQ(v3.y, 10);
  EXPECT_EQ(v3.z, 18);
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 10);
  EXPECT_EQ(v1.z, 18);
}

TEST(Vec3, CustomVecDiv) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{4, 5, 6};
  auto v3 = v1 / v2;
  v1 /= v2;
  EXPECT_EQ(v3.x, 1 / 4);
  EXPECT_EQ(v3.y, 2 / 5);
  EXPECT_EQ(v3.z, 3 / 6);
  EXPECT_EQ(v1.x, 1 / 4);
  EXPECT_EQ(v1.y, 2 / 5);
  EXPECT_EQ(v1.z, 3 / 6);
}

TEST(Vec3, CustomVecMod) {
  ams::Vec3<int> v1{1, 2, 3};
  V3Tst v2{4, 5, 6};
  auto v3 = v1 % v2;
  v1 %= v2;
  EXPECT_EQ(v3.x, 1 % 4);
  EXPECT_EQ(v3.y, 2 % 5);
  EXPECT_EQ(v3.z, 3 % 6);
  EXPECT_EQ(v1.x, 1 % 4);
  EXPECT_EQ(v1.y, 2 % 5);
  EXPECT_EQ(v1.z, 3 % 6);
}

TEST(Vec3, EQOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
}

TEST(Vec3, NEQOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
}

TEST(Vec3, GTOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v1 > v3);
  EXPECT_TRUE(v3 > v1);
}

TEST(Vec3, GTEOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_TRUE(v1 >= v2);
  EXPECT_FALSE(v1 >= v3);
  EXPECT_TRUE(v3 >= v1);
}

TEST(Vec3, LTOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_FALSE(v1 < v2);
  EXPECT_TRUE(v1 < v3);
  EXPECT_FALSE(v3 < v1);
}

TEST(Vec3, LTEOperator) {
  ams::Vec3<int> v1{1, 2, 3};
  ams::Vec3<int> v2{1, 2, 3};
  ams::Vec3<int> v3{4, 5, 6};
  EXPECT_TRUE(v1 <= v2);
  EXPECT_TRUE(v1 <= v3);
  EXPECT_FALSE(v3 <= v1);
}

TEST(Vec3, SupportFunction_RemapScalar) {
  ams::Vec3<float> v{0.0f, 2.0f, 3.0f};
  auto v2 = ams::remap(v, 0.0f, 1.0f, 0.0f, 10.0f);
  EXPECT_EQ(v2.x, 0.0f);
  EXPECT_EQ(v2.y, 20.0f);
  EXPECT_EQ(v2.z, 30.0f);
}

TEST(Vec3, SupportFunction_RemapVec) {
  ams::Vec3<float> v{0.0f, 2.0f, 3.0f};
  auto v2 = ams::remap<float>(v, ams::Vec3{0.0f, 0.0f, 0.0f}, ams::Vec3{1.0f, 1.0f, 1.0f}, ams::Vec3{0.0f, 0.0f, 0.0f}, ams::Vec3{10.0f, 10.0f, 10.0f});
  EXPECT_EQ(v2.x, 0.0f);
  EXPECT_EQ(v2.y, 20.0f);
  EXPECT_EQ(v2.z, 30.0f);
}

TEST(Vec3, SupportFunction_ClampScalar) {
  ams::Vec3<float> v{0.0f, 2.0f, 3.0f};
  auto v2 = ams::clamp<float>(v, 0.0f, 1.0f);
  EXPECT_EQ(v2.x, 0.0f);
  EXPECT_EQ(v2.y, 1.0f);
  EXPECT_EQ(v2.z, 1.0f);
}

TEST(Vec3, SupportFunction_ClampVec) {
  ams::Vec3<float> v{0.0f, 2.0f, 3.0f};
  auto v2 = ams::clamp<float>(v, ams::Vec3{0.0f, 0.0f, 0.0f}, ams::Vec3{1.0f, 1.0f, 1.0f});
  EXPECT_EQ(v2.x, 0.0f);
  EXPECT_EQ(v2.y, 1.0f);
  EXPECT_EQ(v2.z, 1.0f);
}

TEST(Vec3, SupportFunction_WrapScalar) {
  ams::Vec3<float> v{0.5f, 1.5f, 2.5f};
  auto v2 = ams::wrap<float>(v, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 0.5f);
}

TEST(Vec3, SupportFunction_WrapVec) {
  ams::Vec3<float> v{0.5f, 1.5f, 2.5f};
  auto v2 = ams::wrap<float>(v, ams::Vec3{0.0f, 0.0f, 0.0f}, ams::Vec3{1.0f, 1.0f, 1.0f});
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 0.5f);
}

TEST(Vec3, SupportFunction_Distance) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 1.7320508075688772f);
}

TEST(Vec3, SupportFunction_DistanceAmbiguousReturn) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance(v1, v2);
  EXPECT_DOUBLE_EQ(d, 1.7320508075688772);
}

TEST(Vec3, SupportFunction_DistanceT2) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  V3Tst v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 1.7320508075688772f);
}

TEST(Vec3, SupportFunction_Distance2) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance2<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 3.0f);
}

TEST(Vec3, SupportFunction_Distance2AmbiguousReturn) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance2(v1, v2);
  EXPECT_DOUBLE_EQ(d, 3.0);
}

TEST(Vec3, SupportFunction_Distance2T2) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  V3Tst v2{1.0f, 1.0f, 1.0f};
  auto d = ams::distance2<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 3.0f);
}

TEST(Vec3, SupportFunction_Length) {
  ams::Vec3<float> v{1.0f, 1.0f, 1.0f};
  auto l = ams::length<float>(v);
  EXPECT_FLOAT_EQ(l, 1.7320508075688772f);
}

TEST(Vec3, SupportFunction_LengthAmbiguousReturn) {
  ams::Vec3<float> v{1.0f, 1.0f, 1.0f};
  auto l = ams::length(v);
  EXPECT_DOUBLE_EQ(l, 1.7320508075688772);
}

TEST(Vec3, SupportFunction_Length2) {
  ams::Vec3<float> v{1.0f, 1.0f, 1.0f};
  auto l = ams::length2<float>(v);
  EXPECT_FLOAT_EQ(l, 3.0f);
}

TEST(Vec3, SupportFunction_Length2AmbiguousReturn) {
  ams::Vec3<float> v{1.0f, 1.0f, 1.0f};
  auto l = ams::length2(v);
  EXPECT_DOUBLE_EQ(l, 3.0);
}

TEST(Vec3, SupportFunction_Dot) {
  ams::Vec3<float> v1{1.0f, 1.0f, 1.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::dot<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 3.0f);
}

TEST(Vec3, SupportFunction_DotAmbiguousReturn) {
  ams::Vec3<float> v1{1.0f, 1.0f, 1.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto d = ams::dot(v1, v2);
  EXPECT_DOUBLE_EQ(d, 3.0);
}

TEST(Vec3, SupportFunction_DotT2) {
  ams::Vec3<float> v1{1.0f, 1.0f, 1.0f};
  V3Tst v2{1.0f, 1.0f, 1.0f};
  auto d = ams::dot<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 3.0f);
}

TEST(Vec3, SupportFunction_Cross) {
  ams::Vec3<float> v1{1.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{0.0f, 1.0f, 0.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 0.0f);
  EXPECT_FLOAT_EQ(v3.y, 0.0f);
  EXPECT_FLOAT_EQ(v3.z, 1.0f);
}

TEST(Vec3, SupportFunction_CrossT2) {
  ams::Vec3<float> v1{1.0f, 0.0f, 0.0f};
  V3Tst v2{0.0f, 1.0f, 0.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 0.0f);
  EXPECT_FLOAT_EQ(v3.y, 0.0f);
  EXPECT_FLOAT_EQ(v3.z, 1.0f);
}

TEST(Vec3, SupportFunction_Normalize) {
  ams::Vec3<float> v{2.0f, 2.0f, 2.0f};
  auto v2 = ams::normalize(v);
  EXPECT_FLOAT_EQ(v2.x, 0.5773502691896258f);
  EXPECT_FLOAT_EQ(v2.y, 0.5773502691896258f);
  EXPECT_FLOAT_EQ(v2.z, 0.5773502691896258f);
}

TEST(Vec3, SupportFunction_Lerp) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  ams::Vec3<float> v2{1.0f, 1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
  EXPECT_FLOAT_EQ(v3.z, 0.5f);
}

TEST(Vec3, SupportFunction_LerpT2) {
  ams::Vec3<float> v1{0.0f, 0.0f, 0.0f};
  V3Tst v2{1.0f, 1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
  EXPECT_FLOAT_EQ(v3.z, 0.5f);
}

#pragma endregion Vec3


#pragma region Vec4
TEST(Vec4, Vec4) {
  ams::Vec4<int> v{1, 2, 3, 4};
  EXPECT_EQ(v.x, 1);
  EXPECT_EQ(v.y, 2);
  EXPECT_EQ(v.z, 3);
  EXPECT_EQ(v.w, 4);
}

TEST(Vec4, CopyAssignment) {
  ams::Vec4<int> v{1, 2, 3, 4};
  ams::Vec4<int> v2 = v;
  EXPECT_EQ(v2.x, 1);
  EXPECT_EQ(v2.y, 2);
  EXPECT_EQ(v2.z, 3);
  EXPECT_EQ(v2.w, 4);
}

TEST(Vec4, Subscript) {
  ams::Vec4<int> v{1, 2, 3, 4};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(Vec4, Add) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  auto v3 = v1 + v2;
  EXPECT_EQ(v3.x, 6);
  EXPECT_EQ(v3.y, 8);
  EXPECT_EQ(v3.z, 10);
  EXPECT_EQ(v3.w, 12);
}

TEST(Vec4, Sub) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  auto v3 = v1 - v2;
  EXPECT_EQ(v3.x, -4);
  EXPECT_EQ(v3.y, -4);
  EXPECT_EQ(v3.z, -4);
  EXPECT_EQ(v3.w, -4);
}

TEST(Vec4, Mul) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  auto v3 = v1 * v2;
  EXPECT_EQ(v3.x, 5);
  EXPECT_EQ(v3.y, 12);
  EXPECT_EQ(v3.z, 21);
  EXPECT_EQ(v3.w, 32);
}

TEST(Vec4, Div) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  auto v3 = v1 / v2;
  EXPECT_EQ(v3.x, 1 / 5);
  EXPECT_EQ(v3.y, 2 / 6);
  EXPECT_EQ(v3.z, 3 / 7);
  EXPECT_EQ(v3.w, 4 / 8);
}

TEST(Vec4, Mod) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  auto v3 = v1 % v2;
  EXPECT_EQ(v3.x, 1 % 5);
  EXPECT_EQ(v3.y, 2 % 6);
  EXPECT_EQ(v3.z, 3 % 7);
  EXPECT_EQ(v3.w, 4 % 8);
}

TEST(Vec4, AddAssign) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  v1 += v2;
  EXPECT_EQ(v1.x, 6);
  EXPECT_EQ(v1.y, 8);
  EXPECT_EQ(v1.z, 10);
  EXPECT_EQ(v1.w, 12);
}

TEST(Vec4, SubAssign) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  v1 -= v2;
  EXPECT_EQ(v1.x, -4);
  EXPECT_EQ(v1.y, -4);
  EXPECT_EQ(v1.z, -4);
  EXPECT_EQ(v1.w, -4);
}

TEST(Vec4, MulAssign) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  v1 *= v2;
  EXPECT_EQ(v1.x, 5);
  EXPECT_EQ(v1.y, 12);
  EXPECT_EQ(v1.z, 21);
  EXPECT_EQ(v1.w, 32);
}

TEST(Vec4, DivAssign) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  v1 /= v2;
  EXPECT_EQ(v1.x, 1 / 5);
  EXPECT_EQ(v1.y, 2 / 6);
  EXPECT_EQ(v1.z, 3 / 7);
  EXPECT_EQ(v1.w, 4 / 8);
}

TEST(Vec4, ModAssign) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{5, 6, 7, 8};
  v1 %= v2;
  EXPECT_EQ(v1.x, 1 % 5);
  EXPECT_EQ(v1.y, 2 % 6);
  EXPECT_EQ(v1.z, 3 % 7);
  EXPECT_EQ(v1.w, 4 % 8);
}

TEST(Vec4, AddScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  auto v3 = v1 + 2;
  EXPECT_EQ(v3.x, 3);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v3.z, 5);
  EXPECT_EQ(v3.w, 6);
}

TEST(Vec4, SubScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  auto v3 = v1 - 2;
  EXPECT_EQ(v3.x, -1);
  EXPECT_EQ(v3.y, 0);
  EXPECT_EQ(v3.z, 1);
  EXPECT_EQ(v3.w, 2);
}

TEST(Vec4, MulScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  auto v3 = v1 * 2;
  EXPECT_EQ(v3.x, 2);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v3.z, 6);
  EXPECT_EQ(v3.w, 8);
}

TEST(Vec4, DivScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  auto v3 = v1 / 2;
  EXPECT_EQ(v3.x, 1 / 2);
  EXPECT_EQ(v3.y, 2 / 2);
  EXPECT_EQ(v3.z, 3 / 2);
  EXPECT_EQ(v3.w, 4 / 2);
}

TEST(Vec4, ModScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  auto v3 = v1 % 2;
  EXPECT_EQ(v3.x, 1 % 2);
  EXPECT_EQ(v3.y, 2 % 2);
  EXPECT_EQ(v3.z, 3 % 2);
  EXPECT_EQ(v3.w, 4 % 2);
}

TEST(Vec4, AddAssignScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  v1 += 2;
  EXPECT_EQ(v1.x, 3);
  EXPECT_EQ(v1.y, 4);
  EXPECT_EQ(v1.z, 5);
  EXPECT_EQ(v1.w, 6);
}

TEST(Vec4, SubAssignScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  v1 -= 2;
  EXPECT_EQ(v1.x, -1);
  EXPECT_EQ(v1.y, 0);
  EXPECT_EQ(v1.z, 1);
  EXPECT_EQ(v1.w, 2);
}

TEST(Vec4, MulAssignScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  v1 *= 2;
  EXPECT_EQ(v1.x, 2);
  EXPECT_EQ(v1.y, 4);
  EXPECT_EQ(v1.z, 6);
  EXPECT_EQ(v1.w, 8);
}

TEST(Vec4, DivAssignScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  v1 /= 2;
  EXPECT_EQ(v1.x, 1 / 2);
  EXPECT_EQ(v1.y, 2 / 2);
  EXPECT_EQ(v1.z, 3 / 2);
  EXPECT_EQ(v1.w, 4 / 2);
}

TEST(Vec4, ModAssignScalar) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  v1 %= 2;
  EXPECT_EQ(v1.x, 1 % 2);
  EXPECT_EQ(v1.y, 2 % 2);
  EXPECT_EQ(v1.z, 3 % 2);
  EXPECT_EQ(v1.w, 4 % 2);
}

TEST(Vec4, CustomVecEq) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{1, 2, 3, 4};
  v1 = v2;
  EXPECT_EQ(v1.x, 1);
  EXPECT_EQ(v1.y, 2);
  EXPECT_EQ(v1.z, 3);
  EXPECT_EQ(v1.w, 4);
}

TEST(Vec4, CustomVecAdd) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{5, 6, 7, 8};
  auto v3 = v1 + v2;
  v1 += v2;
  EXPECT_EQ(v3.x, 6);
  EXPECT_EQ(v3.y, 8);
  EXPECT_EQ(v3.z, 10);
  EXPECT_EQ(v3.w, 12);
  EXPECT_EQ(v1.x, 6);
  EXPECT_EQ(v1.y, 8);
  EXPECT_EQ(v1.z, 10);
  EXPECT_EQ(v1.w, 12);
}

TEST(Vec4, CustomVecSub) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{5, 6, 7, 8};
  auto v3 = v1 - v2;
  v1 -= v2;
  EXPECT_EQ(v3.x, -4);
  EXPECT_EQ(v3.y, -4);
  EXPECT_EQ(v3.z, -4);
  EXPECT_EQ(v3.w, -4);
  EXPECT_EQ(v1.x, -4);
  EXPECT_EQ(v1.y, -4);
  EXPECT_EQ(v1.z, -4);
  EXPECT_EQ(v1.w, -4);
}

TEST(Vec4, CustomVecMul) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{5, 6, 7, 8};
  auto v3 = v1 * v2;
  v1 *= v2;
  EXPECT_EQ(v3.x, 5);
  EXPECT_EQ(v3.y, 12);
  EXPECT_EQ(v3.z, 21);
  EXPECT_EQ(v3.w, 32);
  EXPECT_EQ(v1.x, 5);
  EXPECT_EQ(v1.y, 12);
  EXPECT_EQ(v1.z, 21);
  EXPECT_EQ(v1.w, 32);
}

TEST(Vec4, CustomVecDiv) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{5, 6, 7, 8};
  auto v3 = v1 / v2;
  v1 /= v2;
  EXPECT_EQ(v3.x, 1 / 5);
  EXPECT_EQ(v3.y, 2 / 6);
  EXPECT_EQ(v3.z, 3 / 7);
  EXPECT_EQ(v3.w, 4 / 8);
  EXPECT_EQ(v1.x, 1 / 5);
  EXPECT_EQ(v1.y, 2 / 6);
  EXPECT_EQ(v1.z, 3 / 7);
  EXPECT_EQ(v1.w, 4 / 8);
}

TEST(Vec4, CustomVecMod) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  V4Tst v2{5, 6, 7, 8};
  auto v3 = v1 % v2;
  v1 %= v2;
  EXPECT_EQ(v3.x, 1 % 5);
  EXPECT_EQ(v3.y, 2 % 6);
  EXPECT_EQ(v3.z, 3 % 7);
  EXPECT_EQ(v3.w, 4 % 8);
  EXPECT_EQ(v1.x, 1 % 5);
  EXPECT_EQ(v1.y, 2 % 6);
  EXPECT_EQ(v1.z, 3 % 7);
  EXPECT_EQ(v1.w, 4 % 8);
}

TEST(Vec4, EQOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v3 == v1);
}

TEST(Vec4, NEQOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
  EXPECT_TRUE(v3 != v1);
}

TEST(Vec4, GTOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v1 > v3);
  EXPECT_TRUE(v3 > v1);
}

TEST(Vec4, GTEOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_TRUE(v1 >= v2);
  EXPECT_FALSE(v1 >= v3);
  EXPECT_TRUE(v3 >= v1);
}

TEST(Vec4, LTOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_FALSE(v1 < v2);
  EXPECT_TRUE(v1 < v3);
  EXPECT_FALSE(v3 < v1);
}

TEST(Vec4, LTEOperator) {
  ams::Vec4<int> v1{1, 2, 3, 4};
  ams::Vec4<int> v2{1, 2, 3, 4};
  ams::Vec4<int> v3{4, 5, 6, 7};
  EXPECT_TRUE(v1 <= v2);
  EXPECT_TRUE(v1 <= v3);
  EXPECT_FALSE(v3 <= v1);
}

TEST(Vec4, SupportFunction_RemapScalar) {
  ams::Vec4<float> v{1.0f, 2.0f, 3.0f, 4.0f};
  auto v2 = ams::remap(v, 0.0f, 1.0f, 0.0f, 10.0f);
  EXPECT_FLOAT_EQ(v2.x, 10.0f);
  EXPECT_FLOAT_EQ(v2.y, 20.0f);
  EXPECT_FLOAT_EQ(v2.z, 30.0f);
  EXPECT_FLOAT_EQ(v2.w, 40.0f);
}

TEST(Vec4, SupportFunction_RemapVec) {
  ams::Vec4<float> v{1.0f, 2.0f, 3.0f, 4.0f};
  auto v2 = ams::remap<float>(v, ams::Vec4{0.0f, 0.0f, 0.0f, 0.0f}, ams::Vec4{1.0f, 1.0f, 1.0f, 1.0f}, ams::Vec4{0.0f, 0.0f, 0.0f, 0.0f}, ams::Vec4{10.0f, 10.0f, 10.0f, 10.0f});
  EXPECT_FLOAT_EQ(v2.x, 10.0f);
  EXPECT_FLOAT_EQ(v2.y, 20.0f);
  EXPECT_FLOAT_EQ(v2.z, 30.0f);
  EXPECT_FLOAT_EQ(v2.w, 40.0f);
}

TEST(Vec4, SupportFunction_ClampScalar) {
  ams::Vec4<float> v{-1.0f, 0.5f, 2.0f, 3.0f};
  auto v2 = ams::clamp(v, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(v2.x, 0.0f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 1.0f);
  EXPECT_FLOAT_EQ(v2.w, 1.0f);
}

TEST(Vec4, SupportFunction_ClampVec) {
  ams::Vec4<float> v{-1.0f, 0.5f, 2.0f, 3.0f};
  auto v2 = ams::clamp<float>(v, ams::Vec4{0.0f, 0.0f, 0.0f, 0.0f}, ams::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
  EXPECT_FLOAT_EQ(v2.x, 0.0f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 1.0f);
  EXPECT_FLOAT_EQ(v2.w, 1.0f);
}

TEST(Vec4, SupportFunction_WrapScalar) {
  ams::Vec4<float> v{0.5f, 1.5f, 2.5f, 3.5f};
  auto v2 = ams::wrap(v, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 0.5f);
  EXPECT_FLOAT_EQ(v2.w, 0.5f);
}

TEST(Vec4, SupportFunction_WrapVec) {
  ams::Vec4<float> v{0.5f, 1.5f, 2.5f, 3.5f};
  auto v2 = ams::wrap<float>(v, ams::Vec4{0.0f, 0.0f, 0.0f, 0.0f}, ams::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 0.5f);
  EXPECT_FLOAT_EQ(v2.w, 0.5f);
}

TEST(Vec4, SupportFunction_Distance) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  EXPECT_FLOAT_EQ(ams::distance<float>(v1, v2), 2.0f);
}

TEST(Vec4, SupportFunction_DistanceAmbiguousReturn) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::distance(v1, v2);
  EXPECT_DOUBLE_EQ(d, 2.0);
}

TEST(Vec4, SupportFunction_DistanceT2) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  V4Tst v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::distance<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 2.0f);
}

TEST(Vec4, SupportFunction_Distance2) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  EXPECT_FLOAT_EQ(ams::distance2<float>(v1, v2), 4.0f);
}

TEST(Vec4, SupportFunction_Distance2AmbiguousReturn) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::distance2(v1, v2);
  EXPECT_DOUBLE_EQ(d, 4.0);
}

TEST(Vec4, SupportFunction_Distance2T2) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  V4Tst v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::distance2<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 4.0f);
}

TEST(Vec4, SupportFunction_Length) {
  ams::Vec4<float> v{1.0f, 1.0f, 1.0f, 1.0f};
  auto l = ams::length<float>(v);
  EXPECT_FLOAT_EQ(l, 2.0f);
}

TEST(Vec4, SupportFunction_LengthAmbiguousReturn) {
  ams::Vec4<float> v{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::length(v);
  EXPECT_DOUBLE_EQ(d, 2.0);
}

TEST(Vec4, SupportFunction_Length2) {
  ams::Vec4<float> v{1.0f, 1.0f, 1.0f, 1.0f};
  auto l = ams::length2<float>(v);
  EXPECT_FLOAT_EQ(l, 4.0f);
}

TEST(Vec4, SupportFunction_Length2AmbiguousReturn) {
  ams::Vec4<float> v{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::length2(v);
  EXPECT_DOUBLE_EQ(d, 4.0);
}

TEST(Vec4, SupportFunction_Dot) {
  ams::Vec4<float> v1{1.0f, 1.0f, 1.0f, 1.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  EXPECT_FLOAT_EQ(ams::dot<float>(v1, v2), 4.0f);
}

TEST(Vec4, SupportFunction_DotAmbiguousReturn) {
  ams::Vec4<float> v1{1.0f, 1.0f, 1.0f, 1.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::dot(v1, v2);
  EXPECT_DOUBLE_EQ(d, 4.0);
}

TEST(Vec4, SupportFunction_DotT2) {
  ams::Vec4<float> v1{1.0f, 1.0f, 1.0f, 1.0f};
  V4Tst v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto d = ams::dot<float>(v1, v2);
  EXPECT_FLOAT_EQ(d, 4.0f);
}

TEST(Vec4, SupportFunction_Cross) {
  ams::Vec4<float> v1{1.0f, 1.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{0.0f, 0.0f, 1.0f, 1.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 1.0f);
  EXPECT_FLOAT_EQ(v3.y, -1.0f);
  EXPECT_FLOAT_EQ(v3.z, 0.0f);
  EXPECT_FLOAT_EQ(v3.w, 0.0f);
}

TEST(Vec4, SupportFunction_CrossT2) {
  ams::Vec4<float> v1{1.0f, 1.0f, 0.0f, 0.0f};
  V4Tst v2{0.0f, 0.0f, 1.0f, 1.0f};
  auto v3 = ams::cross(v1, v2);
  EXPECT_FLOAT_EQ(v3.x, 1.0f);
  EXPECT_FLOAT_EQ(v3.y, -1.0f);
  EXPECT_FLOAT_EQ(v3.z, 0.0f);
  EXPECT_FLOAT_EQ(v3.w, 0.0f);
}

TEST(Vec4, SupportFunction_Normalize) {
  ams::Vec4<float> v{2.0f, 2.0f, 2.0f, 2.0f};
  auto v2 = ams::normalize(v);
  EXPECT_FLOAT_EQ(v2.x, 0.5f);
  EXPECT_FLOAT_EQ(v2.y, 0.5f);
  EXPECT_FLOAT_EQ(v2.z, 0.5f);
  EXPECT_FLOAT_EQ(v2.w, 0.5f);
}

TEST(Vec4, SupportFunction_Lerp) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
  EXPECT_FLOAT_EQ(v3.z, 0.5f);
  EXPECT_FLOAT_EQ(v3.w, 0.5f);
}

TEST(Vec4, SupportFunction_LerpT2) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  V4Tst v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto v3 = ams::lerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.5f);
  EXPECT_FLOAT_EQ(v3.y, 0.5f);
  EXPECT_FLOAT_EQ(v3.z, 0.5f);
  EXPECT_FLOAT_EQ(v3.w, 0.5f);
}

TEST(Vec4, SupportFunction_Slerp) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  ams::Vec4<float> v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto v3 = ams::slerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.y, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.z, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.w, 0.7071067811865475f);
}

TEST(Vec4, SupportFunction_SlerpT2) {
  ams::Vec4<float> v1{0.0f, 0.0f, 0.0f, 0.0f};
  V4Tst v2{1.0f, 1.0f, 1.0f, 1.0f};
  auto v3 = ams::slerp(v1, v2, 0.5f);
  EXPECT_FLOAT_EQ(v3.x, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.y, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.z, 0.7071067811865475f);
  EXPECT_FLOAT_EQ(v3.w, 0.7071067811865475f);
}

#pragma endregion Vec4

#pragma region StrangeTypes

// TEST(Vec234, BadTVec) {
//   struct BadTVec {
//     void* x;
//     void* y;
//     void* z;
//     void* w;
//   } badTVec{};
//   MATH_ERREXCEPT(ams::length<double>(badTVec));
// }

TEST(Vec234, BoolVec) {
  ams::Vec2<bool> v2{true, false};
  ams::Vec3<bool> v3{true, false, true};
  ams::Vec4<bool> v4{true, false, true, false};
}

TEST(Vec234, CharVecAdd) {
  ams::Vec2<char> v2{'a', 'b'};
  ams::Vec3<char> v3{'a', 'b', 'c'};
  ams::Vec4<char> v4{'a', 'b', 'c', 'd'};
  auto v2_2 = v2 + v2;
  auto v3_2 = v3 + v3;
  auto v4_2 = v4 + v4;
  EXPECT_EQ(v2_2.x, char('a' + 'a'));
  EXPECT_EQ(v2_2.y, char('b' + 'b'));
  EXPECT_EQ(v3_2.x, char('a' + 'a'));
  EXPECT_EQ(v3_2.y, char('b' + 'b'));
  EXPECT_EQ(v3_2.z, char('c' + 'c'));
  EXPECT_EQ(v4_2.x, char('a' + 'a'));
  EXPECT_EQ(v4_2.y, char('b' + 'b'));
  EXPECT_EQ(v4_2.z, char('c' + 'c'));
  EXPECT_EQ(v4_2.w, char('d' + 'd'));
}

TEST(Vec234, CharVecSub) {
  ams::Vec2<char> v2{'a', 'b'};
  ams::Vec3<char> v3{'a', 'b', 'c'};
  ams::Vec4<char> v4{'a', 'b', 'c', 'd'};
  auto v2_2 = v2 - v2;
  auto v3_2 = v3 - v3;
  auto v4_2 = v4 - v4;
  EXPECT_EQ(v2_2.x, char('a' - 'a'));
  EXPECT_EQ(v2_2.y, char('b' - 'b'));
  EXPECT_EQ(v3_2.x, char('a' - 'a'));
  EXPECT_EQ(v3_2.y, char('b' - 'b'));
  EXPECT_EQ(v3_2.z, char('c' - 'c'));
  EXPECT_EQ(v4_2.x, char('a' - 'a'));
  EXPECT_EQ(v4_2.y, char('b' - 'b'));
  EXPECT_EQ(v4_2.z, char('c' - 'c'));
  EXPECT_EQ(v4_2.w, char('d' - 'd'));
}

TEST(Vec234, CharVecMul) {
  ams::Vec2<char> v2{'a', 'b'};
  ams::Vec3<char> v3{'a', 'b', 'c'};
  ams::Vec4<char> v4{'a', 'b', 'c', 'd'};
  auto v2_2 = v2 * v2;
  auto v3_2 = v3 * v3;
  auto v4_2 = v4 * v4;
  EXPECT_EQ(v2_2.x, char('a' * 'a'));
  EXPECT_EQ(v2_2.y, char('b' * 'b'));
  EXPECT_EQ(v3_2.x, char('a' * 'a'));
  EXPECT_EQ(v3_2.y, char('b' * 'b'));
  EXPECT_EQ(v3_2.z, char('c' * 'c'));
  EXPECT_EQ(v4_2.x, char('a' * 'a'));
  EXPECT_EQ(v4_2.y, char('b' * 'b'));
  EXPECT_EQ(v4_2.z, char('c' * 'c'));
  EXPECT_EQ(v4_2.w, char('d' * 'd'));
}

TEST(Vec234, CharVecDiv) {
  ams::Vec2<char> v2{'a', 'b'};
  ams::Vec3<char> v3{'a', 'b', 'c'};
  ams::Vec4<char> v4{'a', 'b', 'c', 'd'};
  auto v2_2 = v2 / v2;
  auto v3_2 = v3 / v3;
  auto v4_2 = v4 / v4;
  EXPECT_EQ(v2_2.x, char('a' / 'a'));
  EXPECT_EQ(v2_2.y, char('b' / 'b'));
  EXPECT_EQ(v3_2.x, char('a' / 'a'));
  EXPECT_EQ(v3_2.y, char('b' / 'b'));
  EXPECT_EQ(v3_2.z, char('c' / 'c'));
  EXPECT_EQ(v4_2.x, char('a' / 'a'));
  EXPECT_EQ(v4_2.y, char('b' / 'b'));
  EXPECT_EQ(v4_2.z, char('c' / 'c'));
  EXPECT_EQ(v4_2.w, char('d' / 'd'));
}

#pragma endregion StrangeTypes

#pragma region Constexpr Tests

consteval auto constexprTestAdd() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  auto v2_2 = v2 + v2;
  auto v3_2 = v3 + v3;
  auto v4_2 = v4 + v4;
  return;
}

consteval auto constexprTestSub() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  auto v2_2 = v2 - v2;
  auto v3_2 = v3 - v3;
  auto v4_2 = v4 - v4;
  return;
}

consteval auto constexprTestMul() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  auto v2_2 = v2 * v2;
  auto v3_2 = v3 * v3;
  auto v4_2 = v4 * v4;
  return;
}

consteval auto constexprTestDiv() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  auto v2_2 = v2 / v2;
  auto v3_2 = v3 / v3;
  auto v4_2 = v4 / v4;
  return;
}

consteval auto constexprTestMod() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  auto v2_2 = v2 % v2;
  auto v3_2 = v3 % v3;
  auto v4_2 = v4 % v4;
  return;
}

consteval auto constexprTestDot() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  return ams::dot(v2, v2) + ams::dot(v3, v3) + ams::dot(v4, v4);
}

// TODO:
// consteval auto constexprTestCross() {
//   ams::Vec3<int> v3{1, 2, 3};
//   ams::Vec4<int> v4{1, 2, 3, 4};
//   auto v3_2 = ams::cross(v3, v3);
//   auto v4_2 = ams::cross(v4, v4);
//   return;
// }

consteval auto constexprTestLength() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  return ams::length(v2) + ams::length(v3) + ams::length(v4);
}

// TODO:
// consteval auto constexprTestNormalize() {
//   ams::Vec2<int> v2{1, 2};
//   ams::Vec3<int> v3{1, 2, 3};
//   ams::Vec4<int> v4{1, 2, 3, 4};
//   auto v2_2 = ams::normalize(v2);
//   auto v3_2 = ams::normalize(v3);
//   auto v4_2 = ams::normalize(v4);
//   return;
// }

consteval auto constexprTestSwizzle() {
  ams::Vec2<int> v2{1, 2};
  ams::Vec3<int> v3{1, 2, 3};
  ams::Vec4<int> v4{1, 2, 3, 4};
  v2.xx();
  v2.xy();
  v2.yx();
  v2.yy();
  v3.xxx();
  v3.xxy();
  v3.xyx();
  v3.xyy();
  v3.yxx();
  v3.yxy();
  v3.yyx();
  v3.yyy();
  v3.zxx();
  v3.zxy();
  v3.zyx();
  v3.zyy();
  v4.xxx();
  v4.xxy();
  v4.xyx();
  v4.xyy();
  v4.yxx();
  v4.yxy();
  v4.yyx();
  v4.yyy();
  v4.zxx();
  v4.zxy();
  v4.zyx();
  v4.zyy();
  v4.wxx();
  v4.wxy();
  v4.wyx();
  v4.wyy();
  v4.xzx();
  v4.xzy();
  v4.yzx();
  v4.yzy();
  v4.zzx();
  v4.zzy();
  v4.wzx();
  v4.wzy();
  v4.wzz();
  v4.wwx();
  v4.wwy();
  v4.www();
  v4.xxx();
  v4.xxy();
  v4.xxz();
  v4.xyy();
  v4.xyz();
  v4.xzz();
  v4.yxx();
  v4.yxy();
  v4.yxz();
  v4.yyy();
  v4.yyz();
  v4.yzz();
  v4.zxx();
  v4.zxy();
  v4.zxz();
  v4.zyy();
  v4.zyz();
  v4.zzz();
  v4.wxx();
  v4.wxy();
  v4.wxz();
  v4.wyy();
  v4.wyz();
  v4.wzz();
  v4.wwx();
  v4.wwy();
  v4.wwz();
  v4.xxxx();
  v4.xxxy();
  v4.xxyx();
  v4.xxyy();
  v4.xyxx();
  v4.xyxy();
  v4.xyyx();
  v4.xyyy();
  v4.yxxx();
  v4.yxxy();
  v4.yxyx();
  v4.yxyy();
  v4.yyxx();
  v4.yyxy();
  v4.yyyx();
  v4.yyyy();
  v4.zxxx();
  v4.zxxy();
  v4.zxyx();
  v4.zxyy();
  v4.zyxx();
  v4.zyxy();
  v4.zyyx();
  v4.zyyy();
  v4.wxxx();
  v4.wxxy();
  v4.wxyx();
  v4.wxyy();
  v4.wyxx();
  v4.wyxy();
  v4.wyyx();
  v4.wyyy();
  v4.xxxx();
  v4.xxxy();
  v4.xxxz();
  v4.xxyx();
  v4.xxyy();
  v4.xxyz();
  v4.xxzx();
  v4.xxzy();
  v4.xxzz();
  v4.xyxx();
  v4.xyxy();
  v4.xyxz();
  v4.xyyx();
  v4.xyyy();
  v4.xyyz();
  v4.xyzx();
  v4.xyzy();
  v4.xyzz();
  v4.xzxx();
  v4.xzxy();
  v4.xzxz();
  v4.xzyx();
  v4.xzyy();
  v4.xzyz();
  v4.xzzx();
  v4.xzzy();
  v4.xzzz();
  v4.yxxx();
  v4.yxxy();
  v4.yxxz();
  v4.yxyx();
  v4.yxyy();
  v4.yxyz();
  v4.yxzx();
  v4.yxzy();
  v4.yxzz();
  v4.yyxx();
  v4.yyxy();
  v4.yyxz();
  v4.yyyx();
  v4.yyyy();
  v4.yyyz();
  v4.yyzx();
  v4.yyzy();
  v4.yyzz();
  v4.yzxx();
  v4.yzxy();
  v4.yzxz();
  v4.yzyx();
  v4.yzyy();
  v4.yzyz();
  v4.yzzx();
  v4.yzzy();
  v4.yzzz();
  v4.zxxx();
  v4.zxxy();
  v4.zxxz();
  v4.zxyx();
  v4.zxyy();
  v4.zxyz();
  v4.zxzx();
  v4.zxzy();
  v4.zxzz();
  v4.zyxx();
  v4.zyxy();
  v4.zyxz();
  v4.zyyx();
  v4.zyyy();
  v4.zyyz();
  v4.zyzx();
  v4.zyzy();
  v4.zyzz();
  v4.zzxx();
  v4.zzxy();
  v4.zzxz();
  v4.zzyx();
  v4.zzyy();
  v4.zzyz();
  v4.zzzx();
  v4.zzzy();
  v4.zzzz();
  v4.wxxx();
  v4.wxxy();
  v4.wxxz();
  v4.wxyx();
  v4.wxyy();
  v4.wxyz();
  v4.wxzx();
  v4.wxzy();
  v4.wxzz();
  v4.wyxx();
  v4.wyxy();
  v4.wyxz();
  v4.wyyx();
  v4.wyyy();
  v4.wyyz();
  v4.wyzx();
  v4.wyzy();
  v4.wyzz();
  v4.wzxx();
  v4.wzxy();
  v4.wzxz();
  v4.wzyx();
  v4.wzyy();
  v4.wzyz();
  v4.wzzx();
  v4.wzzy();
  v4.wzzz();
  v4.wwxx();
  v4.wwxy();
  v4.wwxz();
  v4.wwyx();
  v4.wwyy();
  v4.wwyz();
  v4.wwzx();
  v4.wwzy();
  v4.wwzz();
  v4.wwwx();
  v4.wwwy();
  v4.wwwz();
  v4.wwww();
}

#pragma endregion
