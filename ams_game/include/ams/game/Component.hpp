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

/*[export module ams.game.Component]*/
/*[exclude begin]*/
#pragma once
#include "ams_game_export.hpp"
#include "Object.hpp"
/*[exclude end]*/
/*[import ams.game.Object]*/

/*[export]*/ namespace ams {

class Entity;

/**
 * @brief The Component class is the base class for all components.
 * @details Components are the building blocks of a ams::Entity. They are used to add core 
 * functionality to a ams::Entity. The lifetime of a component is tied to the lifetime of the ams::Entity
 * it is attached to. When the ams::Entity is destroyed, all of its components are destroyed.
 * Components are attached to a ams::Entity using ams::Entity::addComponent().
 * Components do not have any event handlers and as such they can not be used for behavioral scripting. For
 * scripting, use ams::Behavior.
 */
class AMS_GAME_EXPORT Component : public Object {
protected:
  Entity* entity = nullptr;
public:
    explicit Component(Entity* entity) : entity(entity) {}
    virtual ~Component() = default;
    
    Component(const Component& other) = delete;
    Component(Component&& other) noexcept = delete;
    Component& operator=(const Component& other) = delete;
    Component& operator=(Component&& other) noexcept = delete;
    
    /**
     * @brief Returns the ams::Entity this component is attached to.
     * @return The ams::Entity this component is attached to.
     */
    [[nodiscard]] Entity* getEntity() const { return entity; }
};

} // ams
