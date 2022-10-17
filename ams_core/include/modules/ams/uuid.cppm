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

module;
#include <boost/multiprecision/cpp_int.hpp>

export module ams.uuid;
import <array>;
import <random>;
import <sstream>;
import ams.config;


namespace ams {

const size_t _UUID_SIZE = 2;

using uint128_t = boost::multiprecision::uint128_t;

/**
 * @brief A class that generates a UUID.
 * @details This class generates a UUID based on the RFC 4122 standard.
 * @see https://tools.ietf.org/html/rfc4122
 */
export struct uuid final {
private:
  /**
   * The underlying data of the UUID. A series of 8 64-bit integers.
   */
  uint128_t data;

public:
  /**
   * @brief Construct a new uuid object
   */
  uuid() : data(dis(gen)) {}
  
  constexpr uuid(uint64_t val1, uint64_t val2)
    : data((uint128_t(val1) << 64) | uint128_t(val2)) {}

  /**
   * @brief Construct a new uuid object
   * @param other - The uuid to copy
   */
  constexpr uuid(const uuid& other) {
    data = other.data;
  }
  
  constexpr uuid& operator=(const uuid& other) = default;

  constexpr bool operator==(const uuid& other) const {
    return data == other.data;
  }

  constexpr bool operator!=(const uuid& other) const {
    return !(*this == other);
  }

  /**
   * @brief Get the string representation of the uuid
   * @return std::string - The string representation of the uuid
   */
  [[nodiscard]] std::string to_string() const {
    std::stringstream ss{};
    ss << std::hex << data;
    // ensure that the string is 32 characters long
    std::string str = ss.str();
    str.insert(0, 32 - str.length(), '0');
    return str;
  }

  static constexpr bool is_valid_str(const std::string& str) {
    if (str.length() != 32)
      return false;
    return std::ranges::all_of(str, [](char c) {
      return std::isxdigit(c);
    });
  }
  
  static constexpr bool is_valid_strfmt(const std::string& str) {
    if (str.length() != 36)
      return false;
    if (str[8] != '-' || str[13] != '-' || str[18] != '-' || str[23] != '-')
      return false;
    return std::ranges::all_of(str, [](char c) {
      return std::isxdigit(c) || c == '-';
    });
  }

  [[nodiscard]] std::string to_formatted_string() const {
    // format string as 8-4-4-4-12
    std::string str = to_string();
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
   * @brief creates a uuid from a hex string
   * @param str - The 32 char hex string to create the uuid from
   * @return uuid - The uuid created from the hex string
   */
  static uuid from_str(const std::string& str) {
    if (!is_valid_str(str))
      throw std::invalid_argument("Invalid string");
    uuid u;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> u.data;
    return u;
  }
  
  /**
   * @brief creates a uuid from a formatted hex string
   * @param str - The 8-4-4-4-12 formatted hex string to create the uuid from
   * @return uuid - The uuid created from the hex string
   */
  static uuid from_strfmt(const std::string& str) {
    if (!is_valid_strfmt(str))
      throw std::invalid_argument("Invalid string");
    std::string unformatted = str;
    unformatted.erase(std::remove(unformatted.begin(), unformatted.end(), '-'), unformatted.end());
    return from_str(unformatted);
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
