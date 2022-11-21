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
#include "ams/game/Components/MeshComponent.hpp"
#include "ams/game/internal/Meshes.hpp"
#else
import ams.game.Components.MeshComponent;
import ams.game.internal.Meshes;
#endif


namespace ams {
MeshComponent::MeshComponent(Entity* entity, Mesh* mesh)
  : ActiveComponent(entity),
    _sharedMesh(mesh)
{
  if (!_sharedMesh) {
    _sharedMesh = &internal::Meshes::BoxMesh; // todo: shared mesh || instanced mesh
  }
}

MeshComponent::~MeshComponent() {
  if (_mesh)
    delete _mesh;
}

const Mesh* MeshComponent::getMesh() const {
  return _mesh ? _mesh : _sharedMesh;
}

void MeshComponent::setMesh(Mesh* mesh) {
  _sharedMesh = mesh;
}

} // ams