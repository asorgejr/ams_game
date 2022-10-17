//
// Created by asorgejr on 10/3/2022.
//

#include <gtest/gtest.h>
#ifndef AMS_MODULES
#include <ams/spatial/Quaternion.hpp>
#include <ams/spatial/Matrix.hpp>
#else
import ams.spatial.Quaternion;
import ams.spatial.Matrix;
#endif

namespace {

TEST(Quaternion, Quaternion) {
  ams::Quaternion q;
  EXPECT_EQ(q.x, 0);
  EXPECT_EQ(q.y, 0);
  EXPECT_EQ(q.z, 0);
  EXPECT_EQ(q.w, 0);
}

TEST(Quaternion, Copy) {
  ams::Quaternion q(1, 2, 3, 4);
  ams::Quaternion q2(q);
  EXPECT_EQ(q2.x, 1);
  EXPECT_EQ(q2.y, 2);
  EXPECT_EQ(q2.z, 3);
  EXPECT_EQ(q2.w, 4);
}

TEST(Quaternion, Multiply) {
  ams::Quaternion q(1, 2, 3, 4);
  ams::Quaternion q2(5, 6, 7, 8);
  auto q3 = q * q2;
  EXPECT_EQ(q3.x, 24);
  EXPECT_EQ(q3.y, 48);
  EXPECT_EQ(q3.z, 48);
  EXPECT_EQ(q3.w, -6);
}

TEST(Quaternion, Identity) {
  ams::Quaternion q = ams::Quaternion::identity();
  EXPECT_EQ(q.x, 0);
  EXPECT_EQ(q.y, 0);
  EXPECT_EQ(q.z, 0);
  EXPECT_EQ(q.w, 1);
}

}