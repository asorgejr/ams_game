//
// Created by asorgejr on 10/3/2022.
//

#include <gtest/gtest.h>
#ifndef AMS_MODULES
#include "ams/Matrix.hpp"
#else
import ams.Matrix;
#endif

TEST(Matrix2, Matrix2) {
  ams::Matrix2 m;
  EXPECT_EQ(m[0][0], 0);
  EXPECT_EQ(m[0][1], 0);
  EXPECT_EQ(m[1][0], 0);
  EXPECT_EQ(m[1][1], 0);
}

TEST(Matrix2, Copy) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::Matrix2 m2(m);
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[1][0], 3);
  EXPECT_EQ(m2[1][1], 4);
}

TEST(Matrix2, Move) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::Matrix2 m2(std::move(m));
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[1][0], 3);
  EXPECT_EQ(m2[1][1], 4);
}

TEST(Matrix2, Multiply) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::Matrix2 m2(5, 6, 7, 8);
  auto m3 = m * m2;
  EXPECT_EQ(m3[0][0], 19);
  EXPECT_EQ(m3[0][1], 22);
  EXPECT_EQ(m3[1][0], 43);
  EXPECT_EQ(m3[1][1], 50);
}

TEST(Matrix3, Matrix3) {
  ams::Matrix3 m;
  EXPECT_EQ(m[0][0], 0);
  EXPECT_EQ(m[0][1], 0);
  EXPECT_EQ(m[0][2], 0);
  EXPECT_EQ(m[1][0], 0);
  EXPECT_EQ(m[1][1], 0);
  EXPECT_EQ(m[1][2], 0);
  EXPECT_EQ(m[2][0], 0);
  EXPECT_EQ(m[2][1], 0);
  EXPECT_EQ(m[2][2], 0);
}

TEST(Matrix3, Copy) {
  ams::Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
  ams::Matrix3 m2(m);
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[0][2], 3);
  EXPECT_EQ(m2[1][0], 4);
  EXPECT_EQ(m2[1][1], 5);
  EXPECT_EQ(m2[1][2], 6);
  EXPECT_EQ(m2[2][0], 7);
  EXPECT_EQ(m2[2][1], 8);
  EXPECT_EQ(m2[2][2], 9);
}

TEST(Matrix3, Move) {
  ams::Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
  ams::Matrix3 m2(std::move(m));
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[0][2], 3);
  EXPECT_EQ(m2[1][0], 4);
  EXPECT_EQ(m2[1][1], 5);
  EXPECT_EQ(m2[1][2], 6);
  EXPECT_EQ(m2[2][0], 7);
  EXPECT_EQ(m2[2][1], 8);
  EXPECT_EQ(m2[2][2], 9);
}

TEST(Matrix3, Multiply) {
  ams::Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
  ams::Matrix3 m2(10, 11, 12, 13, 14, 15, 16, 17, 18);
  auto m3 = m * m2;
  EXPECT_EQ(m3[0][0], 84);
  EXPECT_EQ(m3[0][1], 90);
  EXPECT_EQ(m3[0][2], 96);
  EXPECT_EQ(m3[1][0], 201);
  EXPECT_EQ(m3[1][1], 216);
  EXPECT_EQ(m3[1][2], 231);
  EXPECT_EQ(m3[2][0], 318);
  EXPECT_EQ(m3[2][1], 342);
  EXPECT_EQ(m3[2][2], 366);
}

TEST(Matrix4, Matrix4) {
  ams::Matrix4 m;
  EXPECT_EQ(m[0][0], 0);
  EXPECT_EQ(m[0][1], 0);
  EXPECT_EQ(m[0][2], 0);
  EXPECT_EQ(m[0][3], 0);
  EXPECT_EQ(m[1][0], 0);
  EXPECT_EQ(m[1][1], 0);
  EXPECT_EQ(m[1][2], 0);
  EXPECT_EQ(m[1][3], 0);
  EXPECT_EQ(m[2][0], 0);
  EXPECT_EQ(m[2][1], 0);
  EXPECT_EQ(m[2][2], 0);
  EXPECT_EQ(m[2][3], 0);
  EXPECT_EQ(m[3][0], 0);
  EXPECT_EQ(m[3][1], 0);
  EXPECT_EQ(m[3][2], 0);
  EXPECT_EQ(m[3][3], 0);
}

TEST(Matrix4, Copy) {
  ams::Matrix4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  ams::Matrix4 m2(m);
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[0][2], 3);
  EXPECT_EQ(m2[0][3], 4);
  EXPECT_EQ(m2[1][0], 5);
  EXPECT_EQ(m2[1][1], 6);
  EXPECT_EQ(m2[1][2], 7);
  EXPECT_EQ(m2[1][3], 8);
  EXPECT_EQ(m2[2][0], 9);
  EXPECT_EQ(m2[2][1], 10);
  EXPECT_EQ(m2[2][2], 11);
  EXPECT_EQ(m2[2][3], 12);
  EXPECT_EQ(m2[3][0], 13);
  EXPECT_EQ(m2[3][1], 14);
  EXPECT_EQ(m2[3][2], 15);
  EXPECT_EQ(m2[3][3], 16);
}

TEST(Matrix4, Move) {
  ams::Matrix4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  ams::Matrix4 m2(std::move(m));
  EXPECT_EQ(m2[0][0], 1);
  EXPECT_EQ(m2[0][1], 2);
  EXPECT_EQ(m2[0][2], 3);
  EXPECT_EQ(m2[0][3], 4);
  EXPECT_EQ(m2[1][0], 5);
  EXPECT_EQ(m2[1][1], 6);
  EXPECT_EQ(m2[1][2], 7);
  EXPECT_EQ(m2[1][3], 8);
  EXPECT_EQ(m2[2][0], 9);
  EXPECT_EQ(m2[2][1], 10);
  EXPECT_EQ(m2[2][2], 11);
  EXPECT_EQ(m2[2][3], 12);
  EXPECT_EQ(m2[3][0], 13);
  EXPECT_EQ(m2[3][1], 14);
  EXPECT_EQ(m2[3][2], 15);
  EXPECT_EQ(m2[3][3], 16);
}

TEST(Matrix4, Multiply) {
  ams::Matrix4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  ams::Matrix4 m2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
  auto m3 = m * m2;
  EXPECT_EQ(m3[0][0], 250);
  EXPECT_EQ(m3[0][1], 260);
  EXPECT_EQ(m3[0][2], 270);
  EXPECT_EQ(m3[0][3], 280);
  EXPECT_EQ(m3[1][0], 618);
  EXPECT_EQ(m3[1][1], 644);
  EXPECT_EQ(m3[1][2], 670);
  EXPECT_EQ(m3[1][3], 696);
  EXPECT_EQ(m3[2][0], 986);
  EXPECT_EQ(m3[2][1], 1028);
  EXPECT_EQ(m3[2][2], 1070);
  EXPECT_EQ(m3[2][3], 1112);
  EXPECT_EQ(m3[3][0], 1354);
  EXPECT_EQ(m3[3][1], 1412);
  EXPECT_EQ(m3[3][2], 1470);
  EXPECT_EQ(m3[3][3], 1528);
}
