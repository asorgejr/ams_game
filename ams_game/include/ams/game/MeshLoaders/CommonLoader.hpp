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

/*[export module ams.game.MeshLoaders.CommonLoader]*/
/*[exclude begin]*/
#pragma once
#include "ams/game/Mesh.hpp"
/*[exclude end]*/
/*[import ams.game.Mesh]*/

/*[export]*/ namespace ams {

/**
 * @brief CommonLoader supports loading static meshes from any filetype supported by Assimp.
 * @details Supported filetypes are:
 * Autodesk ( .fbx ),
 * Collada ( .dae ),
 * glTF ( .gltf, .glb ),
 * Blender 3D ( .blend ),
 * 3ds Max 3DS ( .3ds ),
 * 3ds Max ASE ( .ase ),
 * Wavefront Object ( .obj ),
 * Industry Foundation Classes (IFC/Step) ( .ifc ),
 * XGL ( .xgl,.zgl ),
 * Stanford Polygon Library ( .ply ),
 * LightWave ( .lwo ),
 * LightWave Scene ( .lws ),
 * Modo ( .lxo ),
 * Stereolithography ( .stl ),
 * DirectX X ( .x ),
 * AC3D ( .ac ),
 * Milkshape 3D ( .ms3d ),
 * TrueSpace ( .cob,.scn ),
 */
class CommonLoader : public IMeshLoader {
public:
  CommonLoader() = default;
  ~CommonLoader() = default;
  Mesh load(const std::filesystem::path& path) const override;
};

} // ams
