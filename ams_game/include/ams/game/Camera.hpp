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

/*[export module ams.game.Camera]*/
/*[exclude begin]*/
#pragma once
/*[exclude end]*/
/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[exclude begin]*/
#include <ams/spatial/Matrix.hpp>
#include "internal/ActiveComponent.hpp"
/*[exclude end]*/
/*[import ams.spatial.Matrix]*/
/*[import ams.game.ActiveComponent]*/

/*[export]*/ namespace ams {

class AMS_GAME_EXPORT Camera : public internal::ActiveComponent {
protected:
  Matrix4 projectionMatrix = Matrix4::identity();
  /** The camera's field of view in degrees. */
  decimal_t fov = 45.0f;
  /** 
   * The aspect ratio of the camera's view.
   * @details This is the ratio of the width of the view to the height of the view.
   */
  decimal_t aspectRatio = 1.0f;
  /** The near clipping plane of the camera. */
  decimal_t nearPlane = 0.1f;
  /** The far clipping plane of the camera. */
  decimal_t farPlane = 100.0f;
  
public:
  explicit Camera(Entity* entity);
  
  void setProjectionMatrix(const Matrix4& matrix);
  
  const Matrix4& getProjectionMatrix() const;
  
  void setFOV(decimal_t fov);
  
  decimal_t getFOV() const;
  
  void setAspectRatio(decimal_t aspectRatio);
  
  decimal_t getAspectRatio() const;
  
  void setNearPlane(decimal_t nearPlane);
  
  decimal_t getNearPlane() const;
  
  void setFarPlane(decimal_t farPlane);
  
  decimal_t getFarPlane() const;
  
};

} // ams
