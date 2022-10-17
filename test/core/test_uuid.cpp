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

#include <ams/uuid.hpp>

#else
import ams.uuid;
#endif

TEST(uuid, uuid) {
  ams::uuid uuid;
  EXPECT_NE(uuid, ams::uuid());
}

TEST(uuid, uuid_string) {
  ams::uuid uuid(0, 0);
  EXPECT_EQ(uuid.to_string(), "00000000000000000000000000000000");
}

TEST(uuid, uuid_formatted_string) {
  ams::uuid uuid = ams::uuid(0, 0);
  EXPECT_EQ(uuid.to_formatted_string(), "00000000-0000-0000-0000-000000000000");
}

TEST(uuid, uuid_from_string) {
  ams::uuid uuid = ams::uuid::from_str("aabbccddeeff00112233445566778899");
  EXPECT_EQ(uuid.to_string(), "aabbccddeeff00112233445566778899");
}

TEST(uuid, uuid_from_formatted_string) {
  ams::uuid uuid = ams::uuid::from_strfmt("00000000-0000-0000-0000-000000000000");
  EXPECT_EQ(uuid, ams::uuid(0, 0));
}

TEST(uuid, uuid_from_two_values) {
  uint64_t val1 = 0xAFAFAFAFAFAFAFAF;
  uint64_t val2 = 0xBFBFBFBFBFBFBFBF;
  ams::uuid uuid = ams::uuid(val1, val2);
  EXPECT_EQ(uuid.to_string(), "afafafafafafafafbfbfbfbfbfbfbfbf");
}

TEST(uuid, uuid_throw_for_invalid_string) {
  EXPECT_THROW(ams::uuid::from_str("aabbccddeeff0011223344556677889"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("aabbccddeeff00112233445566778899a"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("abcdefghijklmnopqrstuvwxyz/*-+++"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("ffffffff-ffff-ffff-ffff-ffffffffffff"), std::invalid_argument);
}

TEST(uuid, uuid_throw_for_invalid_formatted_string) {
  EXPECT_THROW(ams::uuid::from_str("aabbccddeeff0011223344556677889"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("aabbccddeeff00112233445566778899a"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("abcdefghijklmnopqrstuvwxyz/*-+++"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_str("ffffffff-ffff-ffff-ffff-ffffffffffff"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_strfmt("00000000-0000-0000-0000-00000000000"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_strfmt("00000000-0000-0000-0000-0000000000000"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_strfmt("00000000-0000-0000-0000-000000000000-"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_strfmt("0000000-0000-0000-0000-0000000000000"), std::invalid_argument);
  EXPECT_THROW(ams::uuid::from_strfmt("000000000-0000-0000-0000-00000000000"), std::invalid_argument);
}
