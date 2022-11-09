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
#include "ams/game/MeshLoaders/AMSMeshLoader.hpp"
#include "ams/game/Mesh.hpp"
#include "ams/config.hpp"
#include "ams/game/Util.hpp"
#else
import ams.game.MeshLoaders.AMSMeshLoader;
import ams.game.Mesh;
import ams.config;
import ams.game.Util;
#endif

#include <iostream> // TODO: see if module can be used instead
#include <fstream> // TODO: see if module can be used instead
#include <sstream>


namespace ams {

const std::string AMSMeshLoader::filetype() const {
  return "ams";
}

Mesh AMSMeshLoader::load(const std::filesystem::path& path) const {
  auto fail = [&path](const std::string& msg) {
    return throwOrDefault<std::runtime_error, Mesh>("MeshLoader::load: " + msg + " (" + path.string() + ")");
  };
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    return fail("Failed to open file: " + path.string());
  }
// read header
  std::string header;
  std::getline(file, header);
  if (header != Mesh::ams_file_header) {
    return fail("Header is not ams_mesh " + path.string());
  }
// read version
  std::string versionStr;
  std::getline(file, versionStr);
// get value after space
  std::string version = versionStr.substr(versionStr.find(" ") + 1, versionStr.length());
  if (version != Mesh::ams_file_version) {
    return fail("Version is not supported " + path.string());
  }
  try {
// ascii or binary
    std::string format;
    std::getline(file, format);
    bool binary = format == "binary";
// get vertex count
    std::string vertexCountStr;
    std::getline(file, vertexCountStr);
    Mesh::index_t vertexCount = std::stoi(vertexCountStr.substr(vertexCountStr.find(" ") + 1));
// get normal count
    std::string normalCountStr;
    std::getline(file, normalCountStr);
    Mesh::index_t normalCount = std::stoi(normalCountStr.substr(normalCountStr.find(" ") + 1));
// get tangent count
    std::string tangentCountStr;
    std::getline(file, tangentCountStr);
    Mesh::index_t tangentCount = std::stoi(tangentCountStr.substr(tangentCountStr.find(" ") + 1));
// get uv count
    std::string uvCountStr;
    std::getline(file, uvCountStr);
    Mesh::index_t uvCount = std::stoi(uvCountStr.substr(uvCountStr.find(" ") + 1));
// get uv2 count
    std::string uv2CountStr;
    std::getline(file, uv2CountStr);
    Mesh::index_t uv2Count = std::stoi(uv2CountStr.substr(uv2CountStr.find(" ") + 1));
// get uv3 count
    std::string uv3CountStr;
    std::getline(file, uv3CountStr);
    Mesh::index_t uv3Count = std::stoi(uv3CountStr.substr(uv3CountStr.find(" ") + 1));
// get uv4 count
    std::string uv4CountStr;
    std::getline(file, uv4CountStr);
    Mesh::index_t uv4Count = std::stoi(uv4CountStr.substr(uv4CountStr.find(" ") + 1));
// get color count
    std::string colorCountStr;
    std::getline(file, colorCountStr);
    Mesh::index_t colorCount = std::stoi(colorCountStr.substr(colorCountStr.find(" ") + 1));
// get face count
    std::string faceCountStr;
    std::getline(file, faceCountStr);
    Mesh::index_t faceCount = std::stoi(faceCountStr.substr(faceCountStr.find(" ") + 1));
// get submesh count
    std::string submeshCountStr;
    std::getline(file, submeshCountStr);
    Mesh::index_t submeshCount = std::stoi(submeshCountStr.substr(submeshCountStr.find(" ") + 1));
// get vertex data
    Mesh::vertices_t vertices;
    if (vertexCount > 0) {
// search for "vertices" line
      std::string line;
      while (std::getline(file, line))
        if (line == "vertices")
          break;
        else if (file.eof())
          return fail("vertex_count > 0 but vertices not found");
      vertices.resize(vertexCount);
      if (binary) {
        file.read(reinterpret_cast<char*>(vertices.data()), vertexCount * sizeof(Mesh::vertex_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < vertexCount; ++i) {
          file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
        }
      }
    }
// get normal data
    Mesh::normals_t normals;
    if (normalCount > 0) {
// search for "normals" line
      std::string line;
      while (std::getline(file, line))
        if (line == "normals")
          break;
        else if (file.eof())
          return fail("normal_count > 0 but normals not found");
      normals.resize(normalCount);
      if (binary) {
        file.read(reinterpret_cast<char*>(normals.data()), normalCount * sizeof(Mesh::normal_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < normalCount; ++i) {
          file >> normals[i].x >> normals[i].y >> normals[i].z;
        }
      }
    }
// get tangent data
    Mesh::tangents_t tangents;
    if (tangentCount > 0) {
// search for "tangents" line
      std::string line;
      while (std::getline(file, line))
        if (line == "tangents")
          break;
        else if (file.eof())
          return fail("tangent_count > 0 but tangents not found");
      tangents.resize(tangentCount);
      if (binary) {
        file.read(reinterpret_cast<char*>(tangents.data()), tangentCount * sizeof(Mesh::tangent_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < tangentCount; ++i) {
          file >> tangents[i].x >> tangents[i].y >> tangents[i].z;
        }
      }
    }
// get uv data
    Mesh::uvs_t uvs;
    if (uvCount > 0) {
// search for "uv" line
      std::string line;
      while (std::getline(file, line))
        if (line == "uv")
          break;
        else if (file.eof())
          return fail("uv_count > 0 but uv not found");
      uvs.resize(uvCount);
      if (binary) {
        file.read(reinterpret_cast<char*>(uvs.data()), uvCount * sizeof(Mesh::uv_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < uvCount; ++i) {
          file >> uvs[i].x >> uvs[i].y;
        }
      }
    }
// get uv2 data
    Mesh::uvs_t uv2s;
    if (uv2Count > 0) {
// search for "uv2" line
      std::string line;
      while (std::getline(file, line))
        if (line == "uv2")
          break;
        else if (file.eof())
          return fail("uv2_count > 0 but uv2 not found");
      uv2s.resize(uv2Count);
      if (binary) {
        file.read(reinterpret_cast<char*>(uv2s.data()), uv2Count * sizeof(Mesh::uv_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < uv2Count; ++i) {
          file >> uv2s[i].x >> uv2s[i].y;
        }
      }
    }
// get uv3 data
    Mesh::uvs_t uv3s;
    if (uv3Count > 0) {
// search for "uv3" line
      std::string line;
      while (std::getline(file, line))
        if (line == "uv3")
          break;
        else if (file.eof())
          return fail("uv3_count > 0 but uv3 not found");
      uv3s.resize(uv3Count);
      if (binary) {
        file.read(reinterpret_cast<char*>(uv3s.data()), uv3Count * sizeof(Mesh::uv_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < uv3Count; ++i) {
          file >> uv3s[i].x >> uv3s[i].y;
        }
      }
    }
// get uv4 data
    Mesh::uvs_t uv4s;
    if (uv4Count > 0) {
// search for "uv4" line
      std::string line;
      while (std::getline(file, line))
        if (line == "uv4")
          break;
        else if (file.eof())
          return fail("uv4_count > 0 but uv4 not found");
      uv4s.resize(uv4Count);
      if (binary) {
        file.read(reinterpret_cast<char*>(uv4s.data()), uv4Count * sizeof(Mesh::uv_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < uv4Count; ++i) {
          file >> uv4s[i].x >> uv4s[i].y;
        }
      }
    }
// get color data
    Mesh::colors_t colors;
    if (colorCount > 0) {
// search for "colors" line
      std::string line;
      while (std::getline(file, line))
        if (line == "colors")
          break;
        else if (file.eof())
          return fail("color_count > 0 but colors not found");
      colors.resize(colorCount);
      if (binary) {
        file.read(reinterpret_cast<char*>(colors.data()), colorCount * sizeof(Mesh::color_elem_t));
      } else {
        for (Mesh::index_t i = 0; i < colorCount; ++i) {
          file >> colors[i].x >> colors[i].y >> colors[i].z >> colors[i].w;
        }
      }
    }
// get face data
    Mesh::faces_t faces;
    if (faceCount > 0) {
// search for "faces" line
      std::string line;
      while (std::getline(file, line))
        if (line == "faces")
          break;
        else if (file.eof())
          return fail("face_count > 0 but faces not found");
      faces.resize(faceCount);
      if (binary) {
// read data
        for (Mesh::index_t i = 0; i < faceCount; ++i) {
// get size hint
          Mesh::index_t face_size = 0;
          file.read(reinterpret_cast<char*>(&face_size), sizeof(face_size));
          faces[i].resize(face_size);
          for (Mesh::index_t j = 0; j < face_size; ++j) {
            file.read(reinterpret_cast<char*>(&faces[i][j]), sizeof(Mesh::index_t));
          }
// next line
          file.get();
        }
      } else {
        for (Mesh::index_t i = 0; i < faceCount; ++i) {
// size hint
          Mesh::index_t face_size = 0;
          file >> face_size;
          if (face_size <= 0) {
            return fail("invalid face size");
          }
          faces[i].resize(face_size);
// extra space after first number
          file.get();
          for (Mesh::index_t j = 0; j < face_size; ++j) {
            file >> faces[i][j];
          }
        }
      }
    }
// get submesh data
    Mesh::submeshes_t submeshes;
    if (submeshCount > 0) {
// search for "submeshes" line
      std::string line;
      while (std::getline(file, line))
        if (line == "submeshes")
          break;
        else if (file.eof())
          return fail("submesh_count > 0 but submeshes not found");
      submeshes.resize(submeshCount);
      if (binary) {
// read data
        for (Mesh::index_t i = 0; i < submeshCount; ++i) {
// get size hint
          Mesh::index_t submesh_size = 0;
          file.read(reinterpret_cast<char*>(&submesh_size), sizeof(Mesh::index_t));
          submeshes[i].resize(submesh_size);
          for (Mesh::index_t j = 0; j < submesh_size; ++j) {
            file.read(reinterpret_cast<char*>(&submeshes[i][j]), sizeof(Mesh::index_t));
          }
// next line
          file.get();
        }
      } else {
        for (Mesh::index_t i = 0; i < submeshCount; ++i) {
// size hint
          Mesh::index_t submesh_size = 0;
          file >> submesh_size;
          if (submesh_size <= 0) {
            return fail("invalid submesh size");
          }
          submeshes[i].resize(submesh_size);
// extra space after first number
          file.get();
          for (Mesh::index_t j = 0; j < submeshes[i].size(); ++j) {
            file >> submeshes[i][j];
          }
        }
      }
    }
    return Mesh(vertices, normals, tangents, uvs, uv2s, uv3s, uv4s, colors, faces, submeshes);
  } catch (std::exception& e) {
    return fail("Failed to read mesh file: " + std::string(e.what()));
  }
}

} // ams