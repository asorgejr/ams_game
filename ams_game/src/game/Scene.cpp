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
#include "ams/game/Scene.hpp"
#include "ams/game/Transform.hpp"
#include "ams/game/Entity.hpp"
#include "ams/game/Camera.hpp"
#include "ams/game/Behavior.hpp"
#include "ams/game/Application.hpp"

#else
import ams.game.Scene;
import ams.game.Transform;
import ams.game.Entity;
import ams.game.Behavior;
import ams.game.Application;
import ams.game.Camera;
import ams.game.Exceptions;
#endif

using namespace ams::internal;

namespace ams {

Scene::Scene(Application* app, const std::string& name)
: Object(name), _application(app)
{
  if constexpr (AMSExceptions)
    if (app == nullptr)
      throw NullPointerException("Application is null");
  _entities = std::map<uint64_t, std::unique_ptr<Entity>>();
}

Entity* Scene::createEntity() {
  auto* pEntity = new Entity(this);
  auto upEntity = std::unique_ptr<Entity>(pEntity);
  for (auto* behavior : upEntity->_behaviors)
    registerBehavior(behavior);
  _entities[upEntity->id] = std::move(upEntity);
  return pEntity;
}

Entity* Scene::createEntity(const std::string& name) {
  auto* pEntity = new Entity(this, name);
  auto upEntity = std::unique_ptr<Entity>(pEntity);
  for (auto* behavior : upEntity->_behaviors)
    registerBehavior(behavior);
  _entities[upEntity->id] = std::move(upEntity);
  return pEntity;
}

Entity* Scene::createEntity(const std::string& name, Transform* parent) {
  if constexpr (AMSExceptions)
    if (parent == nullptr)
      throw NullPointerException("Parent is null");
  auto upEntity = std::unique_ptr<Entity>(new Entity(this, name, parent));
  auto pEntity = upEntity.get();
  _entities[upEntity->id] = std::move(upEntity);
  for (auto* behavior : pEntity->_behaviors)
    registerBehavior(behavior);
  return pEntity;
}

bool Scene::destroyEntity(Entity* entity) {
  if constexpr (AMSExceptions)
    if (entity == nullptr)
      throw NullPointerException("Entity is null");
  if (_entities.find(entity->id) != _entities.end()) {
    for (auto* behavior : entity->_behaviors)
      unregisterBehavior(behavior);
    _entities.erase(entity->id);
    return true;
  }
  return false;
}

void Scene::onEnter() {
  for (auto& [id, behavior] : _behaviors)
    behavior->onEnable();
}

void Scene::onExit() {
  _frameIsValid.store(false);
  for (auto& [id, behavior] : _behaviors)
    behavior->onDisable();
  _entities.clear();
}

void Scene::onUpdate() {
  _frameIsValid = true;
  
  for (auto& [id, behavior] : _behaviors) {
    behavior->onUpdate();
    if (!_frameIsValid) // something is requesting to stop the frame
      break;
  }

  _frameIsValid = false;
}

void Scene::onRender() {
  for (auto& [id, behavior] : _behaviors) {
    behavior->onLateUpdate();
    if (!_frameIsValid) // something is requesting to stop the frame
      break;
  }
}

bool Scene::registerBehavior(Behavior* behavior) {
  if (behavior == nullptr) {
    if constexpr (AMSExceptions)
      throw NullPointerException("Behavior is null");
    return false;
  }
  if (!behavior->isEnabled())
    return false;
  auto eid = behavior->getEntity()->getId();
  auto bid = behavior->getId();
  if (_behaviors.find(bid) != _behaviors.end())
    return false;
  _behaviors[bid] = behavior;
  auto behaviors = std::vector<Behavior*>();
  behaviors.push_back(behavior);
  behavior->onEnable();
  behavior->onStart();
  return true;
}

bool Scene::unregisterBehavior(Behavior* behavior) {
  if constexpr (AMSExceptions)
    if (behavior == nullptr)
      throw NullPointerException("Behavior is null");
  auto bid = behavior->getId();
  if (_behaviors.find(bid) == _behaviors.end())
    return false;
  behavior->onDisable();
  _behaviors.erase(bid);
  return true;
}

bool Scene::registerCamera(Camera* camera) {
  if constexpr(AMSExceptions) {
    if (camera == nullptr)
      throw NullPointerException("Camera is null");
  }
  auto* entity = camera->getEntity();
  if (_entities.find(entity->id) == _entities.end()) {
    if constexpr (AMSExceptions)
      throw std::runtime_error("Camera is not attached to a valid entity");
    return false;
  }
  EntityCam cam {entity, entity->getTransform(), camera};
  return _cameras.try_emplace(entity->getId(), cam).second;
}

bool Scene::unregisterCamera(Camera* camera) {
  if constexpr(AMSExceptions) {
    if (camera == nullptr)
      throw NullPointerException("Camera is null");
  }
  return _cameras.erase(camera->getEntity()->getId()) > 0;
}

Application* Scene::getApplication() const {
  return _application;
}

std::vector<Scene::EntityCam> Scene::getCameras() const {
  auto cameras = std::vector<EntityCam>();
  for (auto& [id, cam] : _cameras)
    cameras.push_back(cam);
  return cameras;
}

std::vector<Behavior*> Scene::getBehaviors() const {
  auto behaviors = std::vector<Behavior*>();
  for (auto& [id, behavior] : _behaviors)
    behaviors.push_back(behavior);
  return behaviors;
}

std::vector<Entity*> Scene::getEntities() const {
  auto entities = std::vector<Entity*>();
  for (auto& [id, entity] : _entities)
    entities.push_back(entity.get());
  return entities;
}

} // ams
