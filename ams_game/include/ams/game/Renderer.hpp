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
/*[export module ams.Renderer]*/
/*[exclude begin]*/
#pragma once
#include "Object.hpp"
/*[exclude end]*/
/*[import ams.Object]*/

/*[export]*/ namespace ams {

class Application;

class Window;

class Scene;

/**
 * @brief The Renderer class is responsible for rendering the scene. 
 */
class Renderer : public Object {
private:
  Application* _application;
  Window* _window;
  Scene* _scene;
public:
  /**
   * @brief Render the scene.
   */
  void render();

private:
  friend class Application;

  friend class Window;
};

} // ams
