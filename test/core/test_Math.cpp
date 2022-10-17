//
// Created by asorgejr on 9/25/2022.
//

#include <gtest/gtest.h>
#include <chrono>

#ifndef AMS_MODULES

#include <ams/Math.hpp>
#include <cmath>

#else
import ams.Math;
import <cmath>;
#endif

// #define AMS_TEST_MATH_BENCHMARK

using namespace std::chrono;
using hrclock = high_resolution_clock;

// ams time / cmath time limit
const float cm_ts = 1.4;

// ams cexpr time / cmath time limit
const float cm_cexpr_ts = 0.7;

TEST(Math, abs) {
  EXPECT_EQ(ams::abs(1), 1);
  EXPECT_EQ(ams::abs(-1), 1);
  EXPECT_EQ(ams::abs(-4), 4);
  EXPECT_EQ(ams::abs(0), 0);
  EXPECT_EQ(ams::abs(-0), 0);
  EXPECT_EQ(ams::abs(1.0), 1.0);
  EXPECT_EQ(ams::abs(-1.0), 1.0);
  EXPECT_EQ(ams::abs(-4.5), 4.5);
  EXPECT_EQ(ams::abs(0.0), 0.0);
  EXPECT_EQ(ams::abs(-0.0), 0.0);
}

TEST(Math, abs_constexpr_eq_std) {
  constexpr auto a = ams::abs(1);
  constexpr auto b = ams::abs(-1);
  constexpr auto c = ams::abs(-4);
  constexpr auto d = ams::abs(0);
  constexpr auto e = ams::abs(-0);
  constexpr auto f = ams::abs(1.0);
  constexpr auto g = ams::abs(-1.0);
  constexpr auto h = ams::abs(-4.5);
  constexpr auto i = ams::abs(0.0);
  constexpr auto j = ams::abs(-0.0);
  EXPECT_EQ(a, std::abs(1));
  EXPECT_EQ(b, std::abs(-1));
  EXPECT_EQ(c, std::abs(-4));
  EXPECT_EQ(d, std::abs(0));
  EXPECT_EQ(e, std::abs(-0));
  EXPECT_EQ(f, std::abs(1.0));
  EXPECT_EQ(g, std::abs(-1.0));
  EXPECT_EQ(h, std::abs(-4.5));
  EXPECT_EQ(i, std::abs(0.0));
  EXPECT_EQ(j, std::abs(-0.0));
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, abs_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto n = ams::abs(1);
    n = ams::abs(-1);
    n = ams::abs(-4);
    n = ams::abs(0);
    n = ams::abs(-0);
    auto f = ams::abs(1.0);
    f = ams::abs(-1.0);
    f = ams::abs(-4.5);
    f = ams::abs(0.0);
    f = ams::abs(-0.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::abs(1);
    a = std::abs(-1);
    a = std::abs(-4);
    a = std::abs(0);
    a = std::abs(-0);
    auto f = std::abs(1.0);
    f = std::abs(-1.0);
    f = std::abs(-4.5);
    f = std::abs(0.0);
    f = std::abs(-0.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, abs_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::abs(1);
    constexpr auto b = ams::abs(-1);
    constexpr auto c = ams::abs(-4);
    constexpr auto d = ams::abs(0);
    constexpr auto e = ams::abs(-0);
    constexpr auto f = ams::abs(1.0);
    constexpr auto g = ams::abs(-1.0);
    constexpr auto h = ams::abs(-4.5);
    constexpr auto j = ams::abs(0.0);
    constexpr auto k = ams::abs(-0.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::abs(1);
    a = std::abs(-1);
    a = std::abs(-4);
    a = std::abs(0);
    a = std::abs(-0);
    a = std::abs(1.0);
    a = std::abs(-1.0);
    a = std::abs(-4.5);
    a = std::abs(0.0);
    a = std::abs(-0.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, mod) {
  EXPECT_EQ(ams::mod(1, 1), 0);
  EXPECT_EQ(ams::mod(1, 2), 1);
  EXPECT_EQ(ams::mod(2, 1), 0);
  EXPECT_EQ(ams::mod(-1, 1), 0);
  EXPECT_EQ(ams::mod(-1, 2), 1);
  EXPECT_EQ(ams::mod(1.0, 1.0), 0.0);
  EXPECT_EQ(ams::mod(1.0, 2.0), 1.0);
  EXPECT_EQ(ams::mod(2.0, 1.0), 0.0);
  EXPECT_EQ(ams::mod(-1.0, 1.0), 0.0);
  EXPECT_EQ(ams::mod(-1.0, 2.0), 1.0);
}

TEST(Math, mod_divbyzero) {
  EXPECT_THROW(ams::mod(1, 0), std::domain_error);
  EXPECT_THROW(ams::mod(1.0, 0.0), std::domain_error);
}

TEST(Math, mod_constexpr) {
  constexpr auto a = ams::mod(1, 1);
  constexpr auto b = ams::mod(1, 2);
  constexpr auto c = ams::mod(2, 1);
  constexpr auto d = ams::mod(-1, 1);
  constexpr auto e = ams::mod(-1, 2);
  constexpr auto f = ams::mod(1.0, 1.0);
  constexpr auto g = ams::mod(1.0, 2.0);
  constexpr auto h = ams::mod(2.0, 1.0);
  constexpr auto i = ams::mod(-1.0, 1.0);
  constexpr auto j = ams::mod(-1.0, 2.0);
  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 1);
  EXPECT_EQ(c, 0);
  EXPECT_EQ(d, 0);
  EXPECT_EQ(e, 1);
  EXPECT_EQ(f, 0.0);
  EXPECT_EQ(g, 1.0);
  EXPECT_EQ(h, 0.0);
  EXPECT_EQ(i, 0.0);
  EXPECT_EQ(j, 1.0);
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, mod_float_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto f = ams::mod(1.0, 1.0);
    f = ams::mod(1.0, 2.0);
    f = ams::mod(2.0, 1.0);
    f = ams::mod(-1.0, 1.0);
    f = ams::mod(-1.0, 2.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto f = std::fmod(1.0, 1.0);
    f = std::fmod(1.0, 2.0);
    f = std::fmod(2.0, 1.0);
    f = std::fmod(-1.0, 1.0);
    f = std::fmod(-1.0, 2.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, mod_int_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::mod(1, 1);
    a = ams::mod(1, 2);
    a = ams::mod(2, 1);
    a = ams::mod(-1, 1);
    a = ams::mod(-1, 2);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  auto a1 = 1;
  auto a2 = 2;
  auto a_1 = -1;
  auto b1 = 1;
  auto b2 = 2;
  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto c = a1 % b1;
    c = a1 % b2;
    c = a2 % b1;
    c = a_1 % b1;
    c = a_1 % b2;
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, mod_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::mod(1, 1);
    constexpr auto b = ams::mod(1, 2);
    constexpr auto c = ams::mod(2, 1);
    constexpr auto d = ams::mod(-1, 1);
    constexpr auto e = ams::mod(-1, 2);
    constexpr auto f = ams::mod(1.0, 1.0);
    constexpr auto g = ams::mod(1.0, 2.0);
    constexpr auto h = ams::mod(2.0, 1.0);
    constexpr auto j = ams::mod(-1.0, 1.0);
    constexpr auto k = ams::mod(-1.0, 2.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::fmod(1, 1);
    a = std::fmod(1, 2);
    a = std::fmod(2, 1);
    a = std::fmod(-1, 1);
    a = std::fmod(-1, 2);
    a = std::fmod(1.0, 1.0);
    a = std::fmod(1.0, 2.0);
    a = std::fmod(2.0, 1.0);
    a = std::fmod(-1.0, 1.0);
    a = std::fmod(-1.0, 2.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, frac) {
  EXPECT_EQ(ams::frac(1.0), 0.0);
  EXPECT_EQ(ams::frac(1.5), 0.5);
  EXPECT_EQ(ams::frac(2.0), 0.0);
  EXPECT_EQ(ams::frac(-1.0), 0.0);
  EXPECT_EQ(ams::frac(-1.5), 0.5);
  EXPECT_EQ(ams::frac(-2.0), 0.0);
}

TEST(Math, frac_constexpr_eq_runtime) {
  constexpr auto a = ams::frac(1.0);
  constexpr auto b = ams::frac(1.5);
  constexpr auto c = ams::frac(2.0);
  constexpr auto d = ams::frac(-1.0);
  constexpr auto e = ams::frac(-1.5);
  constexpr auto f = ams::frac(-2.0);
  EXPECT_EQ(a, ams::frac(1.0));
  EXPECT_EQ(b, ams::frac(1.5));
  EXPECT_EQ(c, ams::frac(2.0));
  EXPECT_EQ(d, ams::frac(-1.0));
  EXPECT_EQ(e, ams::frac(-1.5));
  EXPECT_EQ(f, ams::frac(-2.0));
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, frac_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::frac(1.0);
    a = ams::frac(1.5);
    a = ams::frac(2.0);
    a = ams::frac(-1.0);
    a = ams::frac(-1.5);
    a = ams::frac(-2.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::fmod(1.0, 1.0);
    a = std::fmod(1.5, 1.0);
    a = std::fmod(2.0, 1.0);
    a = std::fmod(-1.0, 1.0);
    a = std::fmod(-1.5, 1.0);
    a = std::fmod(-2.0, 1.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, frac_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::frac(1.0);
    constexpr auto b = ams::frac(1.5);
    constexpr auto c = ams::frac(2.0);
    constexpr auto d = ams::frac(-1.0);
    constexpr auto e = ams::frac(-1.5);
    constexpr auto f = ams::frac(-2.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::fmod(1.0, 1.0);
    a = std::fmod(1.5, 1.0);
    a = std::fmod(2.0, 1.0);
    a = std::fmod(-1.0, 1.0);
    a = std::fmod(-1.5, 1.0);
    a = std::fmod(-2.0, 1.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, sqrt) {
  EXPECT_EQ(ams::sqrt<double>(1.0), 1.0);
  EXPECT_EQ(ams::sqrt(4.0), 2.0);
  EXPECT_EQ(ams::sqrt(9.0), 3.0);
  EXPECT_EQ(ams::sqrt(16.0), 4.0);
  EXPECT_EQ(ams::sqrt(25.0), 5.0);
  EXPECT_EQ(ams::sqrt(36.0), 6.0);
  EXPECT_EQ(ams::sqrt(49.0), 7.0);
  EXPECT_EQ(ams::sqrt(64.0), 8.0);
  EXPECT_EQ(ams::sqrt(81.0), 9.0);
  EXPECT_EQ(ams::sqrt(100.0), 10.0);
}

TEST(Math, sqrt_constexpr_eq_runtime) {
  constexpr auto a = ams::sqrt(1.0);
  constexpr auto b = ams::sqrt(4.0);
  constexpr auto c = ams::sqrt(9.0);
  constexpr auto d = ams::sqrt(16.0);
  constexpr auto e = ams::sqrt(25.0);
  constexpr auto f = ams::sqrt(36.0);
  constexpr auto g = ams::sqrt(49.0);
  constexpr auto h = ams::sqrt(64.0);
  constexpr auto j = ams::sqrt(81.0);
  constexpr auto k = ams::sqrt(100.0);
  EXPECT_DOUBLE_EQ(a, ams::sqrt(1.0));
  EXPECT_DOUBLE_EQ(b, ams::sqrt(4.0));
  EXPECT_DOUBLE_EQ(c, ams::sqrt(9.0));
  EXPECT_DOUBLE_EQ(d, ams::sqrt(16.0));
  EXPECT_DOUBLE_EQ(e, ams::sqrt(25.0));
  EXPECT_DOUBLE_EQ(f, ams::sqrt(36.0));
  EXPECT_DOUBLE_EQ(g, ams::sqrt(49.0));
  EXPECT_DOUBLE_EQ(h, ams::sqrt(64.0));
  EXPECT_DOUBLE_EQ(j, ams::sqrt(81.0));
  EXPECT_DOUBLE_EQ(k, ams::sqrt(100.0));
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, sqrt_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::sqrt(1.0);
    a = ams::sqrt(4.0);
    a = ams::sqrt(9.0);
    a = ams::sqrt(16.0);
    a = ams::sqrt(25.0);
    a = ams::sqrt(36.0);
    a = ams::sqrt(49.0);
    a = ams::sqrt(64.0);
    a = ams::sqrt(81.0);
    a = ams::sqrt(100.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::sqrt(1.0);
    a = std::sqrt(4.0);
    a = std::sqrt(9.0);
    a = std::sqrt(16.0);
    a = std::sqrt(25.0);
    a = std::sqrt(36.0);
    a = std::sqrt(49.0);
    a = std::sqrt(64.0);
    a = std::sqrt(81.0);
    a = std::sqrt(100.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, sqrt_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::sqrt(1.0);
    constexpr auto b = ams::sqrt(4.0);
    constexpr auto c = ams::sqrt(9.0);
    constexpr auto d = ams::sqrt(16.0);
    constexpr auto e = ams::sqrt(25.0);
    constexpr auto f = ams::sqrt(36.0);
    constexpr auto g = ams::sqrt(49.0);
    constexpr auto h = ams::sqrt(64.0);
    constexpr auto j = ams::sqrt(81.0);
    constexpr auto k = ams::sqrt(100.0);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::sqrt(1.0);
    a = std::sqrt(4.0);
    a = std::sqrt(9.0);
    a = std::sqrt(16.0);
    a = std::sqrt(25.0);
    a = std::sqrt(36.0);
    a = std::sqrt(49.0);
    a = std::sqrt(64.0);
    a = std::sqrt(81.0);
    a = std::sqrt(100.0);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, sin) {
  EXPECT_NEAR(ams::sin(0.0), 0.0, 1e-15);
  EXPECT_NEAR(ams::sin(ams::PI / 6.0), 0.5, 1e-15);
  EXPECT_NEAR(ams::sin(ams::PI / 4.0), 0.707106781186547524, 1e-15);
  EXPECT_NEAR(ams::sin(ams::PI / 3.0), 0.866025403784438646, 1e-15);
  EXPECT_NEAR(ams::sin(ams::PI / 2.0), 1.0, 1e-15);
  EXPECT_NEAR(ams::sin(ams::PI), 0.0, 1e-15);
  EXPECT_NEAR(ams::sin(2.0 * ams::PI), 0.0, 1e-15);
}


TEST(Math, sin_constexpr_eq_runtime) {
  constexpr auto a = ams::sin(0.0);
  constexpr auto b = ams::sin(ams::PI / 6.0);
  constexpr auto c = ams::sin(ams::PI / 4.0);
  constexpr auto d = ams::sin(ams::PI / 3.0);
  constexpr auto e = ams::sin(ams::PI / 2.0);
  constexpr auto f = ams::sin(ams::PI);
  constexpr auto g = ams::sin(2.0 * ams::PI);
  EXPECT_NEAR(a, ams::sin(0.0), 1e-15);
  EXPECT_NEAR(b, ams::sin(ams::PI / 6.0), 1e-15);
  EXPECT_NEAR(c, ams::sin(ams::PI / 4.0), 1e-15);
  EXPECT_NEAR(d, ams::sin(ams::PI / 3.0), 1e-15);
  EXPECT_NEAR(e, ams::sin(ams::PI / 2.0), 1e-15);
  EXPECT_NEAR(f, ams::sin(ams::PI), 1e-15);
  EXPECT_NEAR(g, ams::sin(2.0 * ams::PI), 1e-15);
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, sin_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::sin(0.0);
    a = ams::sin(ams::PI / 2);
    a = ams::sin(ams::PI);
    a = ams::sin(3 * ams::PI / 2);
    a = ams::sin(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::sin(0.0);
    a = std::sin(ams::PI / 2);
    a = std::sin(ams::PI);
    a = std::sin(3 * ams::PI / 2);
    a = std::sin(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, sin_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::sin(0.0);
    constexpr auto b = ams::sin(ams::PI / 2);
    constexpr auto c = ams::sin(ams::PI);
    constexpr auto d = ams::sin(3 * ams::PI / 2);
    constexpr auto e = ams::sin(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::sin(0.0);
    auto b = std::sin(ams::PI / 2);
    auto c = std::sin(ams::PI);
    auto d = std::sin(3 * ams::PI / 2);
    auto e = std::sin(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, cos) {
  EXPECT_NEAR(ams::cos(0.0), 1.0, 1e-15);
  EXPECT_NEAR(ams::cos(ams::PI / 6.0), 0.866025403784438646, 1e-15);
  EXPECT_NEAR(ams::cos(ams::PI / 4.0), 0.707106781186547524, 1e-15);
  EXPECT_NEAR(ams::cos(ams::PI / 3.0), 0.5, 1e-15);
  EXPECT_NEAR(ams::cos(ams::PI / 2.0), 0.0, 1e-15);
  EXPECT_NEAR(ams::cos(ams::PI), -1.0, 1e-15);
  EXPECT_NEAR(ams::cos(2.0 * ams::PI), 1.0, 1e-15);
}

TEST(Math, cos_constexpr_eq_runtime) {
  constexpr auto a = ams::cos(0.0);
  constexpr auto b = ams::cos(ams::PI / 6.0);
  constexpr auto c = ams::cos(ams::PI / 4.0);
  constexpr auto d = ams::cos(ams::PI / 3.0);
  constexpr auto e = ams::cos(ams::PI / 2.0);
  constexpr auto f = ams::cos(ams::PI);
  constexpr auto g = ams::cos(2.0 * ams::PI);
  EXPECT_NEAR(a, ams::cos(0.0), 1e-15);
  EXPECT_NEAR(b, ams::cos(ams::PI / 6.0), 1e-15);
  EXPECT_NEAR(c, ams::cos(ams::PI / 4.0), 1e-15);
  EXPECT_NEAR(d, ams::cos(ams::PI / 3.0), 1e-15);
  EXPECT_NEAR(e, ams::cos(ams::PI / 2.0), 1e-15);
  EXPECT_NEAR(f, ams::cos(ams::PI), 1e-15);
  EXPECT_NEAR(g, ams::cos(2.0 * ams::PI), 1e-15);
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, cos_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::cos(0.0);
    a = ams::cos(ams::PI / 2);
    a = ams::cos(ams::PI);
    a = ams::cos(3 * ams::PI / 2);
    a = ams::cos(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::cos(0.0);
    a = std::cos(ams::PI / 2);
    a = std::cos(ams::PI);
    a = std::cos(3 * ams::PI / 2);
    a = std::cos(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, cos_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::cos(0.0);
    constexpr auto b = ams::cos(ams::PI / 2);
    constexpr auto c = ams::cos(ams::PI);
    constexpr auto d = ams::cos(3 * ams::PI / 2);
    constexpr auto e = ams::cos(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::cos(0.0);
    a = std::cos(ams::PI / 2);
    a = std::cos(ams::PI);
    a = std::cos(3 * ams::PI / 2);
    a = std::cos(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif

TEST(Math, tan) {
  EXPECT_NEAR(ams::tan(0.0), 0.0, 1e-15);
  EXPECT_NEAR(ams::tan(ams::PI / 6.0), 0.577350269189625764, 1e-15);
  EXPECT_NEAR(ams::tan(ams::PI / 4.0), 1.0, 1e-15);
  EXPECT_NEAR(ams::tan(ams::PI / 3.0), 1.732050807568877293, 1e-15);
  EXPECT_NEAR(ams::tan(ams::PI), 0.0, 1e-15);
  EXPECT_NEAR(ams::tan(2.0 * ams::PI), 0.0, 1e-15);
}

TEST(Math, tan_constexpr_eq_runtime) {
  constexpr auto a = ams::tan(0.0);
  constexpr auto b = ams::tan(ams::PI / 6.0);
  constexpr auto c = ams::tan(ams::PI / 4.0);
  constexpr auto d = ams::tan(ams::PI / 3.0);
  constexpr auto e = ams::tan(ams::PI / 2.0);
  constexpr auto f = ams::tan(ams::PI);
  constexpr auto g = ams::tan(2.0 * ams::PI);
  EXPECT_NEAR(a, ams::tan(0.0), 1e-15);
  EXPECT_NEAR(b, ams::tan(ams::PI / 6.0), 1e-15);
  EXPECT_NEAR(c, ams::tan(ams::PI / 4.0), 1e-15);
  EXPECT_NEAR(d, ams::tan(ams::PI / 3.0), 1e-15);
  EXPECT_NEAR(f, ams::tan(ams::PI), 1e-15);
  EXPECT_NEAR(g, ams::tan(2.0 * ams::PI), 1e-15);
}

#ifdef AMS_TEST_MATH_BENCHMARK
TEST(Math, tan_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = ams::tan(0.0);
    a = ams::tan(ams::PI / 2);
    a = ams::tan(ams::PI);
    a = ams::tan(3 * ams::PI / 2);
    a = ams::tan(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::tan(0.0);
    a = std::tan(ams::PI / 2);
    a = std::tan(ams::PI);
    a = std::tan(3 * ams::PI / 2);
    a = std::tan(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_ts * cm_time);
}

TEST(Math, tan_constexpr_time) {
  auto start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    constexpr auto a = ams::tan(0.0);
    constexpr auto b = ams::tan(ams::PI / 2);
    constexpr auto c = ams::tan(ams::PI);
    constexpr auto d = ams::tan(3 * ams::PI / 2);
    constexpr auto e = ams::tan(2 * ams::PI);
  }
  auto stop = hrclock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  auto ams_time = duration.count();

  start = hrclock::now();
  for (int i = 0; i < 1000000; i++) {
    auto a = std::tan(0.0);
    a = std::tan(ams::PI / 2);
    a = std::tan(ams::PI);
    a = std::tan(3 * ams::PI / 2);
    a = std::tan(2 * ams::PI);
  }
  stop = hrclock::now();
  duration = duration_cast<microseconds>(stop - start);
  auto cm_time = duration.count();

  EXPECT_LT(ams_time, cm_cexpr_ts * cm_time);
}
#endif


TEST(Math, remap_integral) {
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 100), 50);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 1000), 500);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 10000), 5000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 100000), 50000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 1000000), 500000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 10000000), 5000000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 100000000), 50000000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 1000000000), 500000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 10000000000), 5000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 100000000000), 50000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 1000000000000), 500000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 10000000000000), 5000000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 100000000000000), 50000000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 1000000000000000), 500000000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, 10000000000000000), 5000000000000000);
}

TEST(Math, remap_float) {
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 100.0f), 50.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 1000.0f), 500.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 10000.0f), 5000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 100000.0f), 50000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 1000000.0f), 500000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 10000000.0f), 5000000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 100000000.0f), 50000000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 1000000000.0f), 500000000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 10000000000.0f), 5000000000.0f);
  EXPECT_EQ(ams::remap(5.0f, 0.0f, 10.0f, 0.0f, 100000000000.0f), 50000000000.0f);
}

TEST(Math, remap_double) {
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 100.0), 50.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 1000.0), 500.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 10000.0), 5000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 100000.0), 50000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 1000000.0), 500000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 10000000.0), 5000000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 100000000.0), 50000000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 1000000000.0), 500000000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 10000000000.0), 5000000000.0);
  EXPECT_EQ(ams::remap(5.0, 0.0, 10.0, 0.0, 100000000000.0), 50000000000.0);
}

TEST(Math, remap_long_double) {
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 100.0L), 50.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 1000.0L), 500.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 10000.0L), 5000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 100000.0L), 50000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 1000000.0L), 500000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 10000000.0L), 5000000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 100000000.0L), 50000000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 1000000000.0L), 500000000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 10000000000.0L), 5000000000.0L);
  EXPECT_EQ(ams::remap(5.0L, 0.0L, 10.0L, 0.0L, 100000000000.0L), 50000000000.0L);
}

TEST(Math, remap_negative_output) {
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -10), -5);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -100), -50);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -1000), -500);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -10000), -5000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -100000), -50000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -1000000), -500000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -10000000), -5000000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -100000000), -50000000);
  EXPECT_EQ(ams::remap(5, 0, 10, 0, -1000000000), -500000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -10000000000), -5000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -100000000000), -50000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -1000000000000), -500000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -10000000000000), -5000000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -100000000000000), -50000000000000);
  EXPECT_EQ(ams::remap<long long>(5, 0, 10, 0, -1000000000000000), -500000000000000);
}

TEST(Math, remap_zero_out_range) {
  EXPECT_EQ(ams::remap(5, 0, 10, 0, 0), 0);
  EXPECT_EQ(ams::remap(-5, 0, -10, 0, 0), 0);
}


TEST(Math, clamp_int) {
  EXPECT_EQ(ams::clamp(5, 0, 10), 5);
  EXPECT_EQ(ams::clamp(5, 0, 4), 4);
  EXPECT_EQ(ams::clamp(5, 6, 10), 6);
  EXPECT_EQ(ams::clamp(5, 0, 5), 5);
  EXPECT_EQ(ams::clamp(5, 5, 10), 5);
  EXPECT_EQ(ams::clamp(5, 5, 5), 5);
  EXPECT_EQ(ams::clamp(5, 0, 0), 0);
  EXPECT_EQ(ams::clamp(-5, -10, -5), -5);
  EXPECT_EQ(ams::clamp(-5, -10, -6), -6);
  EXPECT_EQ(ams::clamp(-5, -4, -1), -4);
  EXPECT_EQ(ams::clamp(-5, -5, 0), -5);
}

TEST(Math, clamp_float) {
  EXPECT_EQ(ams::clamp(5.0f, 0.0f, 10.0f), 5.0f);
  EXPECT_EQ(ams::clamp(5.0f, 0.0f, 4.0f), 4.0f);
  EXPECT_EQ(ams::clamp(5.0f, 6.0f, 10.0f), 6.0f);
  EXPECT_EQ(ams::clamp(5.0f, 0.0f, 5.0f), 5.0f);
  EXPECT_EQ(ams::clamp(5.0f, 5.0f, 10.0f), 5.0f);
  EXPECT_EQ(ams::clamp(5.0f, 5.0f, 5.0f), 5.0f);
  EXPECT_EQ(ams::clamp(5.0f, 0.0f, 0.0f), 0.0f);
  EXPECT_EQ(ams::clamp(-5.0f, -10.0f, -5.0f), -5.0f);
  EXPECT_EQ(ams::clamp(-5.0f, -10.0f, -6.0f), -6.0f);
  EXPECT_EQ(ams::clamp(-5.0f, -4.0f, -1.0f), -4.0f);
  EXPECT_EQ(ams::clamp(-5.0f, -5.0f, 0.0f), -5.0f);
}

TEST(Math, clamp_double) {
  EXPECT_EQ(ams::clamp(5.0, 0.0, 10.0), 5.0);
  EXPECT_EQ(ams::clamp(5.0, 0.0, 4.0), 4.0);
  EXPECT_EQ(ams::clamp(5.0, 6.0, 10.0), 6.0);
  EXPECT_EQ(ams::clamp(5.0, 0.0, 5.0), 5.0);
  EXPECT_EQ(ams::clamp(5.0, 5.0, 10.0), 5.0);
  EXPECT_EQ(ams::clamp(5.0, 5.0, 5.0), 5.0);
  EXPECT_EQ(ams::clamp(5.0, 0.0, 0.0), 0.0);
  EXPECT_EQ(ams::clamp(-5.0, -10.0, -5.0), -5.0);
  EXPECT_EQ(ams::clamp(-5.0, -10.0, -6.0), -6.0);
  EXPECT_EQ(ams::clamp(-5.0, -4.0, -1.0), -4.0);
  EXPECT_EQ(ams::clamp(-5.0, -5.0, 0.0), -5.0);
}

TEST(Math, clamp_long_double) {
  EXPECT_EQ(ams::clamp(5.0L, 0.0L, 10.0L), 5.0L);
  EXPECT_EQ(ams::clamp(5.0L, 0.0L, 4.0L), 4.0L);
  EXPECT_EQ(ams::clamp(5.0L, 6.0L, 10.0L), 6.0L);
  EXPECT_EQ(ams::clamp(5.0L, 0.0L, 5.0L), 5.0L);
  EXPECT_EQ(ams::clamp(5.0L, 5.0L, 10.0L), 5.0L);
  EXPECT_EQ(ams::clamp(5.0L, 5.0L, 5.0L), 5.0L);
  EXPECT_EQ(ams::clamp(5.0L, 0.0L, 0.0L), 0.0L);
  EXPECT_EQ(ams::clamp(-5.0L, -10.0L, -5.0L), -5.0L);
  EXPECT_EQ(ams::clamp(-5.0L, -10.0L, -6.0L), -6.0L);
  EXPECT_EQ(ams::clamp(-5.0L, -4.0L, -1.0L), -4.0L);
  EXPECT_EQ(ams::clamp(-5.0L, -5.0L, 0.0L), -5.0L);
}

TEST(Math, lerp_int) {
  EXPECT_EQ(ams::lerp(0, 10, 0.0f), 0);
  EXPECT_EQ(ams::lerp(0, 10, 0.5f), 5);
  EXPECT_EQ(ams::lerp(0, 10, 1.0f), 10);
  EXPECT_EQ(ams::lerp(0, 10, 1.5f), 15);
  EXPECT_EQ(ams::lerp(0, 10, -0.5f), -5);
  EXPECT_EQ(ams::lerp(0, -10, 0.0f), 0);
  EXPECT_EQ(ams::lerp(0, -10, 0.5f), -5);
  EXPECT_EQ(ams::lerp(0, -10, 1.0f), -10);
  EXPECT_EQ(ams::lerp(0, -10, 1.5f), -15);
  EXPECT_EQ(ams::lerp(0, -10, -0.5f), 5);
}

TEST(Math, lerp_float) {
  EXPECT_EQ(ams::lerp(0.0f, 10.0f, 0.0f), 0.0f);
  EXPECT_EQ(ams::lerp(0.0f, 10.0f, 0.5f), 5.0f);
  EXPECT_EQ(ams::lerp(0.0f, 10.0f, 1.0f), 10.0f);
  EXPECT_EQ(ams::lerp(0.0f, 10.0f, 1.5f), 15.0f);
  EXPECT_EQ(ams::lerp(0.0f, 10.0f, -0.5f), -5.0f);
  EXPECT_EQ(ams::lerp(0.0f, -10.0f, 0.0f), 0.0f);
  EXPECT_EQ(ams::lerp(0.0f, -10.0f, 0.5f), -5.0f);
  EXPECT_EQ(ams::lerp(0.0f, -10.0f, 1.0f), -10.0f);
  EXPECT_EQ(ams::lerp(0.0f, -10.0f, 1.5f), -15.0f);
  EXPECT_EQ(ams::lerp(0.0f, -10.0f, -0.5f), 5.0f);
}


TEST(Math, wrap_int) {
  EXPECT_EQ(ams::wrap(5, 0, 10), 5);
  EXPECT_EQ(ams::wrap(0, 0, 10), 0);
  EXPECT_EQ(ams::wrap(10, 0, 10), 10);
  EXPECT_EQ(ams::wrap(11, 0, 10), 1);
  EXPECT_EQ(ams::wrap(15, 0, 10), 5);
  EXPECT_EQ(ams::wrap(30, 5, 15), 10);
  EXPECT_EQ(ams::wrap(-1, 0, 10), 9);
  EXPECT_EQ(ams::wrap(-5, 0, 10), 5);
  EXPECT_EQ(ams::wrap(-10, -15, -10), -10);
  EXPECT_EQ(ams::wrap(-15, -15, -10), -15);
  EXPECT_EQ(ams::wrap(-16, -15, -10), -11);
}

TEST(Math, wrap_decimal) {
  EXPECT_EQ(ams::wrap(5.0f, 0.0f, 10.0f), 5.0f);
  EXPECT_EQ(ams::wrap(0.0f, 0.0f, 10.0f), 0.0f);
  EXPECT_EQ(ams::wrap(10.0f, 0.0f, 10.0f), 10.0f);
  EXPECT_EQ(ams::wrap(11.0f, 0.0f, 10.0f), 1.0f);
  EXPECT_EQ(ams::wrap(15.0f, 0.0f, 10.0f), 5.0f);
  EXPECT_EQ(ams::wrap(30.5f, 5.5f, 15.0f), 11.5f);
  EXPECT_EQ(ams::wrap(-1.0f, 0.0f, 10.0f), 9.0f);
  EXPECT_EQ(ams::wrap(-5.0f, 0.0f, 10.0f), 5.0f);
  EXPECT_EQ(ams::wrap(-10.0f, -15.0f, -10.0f), -10.0f);
  EXPECT_EQ(ams::wrap(-15.0f, -15.0f, -10.0f), -15.0f);
  EXPECT_EQ(ams::wrap(-16.0f, -15.0f, -10.0f), -11.0f);
}
