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

#include <iostream>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <argparse/argparse.hpp>

#ifndef AMS_MODULES
#include <ams/game/Mesh.hpp>
#include <ams/game/MeshLoaders.hpp>
#ifdef AMS_USD_LOADER
#include <ams/usd/USDMeshLoader.hpp>
#endif
#else
import ams.game.Mesh;
import ams.game.MeshLoaders;
#ifdef AMS_USD_LOADER
import ams.usd.USDMeshLoader;
#endif
#endif

using namespace ams;
namespace fs = std::filesystem;

// register loaders
bool hasAMSLoader = Mesh::registerMeshLoader<AMSMeshLoader>();
bool hasBlendLoader = Mesh::registerMeshLoader<BlendMeshLoader>();
bool hasFBXLoader = Mesh::registerMeshLoader<FBXMeshLoader>();
bool hasGLBLoader = Mesh::registerMeshLoader<GLBMeshLoader>();
bool hasGLTFLoader = Mesh::registerMeshLoader<GLTFMeshLoader>();
bool hasObjLoader = Mesh::registerMeshLoader<ObjMeshLoader>();
bool hasPlyLoader = Mesh::registerMeshLoader<PlyMeshLoader>();
#ifdef AMS_USD_LOADER
bool hasUSDLoader = Mesh::registerMeshLoader<USDMeshLoader>();
#endif


void saveToHPP(const Mesh& mesh, const fs::path& path);

int main(int argc, char** argv) {
  argparse::ArgumentParser program("convmesh");
  program.add_argument("input")
    .help("Input file path");
  program.add_argument("outputdir")
    .help("Output directory path");
  program.add_argument("-b", "--binary")
    .help("Output binary file")
    .default_value(false)
    .implicit_value(true);
  program.add_argument("-n", "--name")
    .help("Output file name")
    .default_value(std::string());
  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }
  auto input = fs::path(program.get<std::string>("input"));
  auto output = fs::path(program.get<std::string>("outputdir"));
  auto name = program.get<std::string>("name");
  auto binary = program.get<bool>("binary");
  
  if (!fs::exists(input)) {
    std::cout << "Input file does not exist" << std::endl;
    exit(0);
  }
  if (!fs::exists(output)) {
    std::cout << "Output directory does not exist" << std::endl;
    exit(0);
  }
  // check if input file is supported by extension
  // get extension without dot
  auto ext = fs::path(input).extension().string().substr(1);
  auto supported = Mesh::getSupportedFileTypes();
  if (std::find(supported.begin(), supported.end(), ext) == supported.end()) {
    std::cout << "Input file type is not supported" << std::endl;
    exit(0);
  }
  // make sure we are not overwriting the input file
  auto outputpath = fs::path(output) / fs::path(input).filename();
  if (fs::path(input).string() == outputpath.string()) {
    std::cout << "Output file cannot be the Input file" << std::endl;
    exit(0);
  }
  
  if (name.empty()) {
    name = fs::path(input).stem().string();
  }
  
  auto mesh = Mesh::fromFile(input);
  auto outfile = fs::path(output.string() + "/" + name + ".ams");
  Mesh::saveToFile(mesh, outfile, binary);
  return 0;
}

void saveToHPP(const Mesh& mesh, const fs::path& path, const std::string& name, const std::string& ns="mesh") {
  std::ofstream out(path);
  out << "#pragma once" << std::endl;
  out << "#include <ams/game/Mesh.hpp>" << std::endl;
  out << "namespace " << ns << " {" << std::endl;
  out << "Mesh " << name << " {" << std::endl;
  // vertices
  out << "  {" << std::endl;
  for (auto& v: mesh.getVertices()) {
    out << "    {" << v.x << ", " << v.y << ", " << v.z << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // normals
  out << "  {" << std::endl;
  for (auto& n: mesh.getNormals()) {
    out << "    {" << n.x << ", " << n.y << ", " << n.z << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // tangents
  out << "  {" << std::endl;
  for (auto& t: mesh.getTangents()) {
    out << "    {" << t.x << ", " << t.y << ", " << t.z << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // uv0
  out << "  {" << std::endl;
  for (auto& uv: mesh.getUV()) {
    out << "    {" << uv.x << ", " << uv.y << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // uv2
  out << "  {" << std::endl;
  for (auto& uv: mesh.getUV2()) {
    out << "    {" << uv.x << ", " << uv.y << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // uv3
  out << "  {" << std::endl;
  for (auto& uv: mesh.getUV3()) {
    out << "    {" << uv.x << ", " << uv.y << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // uv4
  out << "  {" << std::endl;
  for (auto& uv: mesh.getUV4()) {
    out << "    {" << uv.x << ", " << uv.y << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // colors
  out << "  {" << std::endl;
  for (auto& c: mesh.getColors()) {
    out << "    {" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // faces
  out << "  {" << std::endl;
  for (auto& f: mesh.getFaces()) {
    out << "    {";
    for (auto& i: f) {
      out << i << ", ";
    }
    out << "}," << std::endl;
  }
  out << "  }," << std::endl;
  // submeshes
  out << "  {" << std::endl;
  for (auto& s: mesh.getSubmeshes()) {
    out << "    {";
    for (auto& i: s) {
      out << i << ", ";
    }
    out << "}," << std::endl;
  }
  out << "  }" << std::endl;
  out << "};" << std::endl;
}

