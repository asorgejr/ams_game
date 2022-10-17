//
// Created by asorgejr on 10/3/2022.
//
#include "gtest/gtest.h"

#ifndef AMS_MODULES

#include <any>
#include <chrono>
#include <utility>
#include "ams/spatial/Vec.hpp"

#else
#include <any>
import <chrono>;
import ams.Vec;
#endif
#define OLC_PGE_APPLICATION

#include <PixelGameEngine/olcPixelGameEngine.h>

using namespace std::chrono;

TEST(Vec2, Add) {
  ams::Vec2<float> v{1, 2};
  olc::vf2d v2{1, 2};
  auto v3 = v + v2;
  v += v2;
  EXPECT_EQ(v3.x, 2);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v.x, 2);
  EXPECT_EQ(v.y, 4);
}

TEST(Vec2, Subtract) {
  ams::Vec2<float> v{1, 2};
  olc::vf2d v2{1, 2};
  auto v3 = v - v2;
  v -= v2;
  EXPECT_EQ(v3.x, 0);
  EXPECT_EQ(v3.y, 0);
  EXPECT_EQ(v.x, 0);
  EXPECT_EQ(v.y, 0);
}

TEST(Vec2, Multiply) {
  ams::Vec2<float> v{1, 2};
  olc::vf2d v2{1, 2};
  auto v3 = v * v2;
  v *= v2;
  EXPECT_EQ(v3.x, 1);
  EXPECT_EQ(v3.y, 4);
  EXPECT_EQ(v.x, 1);
  EXPECT_EQ(v.y, 4);
}

TEST(Vec2, Divide) {
  ams::Vec2<float> v{1, 2};
  olc::vf2d v2{1, 2};
  auto v3 = v / v2;
  v /= v2;
  EXPECT_EQ(v3.x, 1);
  EXPECT_EQ(v3.y, 1);
  EXPECT_EQ(v.x, 1);
  EXPECT_EQ(v.y, 1);
}

TEST(Vec2, Dot) {
  ams::Vec2<float> v{1, 2};
  olc::vf2d v2{1, 2};
  auto v3 = ams::dot(v, v2);
  EXPECT_EQ(v3, 5);
}

TEST(VecMath, Remap) {
  olc::vd2d v1(1, 2);
  auto v2 = ams::remap(v1, 0.0, 1.0, 0.0, 2.0);
  EXPECT_EQ(v2.x, 2);
  EXPECT_EQ(v2.y, 4);
}

TEST(VecMath, Clamp) {
  olc::vd2d v1(1, 2);
  auto v2 = ams::clamp(v1, 0.0, 1.0);
  EXPECT_EQ(v2.x, 1);
  EXPECT_EQ(v2.y, 1);
}

TEST(VecMath, MultiType) {
  olc::vd2d v1(1, 2);
  ams::Vec2<double> v2(3, 4);
  double d = ams::distance(v1, v2);
  EXPECT_EQ(d, 2.8284271247461903);
  double l = ams::length(v1);
  EXPECT_EQ(l, 2.23606797749979);
  auto vn1 = ams::normalize(v1);
  auto vn2 = ams::normalize(v2);
  EXPECT_EQ(vn1.x, 0.4472135954999579);
  EXPECT_EQ(vn1.y, 0.8944271909999159);
  EXPECT_EQ(vn2.x, 0.6);
  EXPECT_EQ(vn2.y, 0.8);
  auto v3_1 = ams::Vec3<double>(vn1.x, vn1.y, 0);
  auto v3_2 = ams::Vec3<double>(vn2.x, vn2.y, 0);
  auto vc = ams::cross(v3_1, v3_2);
  EXPECT_EQ(vc.x, 0);
  EXPECT_EQ(vc.y, 0);
  EXPECT_EQ(vc.z, -0.1788854381999831);
}


struct TestApp : public olc::PixelGameEngine {
private:
  std::function<void()> start{};
  std::function<bool(TestApp*)> update{};
  std::function<void(int, int, olc::Pixel&, TestApp*)> draw{};
  olc::vi2d size{};
public:
  const std::string title = "TestApp";
  long frameCount = 0;
  microseconds lastFrameTime = 0us;
  milliseconds totalTime = 0ms;
  std::any userData;

  TestApp(std::string title,
          std::function<void(int, int, olc::Pixel&, TestApp*)> draw={},
          std::function<void()> start={},
          std::function<bool(TestApp*)> update={},
          std::any userData = std::any())
    : title(std::move(title)),
      start(std::move(start)),
      update(std::move(update)),
      draw(std::move(draw)),
      userData(std::move(userData)) {}

  bool OnUserCreate() override {
    auto begin = high_resolution_clock::now();
    start();
    lastFrameTime = duration_cast<microseconds>(high_resolution_clock::now() - begin);
    totalTime += duration_cast<milliseconds>(lastFrameTime);
    frameCount++;
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    auto begin = high_resolution_clock::now();
    bool result = update(this);
    for (int x = 0; x < ScreenWidth(); x++) {
      for (int y = 0; y < ScreenHeight(); y++) {
        olc::Pixel p = olc::BLACK;
        draw(x, y, p, this);
        Draw(x, y, p);
      }
    }
    lastFrameTime = duration_cast<microseconds>(high_resolution_clock::now() - begin);
    totalTime += duration_cast<milliseconds>(lastFrameTime);
    frameCount++;
    return result;
  }
};


TEST(olc, TestVecDistance) {
  auto app = TestApp(
    "TestVecDot",
    [&](int x, int y, olc::Pixel& p, auto* app) { // draw
      auto c = olc::vi2d(app->ScreenWidth()/2, app->ScreenHeight()/2);
      double d = ams::distance(olc::vi2d(x, y), c);
      p = olc::PixelF(d, d, d);
    }, {},
    [](TestApp* app) { // update
      return app->totalTime < 10000ms;
    });
  app.Construct(1024, 1024, 1, 1);
  app.Start();
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
