//
// Created by asorgejr on 10/6/2022.
//

#ifndef AMS_MODULES
#include <ams/game.hpp>
#include <ams/game/Util.hpp>
#else
import ams.game;
import ams.game.Util;
#endif

#include <gtest/gtest.h>
#include <chrono>


using std::to_string;
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace ams;

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

class TestBehaviorVirtMethods : public Behavior {
AMSBehavior(TestBehaviorVirtMethods)
private:
  time_point<clk_t> _start = clk_t::now();
  Application* _app = nullptr;
public:
  int testUpdate = 0;
  bool testWasEnabled = false;
  bool testWasDisabled = false;
  bool testWasStarted = false;
  void onEnable() override {
    testWasEnabled = true;
  }
  void onDisable() override {
    testWasDisabled = true;
  }
  void onStart() override {
    testWasStarted = true;
    _app = Application::getInstance();
  }
  void onUpdate() override {
    testUpdate++;
  }
};

TEST(Application, App) {
  Application app;
  EXPECT_EQ(app.getName(), "Application");
  EXPECT_NE(app.getCurrentScene(), nullptr);
  EXPECT_EQ(app.getCurrentScene()->getName(), "Application_default_" + to_string(app.getId()));
}

TEST(Application, AppStaticInstnaceDestroyed) {
  if (AMSExceptions) {
    EXPECT_THROW(Application::getInstance(), NullPointerException);
  } else {
    EXPECT_EQ(Application::getInstance(), nullptr);
  }
}

TEST(Application, AppInitScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  EXPECT_NE(pScene, nullptr);
}

TEST(Application, AppSetCurrentScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  app.setCurrentScene(pScene->getName());
  EXPECT_EQ(app.getCurrentScene(), pScene);
}

TEST(Application, AppGetCurrentScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  app.setCurrentScene(pScene->getName());
  EXPECT_EQ(app.getCurrentScene(), pScene);
}

TEST(Application, AppSceneTryGet) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  Scene* pScene1 = nullptr;
  EXPECT_TRUE(app.tryGetScene("TestScene", pScene1));
  EXPECT_EQ(pScene1, pScene);
  Scene* pScene2 = nullptr;
  EXPECT_FALSE(app.tryGetScene("TestScene2", pScene2));
  EXPECT_EQ(pScene2, nullptr);
}

TEST(Application, AppGetScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  EXPECT_EQ(app.getScene("TestScene"), pScene);
#ifdef AMS_EXCEPTIONS
  EXPECT_ANY_THROW(app.getScene("TestScene2"));
#else
  EXPECT_EQ(app.getScene("TestScene2"), nullptr);
#endif
}

TEST(Application, AppWindow) {
  Application app;
  EXPECT_NE(app.getWindow(), nullptr);
  app.exit();
}

