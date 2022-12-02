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

#if defined(_MSC_VER) && defined(CLION_FIX_ANALYSIS)
#ifndef __cpp_consteval
#define __cpp_consteval// TODO: This is a hack to CLion analysis of source_location. MSVC will emit a warning. TODO: remove this when CLion gets patched.
#endif
#endif

export module ams.Exceptions:Exception;
export import <exception>;
export import <format>;
export import <source_location>;
export import <string>;


namespace ams {

export class Exception : public std::exception {
protected:
  const std::source_location trace;
  const std::string message;

public:
  explicit Exception(const std::string& message = "An exception has occurred",
                     const std::source_location& trace = std::source_location::current())
      : std::exception(message.c_str()), trace(trace), message(message) {}

  ~Exception() override = default;

  [[nodiscard]] virtual const std::source_location& getTrace() const noexcept {
    return trace;
  }

  [[nodiscard]] virtual std::string toString() const {
    return std::format("{}: {}:{}:{}", what(), trace.file_name(), trace.line(), trace.column());
  }
};

}// namespace ams