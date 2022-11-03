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
module;

#include "ams_game_export.hpp"

import <atomic>;
import <vector>;
import <chrono>;
import ams.game.config;
import ams.game.Object;

export module ams.game.Application;

export namespace ams {

class Scene;

/**
 * @brief An Application is a singleton that manages the game loop and the game window.
 * @details The Application class is a singleton that manages the game loop and the game window. It is designed to be
 * extended by the user to create a custom game loop. The Application class manages all of the scenes in the game and
 * provides a way to switch between them. If a scene is not provided, the Application will create a default scene.
 */
class AMS_GAME_EXPORT Application : public Object {
private:
  inline static Application* _instance;
  Scene* _currentScene;
protected:
  /** Determines if the game loop should continue. */
  std::atomic_bool running = false;
  /** Time when the game loop started. */
  std::chrono::time_point<clk_t> startTime = clk_t::now();
  /** Time when the last frame started. */
  std::chrono::time_point<clk_t> lastFrameTime = startTime;
  /** The goal frame time of the game. Defaults to 1us/60 */
  time_unit targetFrameTime = time_unit_1s / 60;
  /** The fixed frame time of the game. Defaults to 1us/60 */
  time_unit fixedFrameTime = time_unit_1s / 60;
  /** Frame synchronization time. When this value is 0us (the default value), the game will run as fast as possible. */
  time_unit vsyncTime = time_unit_1s * 0;
  
  /** Currently loaded scenes. */
  std::vector<std::unique_ptr<Scene>> scenes;
  
public:
  explicit Application(const std::string& name = "Application");
  
  virtual ~Application();
  
  /**
   * @brief Runs the game loop.
   * @details Runs the game loop. This method is called by the user to start the game loop.
   */
  void run();

  /**
   * @brief Stops the game loop.
   */
  void stop();
  
  /**
   * @brief Stops any threads and closes the game window.
   */
  virtual void exit();
  
  Scene* getCurrentScene() const;

  /**
   * @brief Tries to get a scene by name.
   * @param name - The name of the scene to get.
   * @param scene - A pointer to the scene if it was found.
   * @return True if the scene was found, false otherwise.
   */
  bool tryGetScene(const std::string& name, Scene*& scene) const;
  
  /**
   * @brief Gets a scene by name.
   * @param name - The name of the scene to get.
   * @return A pointer to the scene if it was found.
   * @throws std::runtime_error if the scene was not found.
   */
  Scene* getScene(const std::string& name) const;
  
  [[maybe_unused]] Scene* setCurrentScene(const std::string& name);
  
  [[maybe_unused]] Scene* createScene(const std::string& name);
  
  /**
   * @brief Gets the time since the game loop started.
   */
  time_unit getElapsedTime() const;
  
  /**
   * @brief Gets the time since the last frame started.
   */
  time_unit getDeltaTime() const;
  
  /**
   * @brief Gets the singleton instance of the Application.
   */
  static Application* getInstance();
  
  /**
   * @brief Sets the target frame rate of the game. The default is 60.0.
   * @param goalFPS - The target frame rate of the game.
   * @details Values less than 1.0 fps will be ignored. If a frame takes less time than the target frame rate,
   * the event loop will sleep for the remaining time after finishing the frame.
   */
  void setTargetFrameRate(float goalFPS);
  
  /**
   * @brief Gets the target frame rate of the game.
   */
  float getTargetFrameRate() const;
  
  /**
   * @brief Sets the fixed frame rate of the game. The default is 60.0.
   * @param fixedFPS - The fixed frame rate of the game.
   * @details Values less than 1.0 fps will be ignored. If a frame takes less time than the fixed frame rate,
   * the event loop will sleep for the remaining time after finishing the frame.
   */
  void setFixedFrameRate(float fixedFPS);
  
  /**
   * @brief Gets the fixed frame rate of the game.
   */
  float getFixedFrameRate() const;
  
  /**
   * @brief Sets the frame synchronization time of the game. The default is 0 (no synchronization).
   * @param vsyncFPS - The frame synchronization time of the game.
   * @details Values less than 1.0 fps will be ignored. If a frame takes less time than the frame synchronization time,
   * the event loop will sleep for the remaining time after finishing the frame.
   */
  void setVsyncTime(float vsyncFPS);
  
  /**
   * @brief Gets the frame synchronization time of the game.
   */
  float getVsyncTime() const;
  
  /**
   * @brief Gets the fixed frame rate as a time duration.
   */
  time_unit getFixedFrameTime() const;
  
protected:
  virtual void onRunStart() {}
  
  virtual void onRunEnd() {}
  
  virtual void onFrameStart() {}
  
  virtual void onFrameEnd() {}
  
  virtual void onFixedFrameStart() {}
  
  virtual void onFixedFrameEnd() {}
  
private:
  Scene* getDefaultScene();

  friend class Scene;
};

} // ams
