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

#include <gtest/gtest.h>

#ifndef AMS_MODULES
#include "ams/game/Mesh.hpp"
#include "ams/game/MeshLoaders.hpp"
#else
import ams.game.Mesh;
import ams.game.MeshLoaders;
#endif


using namespace ams;
using std::vector;

bool hasBlendLoader = Mesh::registerMeshLoader<BlendMeshLoader>();
bool hasFBXLoader = Mesh::registerMeshLoader<FBXMeshLoader>();
bool hasGLBLoader = Mesh::registerMeshLoader<GLBMeshLoader>();
bool hasGLTFLoader = Mesh::registerMeshLoader<GLTFMeshLoader>();
bool hasObjLoader = Mesh::registerMeshLoader<ObjMeshLoader>();
bool hasPlyLoader = Mesh::registerMeshLoader<PlyMeshLoader>();

TEST(Mesh, MeshLoaders) {
  ASSERT_TRUE(hasBlendLoader);
  ASSERT_TRUE(hasFBXLoader);
  ASSERT_TRUE(hasGLBLoader);
  ASSERT_TRUE(hasGLTFLoader);
  ASSERT_TRUE(hasObjLoader);
  ASSERT_TRUE(hasPlyLoader);
}

TEST(Mesh, Mesh) {
  Mesh mesh{{}};
  EXPECT_EQ(mesh.getVertexCount(), 0);
  EXPECT_EQ(mesh.getNormalCount(), 0);
  EXPECT_EQ(mesh.getTangentCount(), 0);
  EXPECT_EQ(mesh.getUVCount(), 0);
  EXPECT_EQ(mesh.getUV2Count(), 0);
  EXPECT_EQ(mesh.getUV3Count(), 0);
  EXPECT_EQ(mesh.getUV4Count(), 0);
  EXPECT_EQ(mesh.getColorCount(), 0);
  EXPECT_EQ(mesh.getFaceCount(), 0);
  EXPECT_EQ(mesh.getSubmeshCount(), 0);

  EXPECT_EQ(mesh.getVertices(), Mesh::vertices_t());
  EXPECT_EQ(mesh.getNormals(), Mesh::normals_t());
  EXPECT_EQ(mesh.getTangents(), Mesh::tangents_t());
  EXPECT_EQ(mesh.getUV(), Mesh::uvs_t());
  EXPECT_EQ(mesh.getUV2(), Mesh::uvs_t());
  EXPECT_EQ(mesh.getUV3(), Mesh::uvs_t());
  EXPECT_EQ(mesh.getUV4(), Mesh::uvs_t());
  EXPECT_EQ(mesh.getColors(), Mesh::colors_t());
  EXPECT_EQ(mesh.getFaces(), Mesh::faces_t());
  EXPECT_EQ(mesh.getSubmeshes(), Mesh::submeshes_t());  
}


// Sphere mesh
// Should have:
// 960 Vertices
// 320 Polygons


TEST(Mesh, MeshFromWavefrontObj) {
  const int vertexCount = 960;
  const int faceCount = 320;
  auto filepath = std::string(TEST_RESOURCES_DIR "/tri_sphere_all_attribs.obj");
  ams::Mesh mesh = Mesh::fromFile(filepath);
  auto verts = mesh.getVertices();
  auto norms = mesh.getNormals();
  auto tangs = mesh.getTangents();
  auto uvs = mesh.getUV();
  auto uvs2 = mesh.getUV2();
  auto uvs3 = mesh.getUV3();
  auto uvs4 = mesh.getUV4();
  auto cols = mesh.getColors();
  auto faces = mesh.getFaces();
  auto submeshes = mesh.getSubmeshes();
  
  EXPECT_EQ(verts.size(), vertexCount);
  EXPECT_EQ(norms.size(), vertexCount);
  EXPECT_EQ(tangs.size(), 0);
  EXPECT_EQ(uvs.size(), vertexCount);
  EXPECT_EQ(uvs2.size(), vertexCount);
  EXPECT_EQ(uvs3.size(), 0);
  EXPECT_EQ(uvs4.size(), 0);
  EXPECT_EQ(cols.size(), vertexCount);
  EXPECT_EQ(faces.size(), faceCount);
  EXPECT_EQ(submeshes.size(), 2);
}

TEST(Mesh, MeshFromAMSASCII) {
  const int vertexCount = 960;
  const int faceCount = 320;
  auto filepath = std::string(TEST_RESOURCES_DIR "/tri_sphere_all_attribs.ams");
  ams::Mesh mesh = Mesh::fromFile(filepath);
  auto verts = mesh.getVertices();
  auto norms = mesh.getNormals();
  auto tangs = mesh.getTangents();
  auto uvs = mesh.getUV();
  auto uvs2 = mesh.getUV2();
  auto uvs3 = mesh.getUV3();
  auto uvs4 = mesh.getUV4();
  auto cols = mesh.getColors();
  auto faces = mesh.getFaces();
  auto submeshes = mesh.getSubmeshes();
  
  EXPECT_EQ(verts.size(), vertexCount);
  EXPECT_EQ(norms.size(), vertexCount);
  EXPECT_EQ(tangs.size(), 0);
  EXPECT_EQ(uvs.size(), vertexCount);
  EXPECT_EQ(uvs2.size(), vertexCount);
  EXPECT_EQ(uvs3.size(), 0);
  EXPECT_EQ(uvs4.size(), 0);
  EXPECT_EQ(cols.size(), vertexCount);
  EXPECT_EQ(faces.size(), faceCount);
  EXPECT_EQ(submeshes.size(), 2);
}