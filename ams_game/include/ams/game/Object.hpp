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

/*[export module ams.game.Object]*/
/*[exclude begin]*/
#pragma once
#include "ams_game_export.hpp"
#include "ams/game/Exceptions.hpp"
/*[exclude end]*/
#include <string>
#include <random>
/*[export import ams.game.Exceptions]*/


/*[export]*/ namespace ams {

using uuid_t = uint64_t;

/**
 * @brief The Object class is the base class for all objects in the game engine.
 * @details The Object class is the base class for all objects in the game engine.
 * It stores the a name and a unique identifier.
 */
class AMS_GAME_EXPORT Object {
protected:
  uuid_t id;
  std::string name;
public:
  Object() : id(dis(gen)) {
    name = "Object_" + std::to_string(id);
  }
  explicit Object(const std::string& name) : id(dis(gen)), name(name) {}

  [[nodiscard]] uuid_t getId() { return id; }
  [[nodiscard]] const std::string& getName() const { return name; }
  
private:
  inline static std::random_device rd{};
  inline static std::mt19937 gen{rd()};
  inline static std::uniform_int_distribution<uint64_t> dis{};
};

} // ams
