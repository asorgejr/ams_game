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
#include "ams/game/Entity.hpp"
#include "ams/game/Component.hpp"
#include "ams/game/Scene.hpp"
#else
import ams.game.Entity;
import ams.game.Component;
import ams.game.Scene;
#endif

namespace ams {

Entity::Entity(Scene* scene) : Object(), _behaviors(
  [&](Behavior* pB) { _scene->registerBehavior(pB); },
  [&](Behavior* pB) { _scene->unregisterBehavior(pB); }
  )
{
  if constexpr (AMSExceptions)
    if (scene == nullptr)
      throw NullPointerException("Scene is null");
  this->_scene = scene;
  auto xform = std::make_unique<Transform>(this);
  _transform = xform.get();
  _components.emplace_back(std::move(xform));
}

void Entity::destroy() {
  _scene->destroyEntity(this);
}

Scene* Entity::getScene() const {
  return _scene;
}

} // ams
