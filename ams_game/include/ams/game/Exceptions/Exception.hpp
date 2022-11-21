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
// This file uses metatags to convert headers to module-interfaces using header2module.py.
// Any block comment formatted as: /*[   ]*/ is a metatag and other code may depend on it.
// Proceed with caution when modifying such comments.

/*[module]*/
/*[exclude begin]*/
#pragma once
#include "ams_game_sysinfo.hpp"
#if defined(AMS_OS_WINDOWS)
  #ifndef __cpp_consteval
    #define __cpp_consteval // TODO: This is a hack to suppress a warning in the Windows SDK.
  #endif
#endif
/*[exclude end]*/

/*[export module ams.game.Exception]*/
#include <exception>
#include <string>
#include <format>
#include <source_location>
/*[exclude begin]*/
/*[exclude end]*/


/*[export]*/ namespace ams {

class Exception : public std::exception {
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

} // ams
