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

export module ams.internal.ActiveComponent;
import ams.game.Component;

export namespace ams::internal {

/**
 * @brief This class is used internally and is not meant to be derived from. Derive from Behavior instead.
 * @details This class extends the Component class and adds the ability to enable and disable the component and has
 * events for when the component is enabled or disabled.
 */
class AMS_GAME_EXPORT ActiveComponent : public Component {
protected:
  bool enabled = true;
public:
  ActiveComponent(Entity* entity) : Component(entity) {}

  /**
   * @brief onEnable is called when the ams::Entity is enabled.
   */
  virtual void onEnable() {}

  /**
   * @brief onDisable is called when the ams::Entity is disabled.
   */
  virtual void onDisable() {}

  /**
   * @brief isEnabled returns true if the ams::Behavior is enabled.
   * @return true if the ams::Behavior is enabled.
   */
  [[nodiscard]] bool isEnabled() const { return enabled; }

  /**
   * @brief setEnabled sets the enabled state of the ams::Behavior.
   * @param enabled the enabled state of the ams::Behavior.
   */
  void setEnabled(bool enabled) { this->enabled = enabled; }
};

} // ams
