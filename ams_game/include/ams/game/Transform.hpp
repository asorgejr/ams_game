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
/*[export module ams.game.Transform]*/
/*[exclude begin]*/
#pragma once
#include "ams_game_export.hpp"
#include <ams/spatial.hpp>
#include "Component.hpp"
/*[exclude end]*/
/*[import ams.internal.config]*/
/*[import ams.spatial]*/
/*[import ams.game.Component]*/

class Entity;

/*[export]*/ namespace ams {

class AMS_GAME_EXPORT Transform final : public Component {
private:
  Vec3<decimal_t> m_position = Vec3(0.0, 0.0, 0.0);
  Quaternion m_rotation = Quaternion::identity();
  Vec3<decimal_t> m_scale = Vec3(1.0, 1.0, 1.0);
  Matrix4 m_modelMatrix = Matrix4::identity();
  Transform* m_parent = nullptr;
  std::vector<Transform*> m_children;
public:
  explicit Transform(Entity* entity) : Component(entity) {}

  constexpr void setPosition(decimal_t x, decimal_t y, decimal_t z) { m_position.x = x; m_position.y = y; m_position.z = z; }

  constexpr void setPosition(const Vec3<decimal_t>& position) { m_position = position; }

  constexpr void setRotation(decimal_t x, decimal_t y, decimal_t z) { m_rotation = Vec3<decimal_t>(x, y, z); }

  constexpr void setRotation(const Vec3<decimal_t>& rotation) { m_rotation = rotation; }

  constexpr void setScale(decimal_t x, decimal_t y, decimal_t z) { m_scale.x = x; m_scale.y = y; m_scale.z = z; }

  constexpr void setScale(const Vec3<decimal_t>& scale) { m_scale = scale; }

  constexpr void translate(const Vec3<decimal_t>& translation) { m_position += translation; }

  constexpr void translate(decimal_t x, decimal_t y, decimal_t z) { m_position.x += x; m_position.y += y; m_position.z += z; }

  /**
   * @brief rotate the transform by the given euler angles in degrees.
   * @param x - The rotation around the x axis in degrees.
   * @param y - The rotation around the y axis in degrees.
   * @param z - The rotation around the z axis in degrees.
   */
  constexpr void rotate(decimal_t x, decimal_t y, decimal_t z) { m_rotation *= Quaternion::fromEuler(radians(Vec3<decimal_t>(x, y, z))); }

  /**
   * @brief rotate the transform by the given euler angles in degrees.
   * @param rotation - The rotation around the x, y, and z axis in degrees.
   */
  constexpr void rotate(const Vec3<decimal_t>& rotation) { m_rotation *= Quaternion::fromEuler(radians(rotation)); }

  /**
   * @brief rotate the transform by the given quaternion.
   * @param rotation - The rotation quaternion.
   */
  constexpr void rotate(const Quaternion& q) { m_rotation *= q; }

  /**
   * @brief scale the transform by the given scale factors.
   * @param x - The scale factor along the x axis.
   * @param y - The scale factor along the y axis.
   * @param z - The scale factor along the z axis.
   */
  constexpr void scale(decimal_t x, decimal_t y, decimal_t z) { m_scale.x *= x; m_scale.y *= y; m_scale.z *= z; }

  /**
   * @brief scale the transform by the given vector.
   * @param scale - The scale vector.
   */
  constexpr void scale(const Vec3<decimal_t>& scale) { m_scale *= scale; }
  
  /**
   * @brief Set the parent of this transform.
   * @param parent - The parent transform.
   */
  void setParent(Transform* parent) {
    if (m_parent != nullptr) {
      m_parent->m_children.erase(
        std::remove(m_parent->m_children.begin(), m_parent->m_children.end(), this), m_parent->m_children.end());
    }
    m_parent = parent;
    if (parent != nullptr && !parent->hasChild(this)) {
      parent->m_children.push_back(this);
    }
  }

  [[nodiscard]] const Vec3<decimal_t>& getPosition() const { return m_position; }

  [[nodiscard]] const Quaternion& getRotation() const { return m_rotation; }

  [[nodiscard]] const Vec3<decimal_t>& getScale() const { return m_scale; }

  [[nodiscard]] const Matrix4& getModelMatrix() const { return m_modelMatrix; }
  
  [[nodiscard]] const Transform* getParent() const { return m_parent; }
  
  [[nodiscard]] const std::vector<Transform*>& getChildren() const { return m_children; }
  
  [[nodiscard]] bool hasChild(const Transform* child) const {
    return std::find(m_children.begin(), m_children.end(), child) != m_children.end();
  }

  void updateModelMatrix() {
    m_modelMatrix.scale(m_scale);
    m_modelMatrix.rotate(m_rotation);
    m_modelMatrix.translate(m_position);
  }
};

} // ams
