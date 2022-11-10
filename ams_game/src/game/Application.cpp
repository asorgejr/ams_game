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
#include "ams/game/Application.hpp"
#include "ams/game/Scene.hpp"
#include "ams/game/Util.hpp"
#include "ams/game/MeshLoaders.hpp"
#else
import ams.game.Application;
import ams.game.Scene;
import ams.game.Util;
import ams.game.MeshLoaders;
#endif
#include <thread>
#include <iostream>
#include <cassert>

#include <GLFW/glfw3.h>

using namespace std::chrono;

namespace ams {

constexpr auto tu0s = time_unit_1s * 0;

Vec2<int> calcDisplayWindowCenter(const Display& disp, const Vec2<int>& winSize) {
  auto dispSize = disp.getSize();
  return Vec2<int>(dispSize.x / 2 - winSize.x / 2, dispSize.y / 2 - winSize.y / 2);
}

Application::Application(const std::string& name, const WindowConfig& cfg)
: Object(name),
_windowConfig(cfg)
{
  assert(glfwInit() == GLFW_TRUE);

  if (_instance != nullptr) {
    throwOrDefault<std::runtime_error, void>("Application already exists");
    delete _instance;
  }
  _instance = this;
  _displays = Display::getDisplays();
  if (_displays.size() == 0) {
    throwOrDefault<std::runtime_error, void>("No displays found");
    delete _instance;
  }
  auto* win = createWindow(_windowConfig);
  if (win == nullptr) {
    throwOrDefault<std::runtime_error, void>("Failed to create window");
    delete _instance;
    return;
  }
  
  win->registerWindowCloseCallback({[&]() {
    _instance->stop();
  }});
  _currentScene = getDefaultScene();
}

Application::~Application() {
  if (_instance == this) {
    _instance = nullptr;
  }
  _windows.clear();
  glfwTerminate();
}

Scene* Application::getCurrentScene() const {
  return _currentScene;
}

Scene* Application::setCurrentScene(const std::string& name) {
  if (_currentScene != nullptr) {
    _currentScene->onExit();
  }
  _currentScene = getScene(name);
  if (_currentScene != nullptr) {
    _currentScene->onEnter();
  }
  return _currentScene;
}

bool Application::tryGetScene(const std::string& name, Scene*& scene) const {
  for (auto& upScene : scenes) {
    if (upScene->getName() == name) {
      scene = upScene.get();
      return true;
    }
  }
  return false;
}

Scene* Application::getScene(const std::string& name) const {
  Scene* ret = nullptr;
  bool result = tryGetScene(name, ret);
  if constexpr (AMSExceptions) {
    if (!result)
      throw std::runtime_error("Scene not found");
  }
  return ret;
}

Scene* Application::createScene(const std::string& name) {
  for (auto& upScene : scenes) {
    if (upScene->getName() == name) {
      if constexpr (AMSExceptions) {
        throw std::runtime_error("Scene already exists");
      }
      return upScene.get();
    }
  }
  auto upScene = std::make_unique<Scene>(this, name);
  auto pScene = upScene.get();
  scenes.push_back(std::move(upScene));
  return pScene;
}

time_unit Application::getElapsedTime() const {
  return duration_cast<time_unit>(clk_t::now() - startTime);
}

time_unit Application::getDeltaTime() const {
  auto ret = duration_cast<time_unit>(clk_t::now() - lastFrameTime);
  return ret;
}

Application* Application::getInstance() {
  if constexpr(AMSExceptions)
    if (_instance == nullptr)
      throw NullPointerException("An instance of Application has not been created");
  return _instance;
}

void Application::run() {
  lastFrameTime = startTime;
  time_unit lag = time_unit_1s * 0; // 0s
  
  running = true;
  onRunStart(); // virtual method - noop unless overridden
  // main loop
  while (running) {
    onFrameStart(); // virtual method - noop unless overridden
    auto now = clk_t::now();
    auto deltaTime = duration_cast<time_unit>(now - lastFrameTime);
    lastFrameTime = now;
    lag += deltaTime;

    // fixed update
    while (lag >= fixedFrameTime && running) {
      onFixedFrameStart(); // virtual method - noop unless overridden
      _currentScene->onUpdate();
      lag -= fixedFrameTime;
      onFixedFrameEnd(); // virtual method - noop unless overridden
    }

    _currentScene->onRender();
    for (auto& win : _windows) {
      win->update();
      if (win->getShouldClose()) {
        _windows.erase(std::find(_windows.begin(), _windows.end(), win));
        if (_windows.size() == 0)
          stop();
      }
    }
    // limit frame rate (vsync)
    if (vsyncTime > tu0s) {
      auto sleepTime = vsyncTime - duration_cast<time_unit>(clk_t::now() - lastFrameTime);
      if (sleepTime > tu0s) {
        std::this_thread::sleep_for(sleepTime);
      }
    }
    onFrameEnd(); // virtual method - noop unless overridden
  }
  onRunEnd(); // virtual method - noop unless overridden
  // exit();
}

void Application::stop() {
  running = false;
}

void Application::exit() {
  stop();
  if (_currentScene != nullptr) {
    _currentScene->_frameIsValid = false;
    _currentScene->onExit();
  }
  _currentScene = nullptr;
  for (auto& upScene : scenes) {
    upScene->onExit();
  }
  scenes.clear();
}

Scene* Application::getDefaultScene() {
  const auto defaultSceneName = name + "_default_" + std::to_string(id);
  Scene* pScene = nullptr;
  auto hasScene = tryGetScene(defaultSceneName, pScene);
  if (!hasScene) {
    pScene = createScene(defaultSceneName);
    _currentScene = pScene;
  }
  return pScene;
}

void Application::setTargetFrameRate(float goalFPS) {
  if (goalFPS < 1.0f) goalFPS = 1.0f;
  targetFrameTime = fpsToUnit<time_unit>(goalFPS);
}

float Application::getTargetFrameRate() const {
  return unitToFps<time_unit>(targetFrameTime);
}

void Application::setFixedFrameRate(float fixedFPS) {
  if (fixedFPS < 1.0f) fixedFPS = 1.0f;
  fixedFrameTime = fpsToUnit<time_unit>(fixedFPS);
}

float Application::getFixedFrameRate() const {
  return unitToFps<time_unit>(fixedFrameTime);
}

time_unit Application::getFixedFrameTime() const {
  return fixedFrameTime;
}

Window* Application::getWindow() {
  if (_windows.empty()) {
    if constexpr (AMSExceptions) {
      throw std::runtime_error("No windows exist");
    }
    return nullptr;
  }
  return _windows[0].get();
}

void Application::setVsyncTime(float vsyncFPS) {
  if (vsyncFPS < 0.0f) vsyncFPS = 0.0f;
  vsyncTime = fpsToUnit<time_unit>(vsyncFPS);
}

float Application::getVsyncTime() const {
  return unitToFps<time_unit>(vsyncTime);
}

Window* Application::getWindow(GLFWwindow* window) {
  for (auto& win : _windows) {
    if (win->getHandle() == window)
      return win.get();
  }
  return nullptr;
}

Window* Application::createWindow(const WindowConfig& cfg) {
  _windows.push_back(std::make_unique<Window>(_displays[0], _windowConfig));
  auto* win = _windows[_windows.size()-1].get();
  if (win == nullptr)
    return win; // errors handled in App constructor.
  if (!_windowConfig.fullscreen) {
    win->setPosition(calcDisplayWindowCenter(_displays[0], _windowConfig.size));
  }
  return win;
}

void Application::handleWindowClose(GLFWwindow* window) {
  auto* app = getInstance();
  if (app == nullptr) return;
  auto* win = getWindow(window);
  if (win != nullptr) {
    win->destroy();
    _windows.erase(std::find_if(_windows.begin(), _windows.end(), [win](auto& upWin) {
      return upWin.get() == win;
    }));
  }
  if (_windows.empty()) {
    app->stop();
  }
}

ApplicationInfo Application::getInfo() const {
  return info;
}

} // ams
