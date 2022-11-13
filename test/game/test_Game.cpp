//
// Created by asorgejr on 10/6/2022.
//

#include <gtest/gtest.h>
#include <chrono>

#ifndef AMS_MODULES
#include <ams/game.hpp>
#include <ams/game/Util.hpp>
#else
import ams.game;
import ams.game.Util;
#endif

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

TEST(Game, Application) {
  Application app;
  EXPECT_EQ(app.getName(), "Application");
  EXPECT_NE(app.getCurrentScene(), nullptr);
  EXPECT_EQ(app.getCurrentScene()->getName(), "Application_default_" + to_string(app.getId()));
}

TEST(Game, ApplicationStaticInstnaceDestroyed) {
  if (AMSExceptions) {
    EXPECT_THROW(Application::getInstance(), NullPointerException);
  } else {
    EXPECT_EQ(Application::getInstance(), nullptr);
  }
}

TEST(Game, AppInitScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  EXPECT_NE(pScene, nullptr);
}

TEST(Game, AppSetCurrentScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  app.setCurrentScene(pScene->getName());
  EXPECT_EQ(app.getCurrentScene(), pScene);
}

TEST(Game, AppGetCurrentScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  app.setCurrentScene(pScene->getName());
  EXPECT_EQ(app.getCurrentScene(), pScene);
}

TEST(Game, AppSceneTryGet) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  Scene* pScene1 = nullptr;
  EXPECT_TRUE(app.tryGetScene("TestScene", pScene1));
  EXPECT_EQ(pScene1, pScene);
  Scene* pScene2 = nullptr;
  EXPECT_FALSE(app.tryGetScene("TestScene2", pScene2));
  EXPECT_EQ(pScene2, nullptr);
}

TEST(Game, AppGetScene) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  EXPECT_EQ(app.getScene("TestScene"), pScene);
#ifdef AMS_EXCEPTIONS
  EXPECT_ANY_THROW(app.getScene("TestScene2"));
#else
  EXPECT_EQ(app.getScene("TestScene2"), nullptr);
#endif
}

TEST(Game, AppWindow) {
  Application app;
  EXPECT_NE(app.getWindow(), nullptr);
  app.exit();
}

TEST(Game, SceneCreateEntity) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  EXPECT_NE(pEntity, nullptr);
  EXPECT_EQ(pEntity->getName(), "Object_" + to_string(pEntity->getId()));
}

TEST(Game, SceneCreateCamera) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  auto* pCamera = pEntity->addComponent<Camera>();
  EXPECT_NE(pCamera, nullptr);
}

TEST(Game, EntityAddComponent) {
  TestApplication app("TestApp", 1000ms);
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  auto* pComp = pEntity->addComponent<TestBehaviorVirtMethods>();
  app.setCurrentScene(pScene->getName());
  app.setVsyncTime(65);
  app.run();
  
  EXPECT_NE(pComp, nullptr);
  EXPECT_EQ(pComp->getName(), "Object_" + to_string(pComp->getId()));
  EXPECT_EQ(pComp->testWasEnabled, true);
  EXPECT_EQ(pComp->testWasStarted, true);
  EXPECT_GT(pComp->testUpdate, 60);
  app.exit();
}

TEST(Game, 100EntitiesAddComponentPerfTest) {
  TestApplication app("TestApp", 1000ms);
  auto* pScene = app.createScene("TestScene");
  std::vector<ams::Entity*> entities;
  for (int i = 0; i < 100; i++) {
    auto* pEntity = pScene->createEntity();
    pEntity->addComponent<TestBehaviorVirtMethods>();
    entities.push_back(pEntity);
  }
  app.setCurrentScene(pScene->getName());
  app.setVsyncTime(65);
  app.run();
  
  for (auto& pEntity : entities) {
    auto* pComp = pEntity->getComponent<TestBehaviorVirtMethods>();
    EXPECT_NE(pComp, nullptr);
    EXPECT_EQ(pComp->getName(), "Object_" + to_string(pComp->getId()));
    EXPECT_EQ(pComp->testWasEnabled, true);
    EXPECT_EQ(pComp->testWasStarted, true);
    EXPECT_GT(pComp->testUpdate, 60);
  }
  app.exit();
}
