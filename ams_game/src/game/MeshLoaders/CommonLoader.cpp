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
#include "ams/game/MeshLoaders/CommonLoader.hpp"
#else
import ams.game.MeshLoaders.CommonLoader;
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ams {

Mesh CommonLoader::load(const std::filesystem::path& path) const {
  // import OBJ file using assimp
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);
  // check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    if constexpr (AMSExceptions)
      throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
    else
      return Mesh();
  }
  // get the mesh(s) from the scene
  Mesh::vertices_t vertices;    // aka vector<Vec3<decimal_t>>
  Mesh::normals_t normals;      // aka vector<Vec3<decimal_t>>
  Mesh::tangents_t tangents;    // aka vector<Vec4<decimal_t>>
  Mesh::uvs_t uv;                // aka vector<Vec2<decimal_t>>
  Mesh::uvs_t uv2;               // aka vector<Vec2<decimal_t>>
  Mesh::uvs_t uv3;               // aka vector<Vec2<decimal_t>>
  Mesh::uvs_t uv4;               // aka vector<Vec2<decimal_t>>
  Mesh::colors_t colors;        // aka vector<Vec4<decimal_t>>
  Mesh::faces_t faces;          // aka vector<vector<uint32_t>>
  Mesh::submeshes_t submeshes;  // aka vector<vector<uint32_t>>

  
  for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[i];
    // start with required data
    if (!mesh->HasPositions())
      throw std::runtime_error("Mesh has no vertices");
    if (!mesh->HasFaces())
      throw std::runtime_error("Mesh has no faces");
    // get vertices
    for (uint32_t j = 0; j < mesh->mNumVertices; j++) {
      vertices.push_back(mesh->mVertices[j]);
    }
    // faces
    auto submeshElem = std::vector<uint32_t>();
    for (uint32_t k = 0; k < mesh->mNumFaces; k++) {
      aiFace face = mesh->mFaces[k];
      auto faceElem = std::vector<uint32_t>();
      for (uint32_t l = 0; l < face.mNumIndices; l++) {
        faceElem.push_back(face.mIndices[l]);
      }
      faces.push_back(faceElem);
      submeshElem.push_back(faces.size() - 1);
    }
    submeshes.push_back(submeshElem);
    
    // normals (generate if not present)
    if (mesh->HasNormals()) {
      for (uint32_t j = 0; j < mesh->mNumVertices; j++) {
        normals.push_back(mesh->mNormals[j]);
      }
    } else {
      normals = Mesh::generateNormals(vertices, faces);
    }
    
    // optional data
    for (uint32_t j = 0; j < mesh->mNumVertices; j++) {
      if (mesh->mTangents) {
        tangents.push_back(mesh->mTangents[j]);
      }
      if (mesh->mTextureCoords[0]) {
        uv.push_back(mesh->mTextureCoords[0][j]);
      }
      if (mesh->mTextureCoords[1]) {
        uv2.push_back(mesh->mTextureCoords[1][j]);
      }
      if (mesh->mTextureCoords[2]) {
        uv3.push_back(mesh->mTextureCoords[2][j]);
      }
      if (mesh->mTextureCoords[3]) {
        uv4.push_back(mesh->mTextureCoords[3][j]);
      }
      if (mesh->mColors[0]) {
        auto color = mesh->mColors[0][j];
        colors.push_back({color.r, color.g, color.b, color.a});
      }
    }
  }
  


  return Mesh(vertices, normals, tangents,
              uv, uv2, uv3, uv4,
              colors, faces, submeshes);
}
} // ams