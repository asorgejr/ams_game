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

/**
 * This macro function is used to define a new Behavior class and should always be included at the beginning of the
 * class code block. It includes some boilerplate code to make it easier to define a new Behavior class.
 */
#define AMSBehavior(name) \
public: \
  using Behavior::Behavior; \
private:


/*[export module ams.game.Behavior]*/
/*[exclude begin]*/
#pragma once
#include "internal/ActiveComponent.hpp"
/*[exclude end]*/
/*[import ams.game.ActiveComponent]*/
/*[import ams.game.IBehavior]*/

/*[export]*/ namespace ams {

/**
 * @brief A ams::Behavior is a ams::Component with event methods which can be overridden to add behavioral
 * functionality to a ams::Entity.
 */
class AMS_GAME_EXPORT Behavior : public internal::ActiveComponent {
public:
  explicit Behavior(Entity* entity);

  ~Behavior() override = default;

  /**
* @brief onStart is called when the ams::Entity is created.
*/
  virtual void onStart() {}

  /**
   * @brief onUpdate is called every frame.
   */
  virtual void onUpdate() {}

  /**
   * @brief onFixedUpdate is called every fixed frame.
   */
  virtual void onFixedUpdate() {}

  /**
   * @brief onLateUpdate is called every late frame.
   */
  virtual void onLateUpdate() {}

  /**
 * @brief onDestroy is called when the ams::Entity is destroyed.
 */
  virtual void onDestroy() {}

  friend class Entity;
};

} // ams
