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

/*[export module ams.game.Scene]*/
/*[exclude begin]*/
#pragma once
#include "config.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
/*[exclude end]*/
#include <map>
/*[import <chrono>]*/
/*[import ams.game.config]*/
/*[import ams.game.Object]*/
/*[import ams.game.Camera]*/
/*[import ams.game.Entity]*/

/*[export]*/ namespace ams {

class Application;
class Transform;
class Behavior;

/**
 * @brief A Scene is a collection of Entities.
 * @details A Scene is a collection of Entities. It is the main container for all instantiated Entities in a game.
 * Its lifecycle is managed by the Application class.
 */
class AMS_GAME_EXPORT Scene : public Object {
private:
  struct EntityCam {
    Entity* entity;
    Transform* transform;
    Camera* camera;
  };
  
  Application* _application;
  std::map<uuid_t, std::unique_ptr<Entity>> _entities{};
  std::map<uuid_t, Behavior*> _behaviors{};
  std::map<uuid_t, EntityCam> _cameras{};
  
  /**
   * if this becomes false in the middle of a tick,
   * something has requested that the scene be destroyed. Break out of the tick loop.
   */
  std::atomic_bool _frameIsValid{true};
  
protected:
  const std::chrono::time_point<clk_t> startTime = clk_t::now();

public:
  Scene(Application* app, const std::string& name);

  virtual ~Scene() = default;

  /**
   * @brief Creates a Entity in the Scene.
   */
  Entity* createEntity();
  
  /**
   * @brief Creates a Entity in the Scene.
   * @param name The name of the Entity.
   */
  Entity* createEntity(const std::string& name);
  
  /**
   * @brief Creates a Entity in the Scene.
   * @param name The name of the Entity.
   * @param parent The parent Transform of the Entity.
   */
  Entity* createEntity(const std::string& name, Transform* parent);
  
  /**
   * @brief Destroys a Entity in the Scene. The same as Entity::destroy().
   * @param entity The Entity to destroy.
   * @return true if the Entity was destroyed, false otherwise.
   */
  bool destroyEntity(Entity* entity);
  
  [[nodiscard]] Application* getApplication() const;
  
protected:
  virtual void onEnter();

  virtual void onExit();

  /**
 * @brief Gets all cameras in the Scene. This method creates a new vector each time it is called. Use sparingly.
 */
  [[nodiscard]] std::vector<EntityCam> getCameras() const;

  /**
   * Gets all behaviors in the Scene. This method creates a new vector each time it is called. Use sparingly.
   */
  [[nodiscard]] std::vector<Behavior*> getBehaviors() const;

  /**
   * @brief Gets all Entities in the Scene. This method creates a new vector each time it is called. Use sparingly.
   */
  [[nodiscard]] std::vector<Entity*> getEntities() const;
  
private:
  void onUpdate();
  
  void onRender();
  
  [[maybe_unused]] bool registerBehavior(Behavior* behavior);
  
  [[maybe_unused]] bool unregisterBehavior(Behavior* behavior);
  
  /**
   * @brief Registers a camera with the Scene.
   * @param entity - The Entity that owns the camera.
   * @return true if successful, false if Entity was already registered or if Entity does not have a camera.
   */
  [[maybe_unused]] bool registerCamera(Camera* camera);

  /**
   * @brief Unregisters a camera from the Scene.
   * @param entity - The Entity that owns the camera.
   * @return true if successful, false if Entity was not registered.
   */
  [[maybe_unused]] bool unregisterCamera(Camera* camera);

public:
  friend class Application;
  friend class Camera;
  friend class Entity;
};

} // ams
