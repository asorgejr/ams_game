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

#pragma once
#include <cmath>
#include <string>
#include <ams/StringExtensions.hpp>

namespace ams {

enum class BoxCommentStyle {
  Star,
  Slash,
};

inline std::string boxComment(const std::string& comment, BoxCommentStyle style=BoxCommentStyle::Slash,
                              int padding = 0, int indent = 0) {
  auto ind = std::string(indent, ' ');
  auto lines = split(comment, '\n');
  // get the longest line
  auto longest = 0;
  for (auto& line : lines) {
    if (line.size() > longest) {
      longest = line.size();
    }
  }
  auto result = ind + "/" + std::string(longest + 4 + padding * 2, style == BoxCommentStyle::Slash ? '/' : '*') + "/\n";
  for (auto& line : lines) {
    int textpad = 1 + padding + std::ceil(double(longest-line.length())/2);
    
    auto cmline = ind + (style == BoxCommentStyle::Slash ? "//" : "/*") + std::string(textpad, ' ') + line;
    cmline += std::string(textpad - (longest-line.length())%2, ' ')
      + (style == BoxCommentStyle::Slash ? "//" : "*/") + "\n";
    result += cmline;
  }
  result += ind + "/" + std::string(longest + 4 + padding * 2, style == BoxCommentStyle::Slash ? '/' : '*') + "/";
  return result;
}

}
