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
#include "ams/game/Camera.hpp"
#include "ams/game/Entity.hpp"
#include "ams/game/Scene.hpp"
#else
import ams.game.Camera;
import ams.game.Entity;
import ams.game.Scene;
#endif

namespace ams {

using namespace ams::internal;

Camera::Camera(ams::Entity* entity)
: ActiveComponent(entity)
{
  entity->getScene()->registerCamera(this);
}

void Camera::setProjectionMatrix(const Matrix4& matrix) {
  projectionMatrix = matrix;
  // extract fov, aspect ratio, near and far planes
  Matrix4::extractPerspective(projectionMatrix, fov, aspectRatio, nearPlane, farPlane);
}

const Matrix4& Camera::getProjectionMatrix() const {
  return projectionMatrix;
}

void Camera::setFOV(decimal_t f) {
  this->fov = f;
  projectionMatrix.setPerspective(fov, aspectRatio, nearPlane, farPlane);
}

decimal_t Camera::getFOV() const {
  return fov;
}

void Camera::setAspectRatio(decimal_t ar) {
  this->aspectRatio = ar;
  projectionMatrix.setPerspective(fov, aspectRatio, nearPlane, farPlane);
}

decimal_t Camera::getAspectRatio() const {
  return 0;
}

void Camera::setNearPlane(decimal_t np) {
  this->nearPlane = np;
  projectionMatrix.setPerspective(fov, aspectRatio, nearPlane, farPlane);
}

decimal_t Camera::getNearPlane() const {
  return nearPlane;
}

void Camera::setFarPlane(decimal_t fp) {
  this->farPlane = fp;
  projectionMatrix.setPerspective(fov, aspectRatio, nearPlane, farPlane);
}

decimal_t Camera::getFarPlane() const {
  return farPlane;
}

// TODO: Add a way to unregister the camera from the scene

} // ams