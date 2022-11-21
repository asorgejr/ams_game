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

/*[module]*/
/*[exclude begin]*/
#pragma once
/*[exclude end]*/
/*[ignore begin]*/
#include "ams_core_export.hpp"
/*[ignore end]*/
/*[exclude begin]*/
#include "ams/config.hpp"
/*[exclude end]*/

/*[export module ams.Uuid]*/
#include <cstdint>
#include <cstddef>
#include <array>
#include <random>
#include <sstream>
#include <ranges>
#include <algorithm>
/*[import ams.config]*/


/*[export]*/ namespace ams {

/**
 * @brief This class is a 128-bit UUID based on the RFC 4122 standard.
 * @see https://tools.ietf.org/html/rfc4122
 */
struct AMS_CORE_EXPORT Uuid final {
public:
  uint64_t low = dis(gen);
  uint64_t high = dis(gen);
  /**
   * @brief Construct a new uuid object
   */
  Uuid() = default;
  
/**
   * @brief Construct a new uuid object
   * @param low The low 64 bits of the UUID
   * @param high The high 64 bits of the UUID
   */
  Uuid(uint64_t low, uint64_t high) : low(low), high(high) {}
  
  /**
   * @brief Construct a new uuid object
   * @param uuid The UUID to copy
   */
  explicit Uuid(const std::string& uuid) {
    *this = Uuid::fromStr(uuid);
  }

  /**
   * @brief Construct a new uuid object
   * @param other - The uuid to copy
   */
  Uuid(const Uuid& other) = default;
  
  Uuid& operator=(const Uuid& other) = default;

  bool operator==(const Uuid& other) const {
    // compare data elements
    return low == other.low && high == other.high;
  }

  bool operator!=(const Uuid& other) const {
    return !(*this == other);
  }

  /**
   * @brief Get the string representation of the uuid
   * @return std::string - The string representation of the uuid
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream ss{};
    ss << std::hex << low << high;
    // ensure that the string is 32 characters long
    std::string str = ss.str();
    str.insert(0, 32 - str.length(), '0');
    return str;
  }

  static bool isValidStr(const std::string& str) {
    if (str.length() != 32)
      return false;
    // return std::ranges::all_of(str, [](char c) {
    return std::all_of(str.begin(), str.end(), [](char c) {
      return std::isxdigit(c);
    });
  }
  
  static bool isValidStrfmt(const std::string& str) {
    if (str.length() != 36)
      return false;
    if (str[8] != '-' || str[13] != '-' || str[18] != '-' || str[23] != '-')
      return false;
    // return std::ranges::all_of(str, [](char c) {
    return std::all_of(str.begin(), str.end(), [](char c) {
      return std::isxdigit(c) || c == '-';
    });
  }

  [[nodiscard]] std::string toFormattedString() const {
    // format string as 8-4-4-4-12
    std::string str = toString();
    std::string formatted = str.substr(0, 8);
    formatted += "-";
    formatted += str.substr(8, 4);
    formatted += "-";
    formatted += str.substr(12, 4);
    formatted += "-";
    formatted += str.substr(16, 4);
    formatted += "-";
    formatted += str.substr(20, 12);
    return formatted;
  }
  
  /**
   * @brief Creates a uuid from a hex string.
   * @param str - The 32 or 36 char hex string to create the uuid from
   * @return uuid - The uuid created from the hex string
   */
  static Uuid fromStr(const std::string& str) {
    if (str.length() != 32) {
      if (str.length() != 36)
        throw std::invalid_argument("Invalid UUID string length");
      return fromStrfmt(str);
    }
    Uuid u(0,0);
    auto low = str.substr(0, 16);
    auto high = str.substr(16, 16);
    u.low = std::stoull(low, nullptr, 16);
    u.high = std::stoull(high, nullptr, 16);
    return u;
  }
  
  /**
   * @brief creates a uuid from a formatted hex string
   * @param str - The 8-4-4-4-12 formatted hex string to create the uuid from
   * @return uuid - The uuid created from the hex string
   */
  static Uuid fromStrfmt(const std::string& str) {
    if (!isValidStrfmt(str))
      throw std::invalid_argument("Invalid string");
    std::string unformatted = str;
    unformatted.erase(std::remove(unformatted.begin(), unformatted.end(), '-'), unformatted.end());
    return fromStr(unformatted);
  }
  
private:
  /**
   * The random device used to generate the uuid
   */
  inline static std::random_device rd = std::random_device();
  /**
   * The random engine used to generate the uuid
   */
  inline static std::mt19937_64 gen = std::mt19937_64(rd());
  /**
   * The distribution used to generate the uuid
   */
  inline static std::uniform_int_distribution<uint64_t> dis = std::uniform_int_distribution<uint64_t>(0, UINT64_MAX);
};

} // ams
