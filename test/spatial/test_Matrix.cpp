//
// Created by asorgejr on 10/3/2022.
//

#include <gtest/gtest.h>
#ifndef AMS_MODULES
#include <ams/spatial/Matrix.hpp>
#include <ams/spatial/Quaternion.hpp>
#else
import ams.spatial.Matrix;
import ams.spatial.Quaternion;
#endif

namespace {


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

TEST(Matrix2, Multiply) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::Matrix2 m2(5, 6, 7, 8);
  auto m3 = m * m2;
  EXPECT_EQ(m3[0][0], 19);
  EXPECT_EQ(m3[0][1], 22);
  EXPECT_EQ(m3[1][0], 43);
  EXPECT_EQ(m3[1][1], 50);
}

TEST(Matrix2, scale_single) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::scale(m, 2);
  EXPECT_EQ(m[0][0], 2);
  EXPECT_EQ(m[0][1], 4);
  EXPECT_EQ(m[1][0], 6);
  EXPECT_EQ(m[1][1], 8);
}

TEST(Matrix2, scale_vec) {
  ams::Matrix2 m(1, 2, 3, 4);
  ams::scale(m, {2, 3});
  // expect row major
  EXPECT_EQ(m[0][0], 2);
  EXPECT_EQ(m[0][1], 6);
  EXPECT_EQ(m[1][0], 6);
  EXPECT_EQ(m[1][1], 12);
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

TEST(Matrix3, FromQuaternion) {
  using namespace ams;
  auto q = ams::Quaternion();
  auto m = ams::Matrix3(q);
}

TEST(Matrix3, FromEulerAngles) {
  using namespace ams;
  auto m = ams::fromEulerAngles(radians(0.0), radians(0.0), radians(0.0));
  EXPECT_NEAR(m[0][0],  1.000000, 1e-6);
  EXPECT_NEAR(m[0][1],  0.000000, 1e-6);
  EXPECT_NEAR(m[0][2],  0.000000, 1e-6);
  EXPECT_NEAR(m[1][0],  0.000000, 1e-6);
  EXPECT_NEAR(m[1][1],  1.000000, 1e-6);
  EXPECT_NEAR(m[1][2],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][0],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][1],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][2],  1.000000, 1e-6);
  
  m = ams::fromEulerAngles(radians(45.0), radians(-90.0), radians(0.0));
  EXPECT_NEAR(m[0][0],  0.000000, 1e-6);
  EXPECT_NEAR(m[0][1],  0.000000, 1e-6);
  EXPECT_NEAR(m[0][2],  1.000000, 1e-6);
  EXPECT_NEAR(m[1][0], -0.707107, 1e-6);
  EXPECT_NEAR(m[1][1],  0.707107, 1e-6);
  EXPECT_NEAR(m[1][2],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][0], -0.707107, 1e-6);
  EXPECT_NEAR(m[2][1], -0.707107, 1e-6);
  EXPECT_NEAR(m[2][2],  0.000000, 1e-6);
  
  m = ams::fromEulerAngles(radians(0.0), radians(0.0), radians(90.0));
  EXPECT_NEAR(m[0][0],  0.000000, 1e-6);
  EXPECT_NEAR(m[0][1],  1.000000, 1e-6);
  EXPECT_NEAR(m[0][2],  0.000000, 1e-6);
  EXPECT_NEAR(m[1][0], -1.000000, 1e-6);
  EXPECT_NEAR(m[1][1],  0.000000, 1e-6);
  EXPECT_NEAR(m[1][2],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][0],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][1],  0.000000, 1e-6);
  EXPECT_NEAR(m[2][2],  1.000000, 1e-6);
}

TEST(Matrix3, FromToEulerAngles) {
  using namespace ams;
  Matrix3 m = ams::fromEulerAngles(0,0,0, true);
  // auto euler = ams::toEulerAngles(m, true);
  auto euler = degrees(m.eulerangles());
  EXPECT_NEAR(euler.x, 0.0, 1e-5);
  EXPECT_NEAR(euler.y, 0.0, 1e-5);
  EXPECT_NEAR(euler.z, 0.0, 1e-5);
  
  m = ams::fromEulerAngles(90.0, 90, 0.0, true);
  // euler = ams::toEulerAngles(m, true);
  euler = degrees(m.eulerangles());
  EXPECT_NEAR(euler.x, 90.0, 1e-5);
  EXPECT_NEAR(euler.y, 90.0, 1e-5);
  EXPECT_NEAR(euler.z, 0.0, 1e-5);
  
  m = ams::fromEulerAngles(-45.0, -90.0, 0.0, true);
  // euler = ams::toEulerAngles(m, true);
  euler = degrees(m.eulerangles());
  EXPECT_NEAR(euler.x, -45.0, 1e-5);
  EXPECT_NEAR(euler.y, -90.0, 1e-5);
  EXPECT_NEAR(euler.z, 0.0, 1e-5);
  
  m = ams::fromEulerAngles(0.0, 0.0, 90.0, true);
  // euler = ams::toEulerAngles(m, true);
  euler = degrees(m.eulerangles());
  EXPECT_NEAR(euler.x, 0.0, 1e-5);
  EXPECT_NEAR(euler.y, 0.0, 1e-5);
  EXPECT_NEAR(euler.z, 90.0, 1e-5);
}

TEST(Matrix3, FromEulerAnglesBackDwn) {
  using namespace ams;
  Matrix3 m = ams::maketransform(Vec3<double>::backward(), Vec3<double>::down());
  auto euler = toEulerAngles(m);
  // EXPECT_EQ(euler.x, 0);
  // EXPECT_EQ(euler.y, -3.14159);
  // EXPECT_EQ(euler.z, 3.14159);
}

TEST(Matrix3, ToQuaternion) {
  using namespace ams;
  ams::Matrix3 m = ams::fromQuaternion(Quaternion::identity());
  auto q = ams::toQuaternion(m);
  EXPECT_NEAR(q.x, 0.0, 1e-5);
  EXPECT_NEAR(q.y, 0.0, 1e-5);
  EXPECT_NEAR(q.z, 0.0, 1e-5);
  EXPECT_NEAR(q.w, 1.0, 1e-5);
  ams::Matrix3 m2 = ams::fromQuaternion(Quaternion::fromAxisAngle(Vec3<double>::up(), radians(90.0)));
  auto q2 = ams::toQuaternion(m2);
  EXPECT_NEAR(q2.x, 0.0, 1e-5);
  EXPECT_NEAR(q2.y, 0.7071067811865475, 1e-5);
  EXPECT_NEAR(q2.z, 0.0, 1e-5);
  EXPECT_NEAR(q2.w, 0.7071067811865475, 1e-5);
  ams::Matrix3 m3 = ams::fromQuaternion(Quaternion::fromAxisAngle(Vec3<double>::right(), radians(90.0)));
  auto q3 = ams::toQuaternion(m3);
  EXPECT_NEAR(q3.x, 0.7071067811865475, 1e-5);
  EXPECT_NEAR(q3.y, 0.0, 1e-5);
  EXPECT_NEAR(q3.z, 0.0, 1e-5);
  EXPECT_NEAR(q3.w, 0.7071067811865475, 1e-5);
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

TEST(Matrix4, MultiplyVector) {
  using namespace ams;
  ams::Matrix4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  ams::Vec4<double> v{17, 18, 19, 20};
  auto v2 = v * m;
  // EXPECT_EQ(v2[0], 250);
  // EXPECT_EQ(v2[1], 618);
  // EXPECT_EQ(v2[2], 986);
  // EXPECT_EQ(v2[3], 1354);
}

}