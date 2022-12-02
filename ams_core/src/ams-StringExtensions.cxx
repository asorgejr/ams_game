module;

module ams:StringExtensions_impl;
#ifndef AMS_MODULES_STD
import <string>;
import <vector>;
#endif
#ifdef AMS_MODULES_STD
import std;
#endif

namespace ams {
std::vector<std::string> split(const std::string& str, const std::string& delim) {
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());
  return tokens;
}

std::vector<std::string> split(const std::string& str, char delim) {
  return split(str, std::string(1, delim));
}
}// namespace ams
