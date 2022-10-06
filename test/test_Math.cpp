//
// Created by asorgejr on 9/25/2022.
//

#include <gtest/gtest.h>
#ifndef AMS_MODULES
#include "ams/Math.hpp"
#else
import ams.Math;
#endif


TEST(Math, abs) {
    EXPECT_EQ(ams::abs(1), 1);
    EXPECT_EQ(ams::abs(-1), 1);
    EXPECT_EQ(ams::abs(0), 0);
    EXPECT_EQ(ams::abs(-0), 0);
    EXPECT_EQ(ams::abs(1.0), 1.0);
    EXPECT_EQ(ams::abs(-1.0), 1.0);
    EXPECT_EQ(ams::abs(0.0), 0.0);
    EXPECT_EQ(ams::abs(-0.0), 0.0);
}

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
