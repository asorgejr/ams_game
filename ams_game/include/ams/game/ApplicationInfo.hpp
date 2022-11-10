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

/*[export module ams.game.ApplicationInfo]*/
/*[exclude begin]*/
#pragma once
/*[exclude end]*/
/*[import ams.AssertFailure]*/
#include <stdexcept>
#include <string>
#include <tuple>

/*[export]*/ namespace ams {

/**
 * @brief Compress a version number into a single integer.
 * @param variant - The variant of the version (bits 29-31) (3 bits)
 * @param major - The major version number (bits 22-28) (7 bits)
 * @param minor - The minor version number (bits 12-21) (10 bits)
 * @param patch - The patch version number (bits 0-11) (12 bits)
 */
constexpr uint32_t CompressVersion(uint32_t variant, uint32_t major, uint32_t minor, uint32_t patch) {
  if (variant > 7)  throw std::invalid_argument("Variant must be less than 8.");
  if (major > 127)  throw std::invalid_argument("Major must be less than 128.");
  if (minor > 1023) throw std::invalid_argument("Minor must be less than 1024.");
  if (patch > 4095) throw std::invalid_argument("Patch must be less than 4096.");
  return (variant << 29) | (major << 22) | (minor << 12) | patch;
}

/**
 * @brief Compress a string version number into a single integer.
 * @param version - The version string to compress.
 */
constexpr uint32_t CompressVersion(const std::string& version) {
  uint32_t variant = 0;
  uint32_t major = 0;
  uint32_t minor = 0;
  uint32_t patch = 0;
  sscanf_s(version.c_str(), "%u.%u.%u.%u", &variant, &major, &minor, &patch);
  return CompressVersion(variant, major, minor, patch);
}

/**
 * @brief Decompress a version number into its components.
 * @param version - The version number to decompress. Variant is bits 29-31, major is bits 22-28, minor is bits 12-21, and patch is bits 0-11.
 * @return - (variant, major, minor, patch)
 */
constexpr std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>
DecompressVersion(uint32_t version) {
  return std::make_tuple((version >> 29) & 0x7, (version >> 22) & 0x7F, (version >> 12) & 0x3FF, version & 0xFFF);
}

/**
 * @brief Application information.
 */
struct ApplicationInfo {
  /**
   * @brief The name of the application.
   */
  const std::string name;
  /**
   * @brief The version of the application. Use the ams::CompressVersion function to create this value.
   */
  const uint32_t version;
  /**
   * @brief The name of the engine.
   */
  const std::string engineName;
  /**
   * @brief The version of the engine. Use the ams::CompressVersion function to create this value.
   */
  const uint32_t engineVersion;
  /**
   * @brief The API version to use. Use the ams::CompressVersion function to create this value.
   */
  const uint32_t apiVersion;
};

} // ams
