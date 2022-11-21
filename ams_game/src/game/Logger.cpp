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

#ifndef AMS_MODULES
#include "ams/game/Logger.hpp"
#include "ams/game/Exceptions.hpp"
#include "ams/game/Application.hpp"
#include "ams/game/Util.hpp"
#else
import ams.game.Logger;
import ams.game.Exceptions;
import ams.game.Application;
import ams.game.Util;
#endif
#include <iostream>
#include <chrono>
#include <format>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using namespace std::chrono;
using std::string;
using std::string_view;
namespace fs = std::filesystem;
using std::make_shared;
using spdlevel = spdlog::level::level_enum;

namespace ams {

#define FMT_STR "[{}] {} > {}"
#define FMT_STR_SRC "[{}] {} > {} < {}"

template<typename T>
using sptr = std::shared_ptr<T>;

auto asLocalTime(const system_clock::time_point tp) {
  return zoned_time{ current_zone(), tp };
}


std::string toString(auto tp) {
  return std::format("{:%F %T %Z}", tp);
}

std::string toString(const std::source_location& source) {
  return std::format("in {}() at {}:{}:{}",
                     source.function_name(),
                     std::filesystem::path(source.file_name()).filename().string(),
                     source.line(),
                     source.column());
}

constexpr string toString(LogLevel level) {
  switch (level) {
    case LogLevel::Fatal:
      return "FATAL";
    case LogLevel::Error:
      return "ERROR";
    case LogLevel::Warning:
      return "WARNING";
    case LogLevel::Info:
      return "INFO";
    case LogLevel::Debug:
      return "DEBUG";
    default:
      return "UNCLASSIFIED";
  }
}

constexpr spdlevel toSpdLogLevel(LogLevel level) {
  switch (level) {
    case LogLevel::Fatal:
      return spdlevel::critical;
    case LogLevel::Error:
      return spdlevel::err;
    case LogLevel::Warning:
      return spdlevel::warn;
    case LogLevel::Info:
      return spdlevel::info;
    case LogLevel::Debug:
      return spdlevel::debug;
    case LogLevel::All:
      return spdlevel::trace;
    case LogLevel::Trace:
      return spdlevel::trace;
    default:
      return spdlevel::off;
  }
}

struct Logger::Impl {
  const std::filesystem::path defaultLogFile = std::filesystem::temp_directory_path() / "log.txt";
  std::filesystem::path logFile = defaultLogFile;
  uint32_t maxFileSize = 1024 * 1024 * 10; // 10 MB
  LogLevel logLevel = LogLevel::Info;
  sptr<spdlog::sinks::stdout_color_sink_mt> stdoutSink;
  sptr<spdlog::sinks::rotating_file_sink_mt> fileSink;
  std::array<spdlog::sink_ptr, 2> sinks;
  sptr<spdlog::async_logger> logger;
  bool started = false;
  
  bool flushAll() {
    if (!logger) return false;
    logger->flush_on(spdlevel::err);
    logger->flush_on(spdlevel::critical);
    logger->flush_on(spdlevel::warn);
    logger->flush_on(spdlevel::info);
    logger->flush_on(spdlevel::debug);
    logger->flush_on(spdlevel::trace);
    logger->flush(); // just in case
    return true;
  }
  
  bool clearSinks() {
    if (!logger) return false;
    logger->sinks().clear();
    started = false;
    return true;
  }
  
  void stop() {
    if (!logger) return;
    logger->flush();
    logger->sinks().clear();
    started = false;
  }
  
  bool init() {
    if (started) return true;
    if (!logger) return false;
    if (!stdoutSink) return false;
    if (!fileSink) return false;
    logger->sinks().clear();
    logger->sinks().insert(logger->sinks().begin(), sinks.begin(), sinks.end());
    logger->set_level(toSpdLogLevel(logLevel));
    started = true;
    return true;
  }
  
  Impl(const std::string& name, const fs::path& file, uint32_t size, LogLevel level)
  : logFile(file), maxFileSize(size), logLevel(level)
  {
    spdlog::init_thread_pool(8192, 1);
    stdoutSink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
    fileSink = make_shared<spdlog::sinks::rotating_file_sink_mt>(logFile.string(), maxFileSize, 3);
    sinks = {stdoutSink, fileSink};
    logger = make_shared<spdlog::async_logger>(name, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_level(toSpdLogLevel(logLevel));
    logger->set_pattern("%v"); // we handle our own formatting.
    logger->flush();
    try {
      spdlog::register_logger(logger);
      started = true;
    } catch (const spdlog::spdlog_ex& ex) {
      std::cerr << "Failed to register logger: " << ex.what() << std::endl;
      started = false;
    }
  }
  
  ~Impl() {
    // shutdown logger
    logger->flush();
    logger->sinks().clear();
    spdlog::drop(logger->name());
    logger.reset();
    spdlog::shutdown();
  }
};

Logger::Impl* Logger::_impl = nullptr;
const Application* Logger::_app = nullptr;

void Logger::setLogLevel(LogLevel level) {
  if (!isInitialized())
    errNotInitialized();
  _impl->logLevel = level;
  _impl->logger->set_level(toSpdLogLevel(level));
}

void Logger::setLogFile(const std::filesystem::path& path) {
  if (!isInitialized())
    errNotInitialized();
  _impl->logFile = path;
  _impl->logger->sinks()[1] = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path.string(), _impl->maxFileSize, 3);
}

void Logger::setMaxTraces(uint32_t maxTraces) {
  if (!isInitialized())
    errNotInitialized();
  _impl->logger->sinks()[1] = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(_impl->logFile.string(), _impl->maxFileSize, maxTraces);
}

void Logger::setLoggerName(const std::string& name) {
  if (!isInitialized())
    errNotInitialized();
  _impl->stop();
  delete _impl;
  _impl = new Impl(name, _impl->logFile, _impl->maxFileSize, _impl->logLevel);
}

void Logger::log(const string_view& message, LogLevel level, const std::source_location& source) {
  if (level == LogLevel::None) return;
  if (!isInitialized()) {
    std::cerr << "A Logger method was called but Logger has not been initialized. < " << toString(source) << std::endl;
    std::cout << message << std::endl;
    return;
  }
  auto timestr = toString(asLocalTime(system_clock::now()));
  auto severity = toString(level);
  switch (level) {
    case LogLevel::Fatal:
      _impl->logger->critical(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    case LogLevel::Error:
      _impl->logger->error(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    case LogLevel::Warning:
      _impl->logger->warn(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    case LogLevel::Info:
      _impl->logger->info(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    case LogLevel::Debug:
      _impl->logger->debug(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    case LogLevel::Trace:
      _impl->logger->trace(FMT_STR_SRC, severity, timestr, message, toString(source));
      break;
    default:
      break;
  }
}

void Logger::log(const Exception& e) {
  if (!isInitialized()) {
    std::cerr << "A Logger method was called but Logger has not been initialized. " << std::endl;
    std::cerr << e.toString() << std::endl;
    return;
  }
  auto timestr = toString(asLocalTime(system_clock::now()));
  auto severity = toString(LogLevel::Error);
  _impl->logger->error(FMT_STR_SRC, severity, timestr, e.what(), toString(e.getTrace()));
}

bool Logger::initialize(const Application* app) {
  if (isInitialized()) {
    if (_app == app) {
      log("Logger is already initialized for this application.", LogLevel::Warning);
      return true;
    }
    if constexpr (AMSExceptions) {
      if (app != nullptr && _app != app) {
        throw LoggerException("Logger has already been initialized with a different Application instance.");
      }
    } else {
      std::cerr << "Logger already initialized" << std::endl;
      return false;
    }
  }
  if (!app) {
    if constexpr (AMSExceptions)
      throw NullPointerException("Application is null");
    else
      return false;
  }
  _app = app;
  _impl = new Impl(app->getName(), app->getAppDataDir() / "log.txt", 1024 * 1024 * 10, LogLevel::Info);
  return _impl != nullptr;
}

void Logger::destroy() {
  if (_impl != nullptr) {
    try {
      _impl->stop();
    } catch (const spdlog::spdlog_ex& ex) {}
    delete _impl;
    _impl = nullptr;
  }
  if (_app != nullptr) _app = nullptr;
}

bool Logger::isInitialized() {
  if (_impl == nullptr) {
    if (!_app)
      return false;
    initialize(_app);
  } else if (!_impl->started)
    return false;
  return _app != nullptr;
}

void Logger::errNotInitialized() {
  if (!isInitialized()) {
    if constexpr (!ErrNoThrow && AMSExceptions) {
      throw LoggerException("Logger not initialized");
    } else {
      std::cerr << "Logger not initialized" << std::endl;
      return;
    }
  }
}

}