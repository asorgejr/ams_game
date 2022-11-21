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
/*[ignore begin]*/
#pragma once
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[export module ams.Logger]*/
#include <source_location>
#include <string_view>
#include <filesystem>

/*[export]*/ namespace ams {

class Application;
class Exception;

enum class LogLevel {
  None = 0x0,
  Fatal = 0x1,
  Error = 0x2,
  Warning = 0x4,
  Info = 0x8,
  Debug = 0x10,
  Trace = 0x20,
  All = 0x3F
};


class AMS_GAME_EXPORT Logger {
private:
  struct Impl;
  static Impl* _impl;
  static const Application* _app;
  static constexpr bool ErrNoThrow = true;
public:
  static void setLogLevel(LogLevel level);
  
  static void setLogFile(const std::filesystem::path& path);
  
  static void setMaxTraces(uint32_t maxTraces);
  
  static void setLoggerName(const std::string& name);
  
  static void log(const std::string_view& message,
                  LogLevel level=LogLevel::Info,
                  const std::source_location& source=std::source_location::current());
  
  static void log(const Exception& e);
  
public:
  /**
   * @brief Initializes the logger.
   * @details When an Application is constructed, this method is automatically called. If initialize() is called again,
   * an error will be logged and the method will return false.
   * @param app 
   * @return 
   */
  static bool initialize(const Application* app);
  static void destroy();
private:
  static bool isInitialized();
  static void errNotInitialized();
  
  friend class Application;
};

// end
} // ams
