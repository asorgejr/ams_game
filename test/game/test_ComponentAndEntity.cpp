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
#include <ams/game.hpp>
#include <ams/game/Util.hpp>
#else
import ams.game;
import ams.game.Util;
#endif

#include <gtest/gtest.h>
#include <filesystem>
#include <chrono>

using std::to_string;
using namespace std::chrono;
using namespace std::chrono_literals;
namespace fs = std::filesystem;
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


TEST(Entity, SceneCreateEntity) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  EXPECT_NE(pEntity, nullptr);
  EXPECT_EQ(pEntity->getName(), "Object_" + to_string(pEntity->getId()));
}

TEST(Entity, SceneCreateCamera) {
  Application app;
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  auto* pCamera = pEntity->addComponent<Camera>();
  EXPECT_NE(pCamera, nullptr);
}

TEST(Entity, AddComponent) {
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

TEST(Entity, AddComponents) {
  TestApplication app("TestApp", 1000ms);
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  auto[comp1, comp2] = pEntity->addComponents<TestBehaviorVirtMethods, TestBehaviorVirtMethods>();
  app.setCurrentScene(pScene->getName());
  app.run();

  EXPECT_NE(comp1, nullptr);
  EXPECT_NE(comp2, nullptr);
  app.exit();
}

TEST(Entity, AddExtraTransformFails) {
  TestApplication app("TestApp", 1000ms);
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  EXPECT_NE(pEntity->getTransform(), nullptr); // default transform is always added
  if (AMSExceptions) {
    EXPECT_ANY_THROW(pEntity->addComponent<Transform>());
  } else {
    EXPECT_EQ(pEntity->addComponent<Transform>(), nullptr);
  }
  app.exit();
}

TEST(Entities, 100AddComponentPerfTest) {
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
