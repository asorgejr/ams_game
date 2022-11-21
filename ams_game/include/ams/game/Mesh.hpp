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

/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[export module ams.Mesh]*/
/*[exclude begin]*/
#pragma once
#include <ams/Serializable.hpp>
#include <ams/spatial/internal/config.hpp>
#include <ams/spatial/Vec.hpp>
#include "Object.hpp"
/*[exclude end]*/
#include <string>
#include <vector>
#include <map>
#include <filesystem>
/*[import ams.Serializable]*/
/*[import ams.spatial.internal.config]*/
/*[import ams.spatial.Vec]*/
/*[import ams.game.Object]*/

/*[export]*/ namespace ams {

class Mesh;

/**
 * @brief A IMeshLoader is an implementable class responsible for loading a mesh from a particular file format.
 * It must have a default constructor.
 */
class IMeshLoader {
public:
  /**
   * @brief The type of file format this loader supports. This should be a file extension without the dot.
   * @example <code>return "obj";</code>
   */
  virtual const std::string filetype() const = 0;
  /**
   * @brief Load a mesh from a file. It is expected that the Mesh is well defined, with a minimum of vertices, normals
   * texture coordinates and faces being defined.
   * @param path - The path to the file to load.
   */
  virtual Mesh load(const std::filesystem::path& path) const = 0;

  virtual ~IMeshLoader() = default;
};

// concept requiring inheriting from IMeshLoader and has default constructor and can be moved.
template <typename T>
concept MeshLoaderT = std::is_base_of_v<IMeshLoader, T>
                      && std::is_default_constructible_v<T>
                      && std::is_move_constructible_v<T>;



struct AMS_GAME_EXPORT Face {
  uint32_t i0=-1;
  uint32_t i1=-1;
  uint32_t i2=-1;
  uint32_t i3=-1;
};

/**
 * @brief A mesh is a collection of vertices and indices that can be rendered.
 */
class AMS_GAME_EXPORT Mesh : public Object, public Serializable {
public:
  inline static const std::string ams_file_header = "ams_mesh";
  inline static const std::string ams_file_version = "1";
  using index_t         = uint32_t;
  using vertex_elem_t   = Vec3<decimal_t>;
  using vertices_t      = std::vector<vertex_elem_t>;
  using normal_elem_t   = Vec3<decimal_t>;
  using normals_t       = std::vector<normal_elem_t>;
  using tangent_elem_t  = Vec3<decimal_t>;
  using tangents_t      = std::vector<tangent_elem_t>;
  using uv_elem_t       = Vec2<decimal_t>;
  using uvs_t           = std::vector<uv_elem_t>;
  using color_elem_t    = Vec4<decimal_t>;
  using colors_t        = std::vector<color_elem_t>;
  using face_elem_t     = std::vector<index_t>;
  using faces_t         = std::vector<face_elem_t>;
  using submesh_elem_t  = std::vector<index_t>;
  using submeshes_t     = std::vector<submesh_elem_t>;

protected:
  /**
   * @brief The vertices of the mesh.
   */
  vertices_t vertices;
  /**
   * @brief The normals of the mesh.
   */
  normals_t normals;
  /**
   * @brief The tangents of the mesh.
   */
  tangents_t tangents;
  /**
   * @brief The texture coordinates of the mesh.
   */
  uvs_t uv;
  /**
   * @brief The second set of texture coordinates of the mesh.
   */
  uvs_t uv2;
  /**
   * @brief The third set of texture coordinates of the mesh.
   */
  uvs_t uv3;
  /**
   * @brief The fourth set of texture coordinates of the mesh.
   */
  uvs_t uv4;
  /**
   * @brief The colors of the mesh.
   */
  colors_t colors;
  /**
   * @brief The faces of the mesh.
   * @details Each face is a list of indices.
   */
  faces_t faces;
  /**
   * @brief The submeshes of the mesh.
   * @details Each submesh is a list of faces.
   */
  submeshes_t submeshes;
  
  inline static std::map<const std::string, std::unique_ptr<IMeshLoader>> meshLoaders{};

public:
  /**
   * @brief Construct a new Mesh object.
   * @param vertices The vertices of the mesh.
   * @param indices The indices of the mesh.
   */
  Mesh(const vertices_t& vertices={}, const normals_t& normals={}, const tangents_t& tangents={},
       const uvs_t& uv={}, const uvs_t& uv2={}, const uvs_t& uv3={}, const uvs_t& uv4={},
       const colors_t& colors={}, const faces_t& faces={}, const submeshes_t& submeshes={});

#pragma region Accessors
  /**
   * @brief Get the vertices of the mesh.
   */
  [[nodiscard]] const vertices_t& getVertices() const;
  /**
   * @brief Set the vertices of the mesh.
   */
  void setVertices(const vertices_t& vertices);
  
  /**
   * @brief Get the normals of the mesh.
   */
  [[nodiscard]] const normals_t& getNormals() const;
  /**
   * @brief Set the normals of the mesh.
   */
  void setNormals(const normals_t& normals);
  
  /**
   * @brief Get the tangents of the mesh.
   */
  [[nodiscard]] const tangents_t& getTangents() const;
  /**
   * @brief Set the tangents of the mesh.
   */
  void setTangents(const tangents_t& tangents);
  
  /**
   * @brief Get the UV coordinates of the mesh.
   */
  [[nodiscard]] const uvs_t& getUV() const;
  /**
   * @brief Set the UV coordinates of the mesh.
   */
  void setUV(const uvs_t& uv);
  
  /**
   * @brief Get the UV2 coordinates of the mesh.
   */
  [[nodiscard]] const uvs_t& getUV2() const;
  /**
   * @brief Set the UV2 coordinates of the mesh.
   */
  void setUV2(const uvs_t& uv2);
  
  /**
   * @brief Get the UV3 coordinates of the mesh.
   */
  [[nodiscard]] const uvs_t& getUV3() const;
  /**
   * @brief Set the UV3 coordinates of the mesh.
   */
  void setUV3(const uvs_t& uv3);
  
  /**
   * @brief Get the UV4 coordinates of the mesh.
   */
  [[nodiscard]] const uvs_t& getUV4() const;
  /**
   * @brief Set the UV4 coordinates of the mesh.
   */
  void setUV4(const uvs_t& uv4);
  
  /**
   * @brief Get the colors of the mesh.
   */
  [[nodiscard]] const colors_t& getColors() const;
  /**
   * @brief Set the colors of the mesh.
   */
  void setColors(const colors_t& colors);
  
  /**
   * @brief Get the faces of the mesh.
   */
  [[nodiscard]] const faces_t& getFaces() const;
  /**
   * @brief Set the faces of the mesh.
   */
  void setFaces(const faces_t& faces);
  
  /**
   * @brief Get the submeshes of the mesh.
   */
  [[nodiscard]] const submeshes_t& getSubmeshes() const;
  /**
   * @brief Set the submeshes of the mesh.
   */
  void setSubmeshes(const submeshes_t& submeshes);

#pragma endregion GetterSetters

#pragma region Getters
  
  /**
   * @brief Get the number of vertices in the mesh.
   * @return uint32_t The number of vertices in the mesh.
   */
  [[nodiscard]] uint32_t getVertexCount() const;
  
  /**
   * @brief Get the number of normals in the mesh.
   * @return uint32_t The number of normals in the mesh.
   */
  [[nodiscard]] uint32_t getNormalCount() const;
  
  /**
   * @brief Get the number of tangents in the mesh.
   * @return uint32_t The number of tangents in the mesh.
   */
  [[nodiscard]] uint32_t getTangentCount() const;
  
  /**
   * @brief Get the number of uv0 in the mesh.
   * @return uint32_t The number of uv0 in the mesh.
   */
  [[nodiscard]] uint32_t getUVCount() const;
  
  /**
   * @brief Get the number of uv1 in the mesh.
   * @return uint32_t The number of uv1 in the mesh.
   */
  [[nodiscard]] uint32_t getUV2Count() const;
  
  /**
   * @brief Get the number of uv2 in the mesh.
   * @return uint32_t The number of uv2 in the mesh.
   */
  [[nodiscard]] uint32_t getUV3Count() const;
  
  /**
   * @brief Get the number of uv3 in the mesh.
   * @return uint32_t The number of uv3 in the mesh.
   */
  [[nodiscard]] uint32_t getUV4Count() const;
  
  /**
   * @brief Get the number of colors in the mesh.
   * @return uint32_t The number of colors in the mesh.
   */
  [[nodiscard]] uint32_t getColorCount() const;

  /**
   * @brief Get the number of faces in the mesh.
   * @return uint32_t The number of faces in the mesh.
   */
  [[nodiscard]] uint32_t getFaceCount() const;
  
  /**
   * @brief Get the number of submeshes in the mesh.
   * @return uint32_t The number of submeshes in the mesh.
   */
  [[nodiscard]] uint32_t getSubmeshCount() const;
  
#pragma endregion Getters
  

  
public:
  /**
   * @brief Smart creation of a new Mesh from a file. If the file is not supported and exceptions are enabled, throws an
   * exception. If exceptions are disabled, returns a default Mesh object.
   * @param path - The path to the file.
   * @details - Support for additional file types can be added by creating a new IMeshLoader and registering it using
   * Mesh::registerMeshLoader().
   */
  static Mesh fromFile(const std::filesystem::path& path);
  
  static Mesh triangulate(const Mesh& mesh);
  
  static void saveToFile(const Mesh& mesh, const std::filesystem::path& path, bool binary = true);
  
  /**
   * @brief Adds a Mesh loader to the list of supported loaders.
   * @tparam TMeshLoader - The type of the Mesh loader.
   * @return false if the extension is already in use, true otherwise.
   */
  template <MeshLoaderT TMeshLoader>
  inline static bool registerMeshLoader() {
    auto loader = std::make_unique<TMeshLoader>();
    if (meshLoaders.contains(loader->filetype())) return false;
    meshLoaders[loader->filetype()] = std::move(loader);
    return true;
  }
  
  inline static std::vector<std::string> getSupportedFileTypes() {
    std::vector<std::string> fileTypes;
    fileTypes.reserve(meshLoaders.size());
    for (const auto& [key, value] : meshLoaders) {
      fileTypes.push_back(key);
    }
    return fileTypes;
  }

  static normals_t generateNormals(vertices_t vts, faces_t faces);
};

} // ams
