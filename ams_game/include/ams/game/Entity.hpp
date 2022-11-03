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
/*[module]*/

/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/

/*[export module ams.game.Entity]*/
/*[exclude begin]*/
#pragma once
#include "internal/CallbackList.hpp"
#include "Object.hpp"
#include "Transform.hpp"
#include "Behavior.hpp"
/*[exclude end]*/
/*[import ams.game.CallbackList]*/
/*[import ams.Object]*/
/*[import ams.Transform]*/
/*[import ams.Behavior]*/


/*[export]*/ namespace ams {

class Component;
class Scene;
class Behavior;

/* TComponent is a type which inherits from Component */
template<typename T>
concept TComponent = std::is_base_of_v<Component, T>;

/**
 * @brief An Entity is a simple container for Components.
 * @details An Entity is composed of a ams::Transform and a list of ams::Components. Entities are the basic
 * building blocks of a ams::Scene and their lifecycle is managed by the scene. Entities cannot be directly
 * constructed and are instead created by the Scene::createEntity() method.
 */
class AMS_GAME_EXPORT Entity final : public Object {
private:
  Scene* _scene;
  std::vector<std::unique_ptr<Component>> _components{};
  Transform* _transform = nullptr;

  internal::CallbackList<Behavior*> _behaviors;

  /** private constructor */
  explicit Entity(Scene* scene);

  /** private constructor */
  Entity(Scene* scene, const std::string& name) : Entity(scene) {
    this->name = name;
  }
  
  /** private constructor */
  Entity(Scene* scene, const std::string& name, Transform* parent) : Entity(scene, name) {
    _transform->setParent(parent);
  }

public:
  Entity() = delete;
  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;
  
public:
  /**
   * @brief Adds a Component to the Entity.
   * @tparam TComp - The type of Component to add.
   * @return A pointer to the newly created Component.
   */
  template<TComponent TComp>
  TComp* addComponent() {
    auto comp = std::make_unique<TComp>(this);
    auto ptr = comp.get();
    _components.emplace_back(std::move(comp));
    auto pBehavior = dynamic_cast<Behavior*>(ptr);
    if (pBehavior != nullptr) {
      _behaviors.add(pBehavior);
    }
    return ptr;
  }
  
  /**
   * @brief Adds multiple Components to the Entity.
   * @tparam TComps - The types of Components to add.
   * @return A tuple of pointers to the newly created Components.
   */
  template<TComponent... TComps>
  [[maybe_unused]] std::tuple<TComps*...> addComponents() {
    (_components.emplace_back(std::make_unique<TComps>(this)), ...);
    for (auto& comp : _components) {
      if (auto* behavior = dynamic_cast<Behavior*>(comp.get()); behavior != nullptr)
        _behaviors.add(behavior);
    }
    return std::make_tuple(static_cast<TComps*>(_components.back().get())...);
  }
  
  /**
   * @brief Get the component of type TComp.
   * @tparam TComp - The type of component to get.
   * @return A pointer to the component of type TComp, or nullptr if the component does not exist.
   */
  template<TComponent TComp>
  TComp* getComponent() {
    for (auto& component : _components) {
      auto comp = dynamic_cast<TComp*>(component.get());
      if (comp != nullptr) {
        return comp;
      }
    }
    if constexpr (AMSExceptions) {
      throw std::runtime_error("Component not found");
    }
    return nullptr;
  }
  
  [[nodiscard]] Transform* getTransform() const {
    return _transform;
  }
  
  void destroy();
  
  [[nodiscard]] Scene* getScene() const;
  
  friend class Scene; // Constructs Entities
};

} // ams
