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

/*[exclude begin]*/
#pragma once
/*[exclude end]*/
/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[export module ams.game.MeshComponent]*/
/*[exclude begin]*/
#include "ams/game/internal/ActiveComponent.hpp"
#include "ams/game/Mesh.hpp"
/*[exclude end]*/
/*[import ams.game.internal.ActiveComponent]*/
/*[import ams.game.Mesh]*/

/*[export]*/ namespace ams {

class AMS_GAME_EXPORT MeshComponent : public internal::ActiveComponent {
private:
  const Mesh* _sharedMesh;
  Mesh* _mesh = nullptr; // If this is not null, then the mesh is owned by this component
  
public:
  explicit MeshComponent(Entity* entity, Mesh* mesh=nullptr);
  
  ~MeshComponent() override;

  const Mesh* getMesh() const;
  
  void setMesh(Mesh* mesh);
};

} // ams
