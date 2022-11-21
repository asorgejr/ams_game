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

#include "ams/game/Mesh.hpp"
#include "ams/config.hpp"
#include "ams/game/Util.hpp"
#include "ams/game/MeshLoaders/AMSMeshLoader.hpp"
#else
import ams.game.Mesh;
import ams.config;
import ams.game.Util;
import ams.game.MeshLoaders.AMSMeshLoader;
#endif

#include <iostream> // TODO: see if module can be used instead
#include <fstream> // TODO: see if module can be used instead
#include <sstream>

namespace ams {

Mesh::Mesh(const vertices_t& vertices, const normals_t& normals, const tangents_t& tangents,
           const uvs_t& uv, const uvs_t& uv2, const uvs_t& uv3, const uvs_t& uv4,
           const colors_t& colors, const faces_t& faces, const submeshes_t& submeshes)
  : vertices(vertices), normals(normals), tangents(tangents), uv(uv),
    uv2(uv2), uv3(uv3), uv4(uv4), colors(colors), faces(faces), submeshes(submeshes) {}

#pragma region GetterSetters

const Mesh::vertices_t& Mesh::getVertices() const {
  return vertices;
}

void Mesh::setVertices(const vertices_t& vertices) {
  this->vertices = vertices;
}

const Mesh::normals_t& Mesh::getNormals() const {
  return normals;
}

void Mesh::setNormals(const normals_t& normals) {
  this->normals = normals;
}

const Mesh::tangents_t& Mesh::getTangents() const {
  return tangents;
}

void Mesh::setTangents(const tangents_t& tangents) {
  this->tangents = tangents;
}

const Mesh::uvs_t& Mesh::getUV() const {
  return uv;
}

void Mesh::setUV(const uvs_t& uv) {
  this->uv = uv;
}

const Mesh::uvs_t& Mesh::getUV2() const {
  return uv2;
}

void Mesh::setUV2(const uvs_t& uv2) {
  this->uv2 = uv2;
}

const Mesh::uvs_t& Mesh::getUV3() const {
  return uv3;
}

void Mesh::setUV3(const uvs_t& uv3) {
  this->uv3 = uv3;
}

const Mesh::uvs_t& Mesh::getUV4() const {
  return uv4;
}

void Mesh::setUV4(const uvs_t& uv4) {
  this->uv4 = uv4;
}

const Mesh::colors_t& Mesh::getColors() const {
  return colors;
}

void Mesh::setColors(const colors_t& colors) {
  this->colors = colors;
}

const Mesh::faces_t& Mesh::getFaces() const {
  return faces;
}

void Mesh::setFaces(const faces_t& faces) {
  this->faces = faces;
}

const Mesh::submeshes_t& Mesh::getSubmeshes() const {
  return submeshes;
}

void Mesh::setSubmeshes(const submeshes_t& submeshes) {
  this->submeshes = submeshes;
}

#pragma endregion GetterSetters

#pragma region Getters

Mesh::index_t Mesh::getVertexCount() const {
  return vertices.size();
}

Mesh::index_t Mesh::getNormalCount() const {
  return normals.size();
}

Mesh::index_t Mesh::getTangentCount() const {
  return tangents.size();
}

Mesh::index_t Mesh::getUVCount() const {
  return uv.size();
}

Mesh::index_t Mesh::getUV2Count() const {
  return uv2.size();
}

Mesh::index_t Mesh::getUV3Count() const {
  return uv3.size();
}

Mesh::index_t Mesh::getUV4Count() const {
  return uv4.size();
}

Mesh::index_t Mesh::getColorCount() const {
  return colors.size();
}

Mesh::index_t Mesh::getFaceCount() const {
  return faces.size();
}

Mesh::index_t Mesh::getSubmeshCount() const {
  return submeshes.size();
}

#pragma endregion Getters

Mesh Mesh::triangulate(const Mesh& mesh) {
  // TODO: implement
  return Mesh();
}

Mesh Mesh::fromFile(const std::filesystem::path& path) {
  // extension without dot
  auto ext = path.extension().string().substr(1);
  if (!meshLoaders.contains(ext)) {
    if (ext == "ams") // loading of ams files is always supported
      Mesh::registerMeshLoader<AMSMeshLoader>();
    else
      return throwOrDefault<std::runtime_error, Mesh>("No mesh loader for extension " + ext);
  }
  return meshLoaders[ext]->load(path);
}

void Mesh::saveToFile(const Mesh& mesh, const std::filesystem::path& path, bool binary) {
  // write to file
  std::ofstream file(path, std::ios::out | std::ios::binary);
  if (!file.is_open()) {
    // try to create file
    file.open(path, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
      return throwOrDefault<std::runtime_error>("Could not open file " + path.string());
    }
  }
  
  // write header
  file << ams_file_header << std::endl;
  file << "version " << ams_file_version << std::endl;
  file << (binary ? "binary" : "ascii") << std::endl;
  file << "vertex_count "   << mesh.getVertexCount() << std::endl;
  file << "normal_count "   << mesh.getNormalCount() << std::endl;
  file << "tangent_count "  << mesh.getTangentCount() << std::endl;
  file << "uv_count "       << mesh.getUVCount() << std::endl;
  file << "uv2_count "      << mesh.getUV2Count() << std::endl;
  file << "uv3_count "      << mesh.getUV3Count() << std::endl;
  file << "uv4_count "      << mesh.getUV4Count() << std::endl;
  file << "color_count "    << mesh.getColorCount() << std::endl;
  file << "face_count "     << mesh.getFaceCount() << std::endl;
  file << "submesh_count "  << mesh.getSubmeshCount() << std::endl;
  file << std::endl;
  
  // write vertices
  if (mesh.getVertexCount() > 0) {
    file << "vertices" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getVertices().data()),
                 mesh.getVertexCount() * sizeof(vertex_elem_t));
      file << std::endl;
    } else {
      for (const auto& v : mesh.getVertices()) {
        file << v.x << " " << v.y << " " << v.z << std::endl;
      }
    }
    
  }
  
  // write normals
  if (mesh.getNormalCount() > 0) {
    file << "normals" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getNormals().data()),
                 mesh.getNormalCount() * sizeof(normal_elem_t));
      file << std::endl;
    } else {
      for (const auto& n : mesh.getNormals()) {
        file << n.x << " " << n.y << " " << n.z << std::endl;
      }
    }
  }
  
  // write tangents
  if (mesh.getTangentCount() > 0) {
    file << "tangents" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getTangents().data()),
                 mesh.getTangentCount() * sizeof(tangent_elem_t));
      file << std::endl;
    } else {
      for (const auto& t : mesh.getTangents()) {
        file << t.x << " " << t.y << " " << t.z << std::endl;
      }
    }
  }
  
  // write uv
  if (mesh.getUVCount() > 0) {
    file << "uv" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getUV().data()),
                 mesh.getUVCount() * sizeof(uv_elem_t));
      file << std::endl;
    } else {
      for (const auto& uv : mesh.getUV()) {
        file << uv.x << " " << uv.y << std::endl;
      }
    }
  }
  
  // write uv2
  if (mesh.getUV2Count() > 0) {
    file << "uv2" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getUV2().data()),
                 mesh.getUV2Count() * sizeof(uv_elem_t));
      file << std::endl;
    } else {
      for (const auto& uv : mesh.getUV2()) {
        file << uv.x << " " << uv.y << std::endl;
      }
    }
  }
  
  // write uv3
  if (mesh.getUV3Count() > 0) {
    file << "uv3" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getUV3().data()),
                 mesh.getUV3Count() * sizeof(uv_elem_t));
      file << std::endl;
    } else {
      for (const auto& uv : mesh.getUV3()) {
        file << uv.x << " " << uv.y << std::endl;
      }
    }
  }
  
  // write uv4
  if (mesh.getUV4Count() > 0) {
    file << "uv4" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getUV4().data()),
                 mesh.getUV4Count() * sizeof(uv_elem_t));
      file << std::endl;
    } else {
      for (const auto& uv : mesh.getUV4()) {
        file << uv.x << " " << uv.y << std::endl;
      }
    }
  }
  
  // write colors
  if (mesh.getColorCount() > 0) {
    file << "colors" << std::endl;
    if (binary) {
      file.write(reinterpret_cast<const char*>(mesh.getColors().data()),
                 mesh.getColorCount() * sizeof(color_elem_t));
      file << std::endl;
    } else {
      for (const auto& c : mesh.getColors()) {
        file << c.x << " " << c.y << " " << c.z << " " << c.w << std::endl;
      }
    }
  }
  
  // write faces
  if (mesh.getFaceCount() > 0) {
    file << "faces" << std::endl;
    for (const auto& f : mesh.getFaces()) {
      Mesh::index_t fsize = f.size();
      if (binary)
        file.write(reinterpret_cast<const char*>(&fsize), sizeof(fsize));
      else
        file << fsize << "  ";
      if (binary) {
        for (Mesh::index_t i : f) {
          file.write(reinterpret_cast<const char*>(&i), sizeof(i));
        }
        file << std::endl;
      } else {
        for (Mesh::index_t i : f) {
          file << i << " ";
        }
        file << std::endl;
      }
    }
  }
  
  // write submeshes
  if (mesh.getSubmeshCount() > 0) {
    file << "submeshes" << std::endl;
    for (const auto& s : mesh.getSubmeshes()) {
      Mesh::index_t ssize = s.size();
      if (binary)
        file.write(reinterpret_cast<const char*>(&ssize), sizeof(ssize));
      else
        file << ssize << "  ";
      if (binary) {
        for (Mesh::index_t i : s) {
          file.write(reinterpret_cast<const char*>(&i), sizeof(i));
        }
        file << std::endl;
      } else {
        for (Mesh::index_t i : s) {
          file << i << " ";
        }
        file << std::endl;
      }
    }
  }
}


Mesh::normals_t Mesh::generateNormals(Mesh::vertices_t vts, Mesh::faces_t faces) {
  normals_t normals;
  normals.resize(vts.size());
  for (auto& n : normals) {
    n = normal_elem_t(0.0f);
  }
  for (const auto& f : faces) {
    if (f.size() < 3) continue;
    normal_elem_t n = normalize(cross(vts[f[1]] - vts[f[0]], vts[f[2]] - vts[f[0]]));
    for (auto i : f) {
      normals[i] = n;
    }
  }
  return normals;
}

} // ams