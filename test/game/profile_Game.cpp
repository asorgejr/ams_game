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

#include <cassert>

#ifndef AMS_MODULES
#include <iostream>
#include <ams/game.hpp>
#include <ams/game/Util.hpp>
#else
import <iostream>
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
  milliseconds duration = 0ms;
  time_point<clk_t> fstart;
public:
  using Application::Application;
  TestApplication(const std::string& name, const milliseconds& duration) : Application(name) {
    this->duration = duration;
  }

protected:
  void onRunStart() override {
    start = clk_t::now();
  }
  
  void onFrameStart() override {
    fstart = clk_t::now();
  }

  void onFrameEnd() override {
    auto elapsed = clk_t::now() - start;
    if (duration > 0ms && elapsed > duration) {
      stop();
    }
    auto fend = clk_t::now();
    auto usdur = duration_cast<microseconds>(fend - fstart);
    // std::cout << "fps: " << unitToFps(usdur) << std::endl
    // << "diff: " << usdur.count() << std::endl;
  }
};

class TestBehaviorVirtMethods : public Behavior {
AMSBehavior(TestBehaviorVirtMethods)
private:
  time_point<clk_t> _start = clk_t::now();
  time_point<clk_t> _last = _start;
  Application* _app = nullptr;
public:
  int testUpdate = 0;
  bool testWasEnabled = false;
  bool testWasDisabled = false;
  bool testWasStarted = false;
  void onEnable() override { testWasEnabled = true; }
  void onDisable() override { testWasDisabled = true; }
  void onStart() override {
    testWasStarted = true;
    _app = Application::getInstance();
  }
  
  void onUpdate() override {
    testUpdate++;
  }
};


int main() {
  TestApplication app("TestApplication");
  auto* pScene = app.createScene("TestScene");
  auto* pEntity = pScene->createEntity();
  auto* pComp = pEntity->addComponent<TestBehaviorVirtMethods>();
  app.setCurrentScene(pScene->getName());
  app.setVsyncTime(0);
  app.run();
  
  assert(pComp->testWasEnabled);
  assert(pComp->testWasStarted);
  
  app.exit();
  return 0;
}
