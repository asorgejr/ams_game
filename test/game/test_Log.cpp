//
// Created by asorgejr on 10/6/2022.
//

#ifndef AMS_MODULES
#include <ams/game.hpp>
#else
import ams.game;
#endif

#include <gtest/gtest.h>
#include <filesystem>
#include <chrono>


using std::to_string;
using namespace std::chrono;
using namespace std::chrono_literals;
namespace fs = std::filesystem;
using namespace ams;

const ApplicationInfo AppTestCfg {
  .name = "AMSTestApplication"
};


class TestApplication : public Application {
private:
  time_point<clk_t> start;
  milliseconds duration = 1000ms;
public:
  using Application::Application;
  TestApplication(const std::string& name, const milliseconds& duration) : Application(name) {
    this->duration = duration;
  }
    
protected:
  void onRunStart() override {
    start = clk_t::now();
  }
  
  void onFrameEnd() override {
    auto elapsed = clk_t::now() - start;
    if (elapsed > duration) {
      stop();
    }
  }
};


void cleanup(const fs::path& dir) {
  fs::remove_all(dir);
}


TEST(Log, CatchWhenNoApp) {
  ASSERT_NO_THROW(Logger::log("test"));
}

TEST(Log, CreatesLogDir) {
  auto* app = new Application(AppTestCfg);
  auto logdir = app->getAppDataDir();
  // Logger is started by Application
  bool direxists = fs::exists(app->getAppDataDir());
  bool isdir = fs::is_directory(app->getAppDataDir());
  ASSERT_TRUE(direxists);
  ASSERT_TRUE(isdir);
  delete app;
  cleanup(logdir);
}


TEST(Log, NoThrowWhenApp) {
  auto* app = new Application(AppTestCfg);
  auto logdir = app->getAppDataDir();
  ASSERT_NO_THROW(Logger::log("test log"));
  ASSERT_NO_THROW(Logger::log("test trace", LogLevel::Trace, std::source_location::current()));
  ASSERT_NO_THROW(Logger::log("test debug", LogLevel::Debug, std::source_location::current()));
  ASSERT_NO_THROW(Logger::log("test info", LogLevel::Info));
  ASSERT_NO_THROW(Logger::log("test warn", LogLevel::Warning, std::source_location::current()));
  ASSERT_NO_THROW(Logger::log("test error", LogLevel::Error, std::source_location::current()));
  ASSERT_NO_THROW(Logger::log("test fatal", LogLevel::Fatal, std::source_location::current()));
  delete app;
  cleanup(logdir);
}

TEST(Log, CatchAfterAppDeleted) {
  auto* app = new Application(AppTestCfg);
  auto logdir = app->getAppDataDir();
  delete app;
  ASSERT_NO_THROW(Logger::log("test"));
  ASSERT_NO_THROW(Logger::destroy());
  cleanup(logdir);
}

TEST(Log, LogCatchesAlreadyInitialized) {
  auto* app = new Application(AppTestCfg);
  auto logdir = app->getAppDataDir();
  ASSERT_NO_THROW(Logger::initialize(app));
  delete app;
  cleanup(logdir);
}

TEST(Log, LogCatchesNullAppPtr) {
  Application* app = nullptr;
  if (AMSExceptions)
    ASSERT_THROW(Logger::initialize(app), NullPointerException);
  else
    ASSERT_NO_THROW(Logger::initialize(app));
}