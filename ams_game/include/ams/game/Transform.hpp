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
/*[export module ams.Transform]*/
/*[exclude begin]*/
#pragma once
#include <ams/spatial/Vec.hpp>
#include <ams/spatial/Matrix.hpp>
#include <ams/spatial/Quaternion.hpp>
#include "Component.hpp"
/*[exclude end]*/
/*[import ams.private.config]*/
/*[import ams.Component]*/

namespace ams {

class Transform : public Component {
public:
    Transform() = default;
    ~Transform() override = default;
    constexpr void SetPosition(const Vec3<double>& position) { m_position = position; }
    constexpr void SetRotation(const Vec3<double>& rotation) { m_rotation = rotation; }
    constexpr void SetScale(const Vec3<double>& scale) { m_scale = scale; }
    constexpr void SetPosition(float x, float y, float z) { m_position = Vec3<decimal_t>(x, y, z); }
    constexpr void SetRotation(float x, float y, float z) { m_rotation = Vec3<decimal_t>(x, y, z); }
    constexpr void SetScale(float x, float y, float z) { m_scale = Vec3<decimal_t>(x, y, z); }
    constexpr void Translate(const Vec3<double>& translation) { m_position += translation; }
    constexpr void Translate(float x, float y, float z) { m_position += Vec3<decimal_t>(x, y, z); }
    constexpr void Rotate(const Vec3<double>& rotation) { m_rotation += rotation; }
    constexpr void Rotate(float x, float y, float z) { m_rotation += Vec3<decimal_t>(x, y, z); }
    constexpr void Scale(const Vec3<double>& scale) { m_scale += scale; }
    void Scale(float x, float y, float z) { m_scale += Vec3<decimal_t>(x, y, z); }
    const Vec3<double>& GetPosition() const { return m_position; }
    const Quaternion& GetRotation() const { return m_rotation; }
    const Vec3<double>& GetScale() const { return m_scale; }
    const Matrix4& GetModelMatrix() const { return m_modelMatrix; }
    void UpdateModelMatrix() {
      translate(m_modelMatrix, m_position);
      rotate(m_modelMatrix, m_rotation);
      scale(m_modelMatrix, m_scale);
    }
private:
    Vec3<double> m_position = Vec3(0.0, 0.0, 0.0);
    Quaternion m_rotation = Quaternion::identity();
    Vec3<double> m_scale = Vec3(1.0, 1.0, 1.0);
    Matrix4 m_modelMatrix = Matrix4::identity();
};

} // ams
