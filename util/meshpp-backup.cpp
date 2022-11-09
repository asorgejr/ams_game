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

#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <regex>
#include <tuple>
#include <argparse/argparse.hpp>
#include "BoxComment.hpp"

#ifndef AMS_MODULES
#include <ams/StringExtensions.hpp>
#include <ams/game/Mesh.hpp>
#include <ams/game/MeshLoaders.hpp>
#ifdef AMS_USD_LOADER
#include <ams/usd/USDMeshLoader.hpp>
#endif
#else
import ams.StringExtensions;
import ams.game.Mesh;
import ams.game.MeshLoaders;
#ifdef AMS_USD_LOADER
import ams.usd.USDMeshLoader;
#endif
#endif

constexpr bool AMSModules=
#ifdef AMS_MODULES
true;
#else
false;
#endif

using namespace ams;
using namespace std;
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

const string importStatement = "import ams.game.Mesh;";
const string includeStatement = "#include <ams/game/Mesh.hpp>";


tuple<int, int> getNsBracketsPos(const string& str) {
  regex nsOpenRegex(R"(namespace\s+([a-zA-Z0-9_]+)\s*\{)");
  regex nsCloseRegex(R"(\}(\s*//\s*namespace\s+([a-zA-Z0-9_]+))?)");
  smatch nsOpenMatch;
  smatch nsCloseMatch;
  if (regex_search(str, nsOpenMatch, nsOpenRegex)) {
    int nsOpenPos = nsOpenMatch.position() + nsOpenMatch.length();
    int nsClosePos = nsOpenPos;
    int nsOpenCount = 1;
    int nsCloseCount = 0;
    while (nsOpenCount != nsCloseCount) {
      if (regex_search(str.begin() + nsClosePos, str.end(), nsCloseMatch, nsCloseRegex)) {
        nsClosePos = nsCloseMatch.position();
        nsCloseCount++;
      }
      if (regex_search(str.begin() + nsClosePos, str.end(), nsOpenMatch, nsOpenRegex)) {
        nsClosePos = nsOpenMatch.position();
        nsOpenCount++;
      }
    }
    return make_tuple(nsOpenPos, nsClosePos);
  }
  return make_tuple(-1, -1);
}


enum class BraceKind : char {
  Angle,
  Curly,
  Round,
  Square
};


int findClosingBrace(const string& str, int pos, BraceKind kind=BraceKind::Curly) {
  int braceCount = 1;
  char ob = kind == BraceKind::Angle ? '<' : kind == BraceKind::Curly ? '{' : kind == BraceKind::Round ? '(' : '[';
  char cb = kind == BraceKind::Angle ? '>' : kind == BraceKind::Curly ? '}' : kind == BraceKind::Round ? ')' : ']';
  while (braceCount > 0) {
    if (str[pos] == ob) {
      braceCount++;
    } else if (str[pos] == cb) {
      braceCount--;
    }
    pos++;
  }
  return pos;
}

int findClosingBrace(ostream& stream, BraceKind kind=BraceKind::Curly) {
  auto streamloc = stream.tellp(); // save current position
  stringstream ss;
  ss << stream.rdbuf(); // copy stream to stringstream
  return findClosingBrace(ss.str(), streamloc, kind);
}

/**
 * @brief find a mesh declaration
 * @param str - the string to search
 * @param meshName - the name of the mesh to find
 * @param start - where to start the search
 * @param end - where to end the search
 * @return [int, bool,int]
 * <p>first: the position of the start of the declaration</p>
 * <p>second: true if the declaration is defined inline</p>
 * <p>third: the position of the start of the definition, if applicable</p>
 * <p>fourth: the position of the end of the declaration, or possibly, the definition</p>
 */
tuple<int,bool,int,int> findMeshDeclarationPos(const string& str, const string& meshName, int start=0, int end=-1) {
  regex meshRegex("(ams::)?Mesh\\s+" + meshName + R"((\s*[=({])?)"); // NOTE: bug prone if user meddles with output, but it's a tool
  smatch meshMatch;
  int pos = -1;
  bool isDefined = false;
  bool defStartPos = -1;
  bool defEndPos = -1;
  if (end == -1) {
    end = str.length();
  }
  if (regex_search(str.begin() + start, str.begin() + end, meshMatch, meshRegex)) {
    pos = meshMatch.position();
    isDefined = meshMatch[2].length() > 0;
    if (!isDefined) {
      defEndPos = pos + meshMatch.length() + 1;
    }
  }
  if (isDefined) {
    defStartPos = pos + meshMatch.length();
    int braceClosePos = findClosingBrace(str, defStartPos);
    
    // check if there is a semicolon after the closing brace
    int semicolonPos = str.find_first_of(";", braceClosePos + 1);
    if (semicolonPos != string::npos) {
      defEndPos = semicolonPos + 1;
    } else {
      defEndPos = braceClosePos + 1;
    }
  }
  return make_tuple(pos, isDefined, defStartPos, defEndPos);
}



void writeBody(ostream& out, const Mesh& mesh, int indent = 0) {
  auto ind = string(indent, ' ');
  out << ind << "{" << endl;
  // vertices
  out << ind << "  { /* vertices"; if (mesh.getVertexCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& v: mesh.getVertices()) {
    out << ind << "    {" << v.x << ", " << v.y << ", " << v.z << "}," << endl;
  }
  out << ind << "  }," << endl; // vertices end
  // normals
  out << ind << "  { /* normals"; if (mesh.getNormalCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& n: mesh.getNormals()) {
    out << ind << "    {" << n.x << ", " << n.y << ", " << n.z << "}," << endl;
  }
  out << ind << "  }," << endl; // normals end
  // tangents
  out << ind << "  { /* tangents"; if (mesh.getTangentCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& t: mesh.getTangents()) {
    out << ind << "    {" << t.x << ", " << t.y << ", " << t.z << "}," << endl;
  }
  out << ind << "  }," << endl; // tangents end
  // uv
  out << ind << "  { /* uv"; if (mesh.getUVCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& uv: mesh.getUV()) {
    out << ind << "    {" << uv.x << ", " << uv.y << "}," << endl;
  }
  out << ind << "  }," << endl; // uv0 end
  // uv2
  out << ind << "  { /* uv2"; if (mesh.getUV2Count() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& uv: mesh.getUV2()) {
    out << ind << "    {" << uv.x << ", " << uv.y << "}," << endl;
  }
  out << ind << "  }," << endl; // uv2 end
  // uv3
  out << ind << "  { /* uv3"; if (mesh.getUV3Count() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& uv: mesh.getUV3()) {
    out << ind << "    {" << uv.x << ", " << uv.y << "}," << endl;
  }
  out << ind << "  }," << endl; // uv3 end
  // uv4
  out << ind << "  { /* uv4"; if (mesh.getUV4Count() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& uv: mesh.getUV4()) {
    out << ind << "    {" << uv.x << ", " << uv.y << "}," << endl;
  }
  out << ind << "  }," << endl; // uv4 end
  // colors
  out << ind << "  { /* colors"; if (mesh.getColorCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& c: mesh.getColors()) {
    out << ind << "    {" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << "}," << endl;
  }
  out << ind << "  }," << endl; // colors end
  // faces
  out << ind << "  { /* faces"; if (mesh.getFaceCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& f: mesh.getFaces()) {
    out << ind << "    {";
    for (auto i = 0; i < f.size(); i++) {
      out << ind << f[i]; if (i < f.size() - 1) out << ", ";
    }
    out << ind << "}," << endl;
  }
  out << ind << "  }," << endl; // faces end
  // submeshes
  out << ind << "  { /* submeshes"; if (mesh.getSubmeshCount() > 0) out << " */" << endl; else out << " (empty) */";
  for (auto& s: mesh.getSubmeshes()) {
    out << ind << "    {";
    for (auto i = 0; i < s.size(); i++) {
      out << ind << s[i]; if (i < s.size() - 1) out << ", ";
    }
    out << ind << "}," << endl;
  }
  out << ind << "  }" << endl; // submeshes end
  out << ind << "};" << endl; // mesh end
}


void writeIntoClassHeader(fstream& out, const Mesh& mesh, const string& classname, const string& meshName, bool inl=false) {
  auto outloc = out.tellp(); // save current position

  // mesh member declaration
  string decl = "static const ams::Mesh " + meshName;
  if (inl)
    decl = "inline " + decl;
  
  // find class start
  int classidx = -1;
  string line;
  while (getline(out, line)) {
    classidx++;
    if (line.find(classname) != string::npos) {
      break;
    }
  }
  int classendidx = findClosingBrace(out);
  if (classendidx == -1) {
    out.seekp(outloc); // restore position
  }
  stringstream classbody;
  if (classidx > -1 && classendidx > classidx) {
    // class found
    // read class body
    for (int i = 0; i < classendidx - classidx; i++) {
      getline(out, line);
      classbody << line << endl;
    }
    // find declaration
    bool declfound = false;
    int declidx = -1;
    while (getline(classbody, line)) {
      if (line.find(decl) != string::npos) {
        declfound = true;
        declidx = out.tellg();
        break;
      }
    }
    if (!declfound) {
      // declaration not found, append it to classbody
      classbody << decl;
      if (inl) {
        classbody << " = ";
        writeBody(classbody, mesh, 2);
      } else {
        out << ";" << endl;
      }
      out.seekp(0, ios::beg);
      // find class end
      classendidx = findClosingBrace(out);
    } else {
      // declaration found, replace it if inl
      if (inl) {
        classbody.seekp(declidx, ios::beg);
        auto declendidx = findClosingBrace(classbody);
      }
    }
  } 
}


/**
 * @brief Save a mesh to a C++ header file
 * @param mesh - Mesh to save
 * @param path - Path to save to
 * @param name - Name of the mesh variable
 * @param ns - Namespace to use
 * @param split - Split declaration and definition to .hpp and .cpp files
 */
void saveToHPP(const Mesh& mesh, const fs::path& path, const string& name, const string* ns=nullptr,
               const fs::path* cpppath=nullptr, const string* classname=nullptr) {
  auto genwarn = []{
    return boxComment("This is an auto-generated file."
                      "\nEdits will be overwritten the next time meshhpp is run."
                      "\nEdit at your own risk.", BoxCommentStyle::Slash, 4);
  };
  fstream out(path);
  fstream outcpp;
  if (cpppath)
    outcpp.open(*cpppath);
  // find pragma once
  string line;
  bool pragmafound = false;
  int pragmaidx = -1;
  while (getline(out, line)) {
    if (line.find("#pragma once") != string::npos) {
      pragmafound = true;
      pragmaidx = out.tellg();
      break;
    }
  }
  // find include
  bool includefound = false;
  int includeidx = -1;
  while (getline(out, line)) {
    if (line.find(includeStatement) != string::npos) {
      includefound = true;
      includeidx = out.tellg();
      break;
    }
  }
  
  out << genwarn() << endl;
  out << "#pragma once" << endl;
  out << includeStatement << endl;
  out << endl;
  if (ns) 
    out << "namespace " << *ns << " {" << endl;
  if (classname) {
    out << "class " << *classname << " {" << endl;
    out << "public:" << endl;
    out << "  ";
    if (!cpppath)
      out << "inline ";
    out << "static const ";
  }
  out << "ams::Mesh " << name;
  if (cpppath && classname) out << ";" << endl; // declaration only, defer class member definition to cpp file below
  else {
    out << " = ";
    writeBody(out, mesh, 0);
  } // write body inline
  if (classname) out << "};" << endl; // class end
  if (ns) out << "}" << endl; // namespace end

  if (cpppath && classname) {
    outcpp << genwarn() << endl;
    outcpp << "#include \"" << path.filename().string() << "\"" << endl;
    outcpp << endl;
    if (ns)
      outcpp << "namespace " << *ns << " {" << endl;
    outcpp << "const ams::Mesh " << *classname << "::" << name << " = ";
    writeBody(outcpp, mesh, 0);
    if (ns)
      outcpp << "}" << endl; // namespace end
  }
}


int main(int argc, char** argv) {
  argparse::ArgumentParser program("meshhpp");
  program.add_argument("input")
    .help("input file");
  program.add_argument("output")
    .help("output file");
  program.add_argument("-n", "--name")
    .help("name of the mesh")
    .default_value(string("mesh"));
  program.add_argument("-N", "--namespace")
    .help("wraps the mesh in a namespace");
  program.add_argument("-s", "--split")
    .help("split declaration and definition to .hpp and .cpp files")
    .default_value(false)
    .implicit_value(true);
  program.add_argument("-o", "--outcpp")
    .help("specifies an output cpp file and splits declaration and definition of the mesh");
  program.add_argument("-c", "--classname")
    .help("wrap the mesh in a named class");
  try {
    program.parse_args(argc, argv);
  }
  catch (const runtime_error& err) {
    cout << err.what() << endl;
    cout << program;
    exit(0);
  }
  auto input = fs::path(program.get<string>("input"));
  auto output = fs::path(program.get<string>("output"));
  auto name = program.get<string>("name");
  auto split = program.get<bool>("split");

  string* ns = nullptr;
  string* classname = nullptr;
  fs::path* outcpp = nullptr;

  if (auto outcppopt = program.present("outcpp")) {
    if (!outcpp)
      outcpp = new fs::path(outcppopt.value());
  }
  if (split && !outcpp) {
    outcpp = new fs::path(input);
    *outcpp = outcpp->replace_extension(".cpp");
  }
  
  if (auto nsopt = program.present("namespace"))
    ns = new string(nsopt.value());
  
  if (auto classopt = program.present("classname"))
    classname = new string(classopt.value());
  
  auto mesh = Mesh::fromFile(input);
  saveToHPP(mesh, output, name, ns, outcpp, classname);
  
  if (ns) delete ns;
  if (classname) delete classname;
  if (outcpp) delete outcpp;
  return 0;
}
