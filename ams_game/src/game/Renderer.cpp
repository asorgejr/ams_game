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
#include "ams/game/Renderer.hpp"
#include "ams/game/internal/RendererOpenGL.hpp"
#include "ams/game/internal/RendererVulkan.hpp"
#else
import ams.game.Application;
import ams.game.Renderer;
import ams.game.internal.RendererOpenGL;
import ams.game.internal.RendererVulkan;
#endif

using namespace ams::internal;

namespace ams {

Renderer::Renderer(Application* application) {
  _application = application;
  _scene = application->getCurrentScene();
  _sceneChangeCallback = [this](Scene* oldScene, Scene* newScene) {
    this->_scene = newScene;
  };
  _application->registerOnSceneChangeCallback(_sceneChangeCallback);
  
  #ifndef AMS_REQUIRE_OPENGL
  auto appInfo = _application->getInfo();
  _rendererImpl = std::make_unique<RendererVulkan>(appInfo, application->getWindow());
  #else
  _rendererImpl = std::make_unique<RendererOpenGL>(application->getInfo(), application->getWindow());
  #endif
  if (!_rendererImpl) {
    throw std::runtime_error("Failed to create renderer backend");
  }
  _rendererImpl->init();
}

Renderer::~Renderer() {
  if (_rendererImpl)
    _rendererImpl->shutdown();
  _application->unregisterOnSceneChangeCallback(_sceneChangeCallback);
}

void Renderer::render() {
  _rendererImpl->beginFrame();
  _rendererImpl->draw();
  _rendererImpl->endFrame();
}

} // ams
