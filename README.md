# AMS Game Engine
## Introduction
The AMS Game Engine is an open source cross-platform game engine written in C++ and Vulkan.
It is implemented entirely in C++20 modules and employs the most cutting edge C++ language features.
## Features
* C++20 modules
* Cross Platform support
* Vulkan
* ECS
* Scripting -- Not implemented yet
### Modules
#### What are all these .cppm files in the source code?
The AMS Game Engine is written in C++20 modules.
Typical legacy C++ code really only needed two types of files: headers (.h/.hpp) and source (.cpp).
Since there were only two contexts, buildsystems could easily deduce the relationships between files and reliably generate a build.
C++20 modules introduce a number of new contexts: module interfaces, module implementations, module partitions, and header units.
Because of the extra contexts, buildsystems need additional information to be able to deduce the relationships between files.
There are two ways to provide buildsystems with this information:
1. Keep the conventional file extensions (.h/.cpp) and manually specify the context for each file.
2. Use additional extensions which clearly delineate context.
The AMS Game Engine uses the second method because it is more convenient and less error-prone.
These are the extensions used:
* .cppm -- Module interface and module partitions
* .cxx -- Module implementation
* .hpp -- Header unit
* .h -- Legacy C++ header file which must be included in the global module fragment
* .cpp -- Non-module C++ source file
#### What is the public/ directory?
The public/ directory contains public module interfaces which are exported by the library.
#### Where can the module implementation code be found?
The module implementation code is in the src/ directory.

## Building
### Requirements
* C++20 compiler (limited cross-platform support, see footnote)
* CMake 3.23
* Vulkan SDK
* Python 3.9
### Building on Windows
1. Clone the repository
2. Run cmake
3. Build the solution
### Building on Linux
1. Clone the repository
2. Run cmake & make

## Footnotes
### C++20 compiler support
The AMS Game Engine is currently only tested on Windows with MSVC 19.29.
When using C++20, most standard library features are imported as header units. This design choice was made to keep symbol
leakage to an absolute minimum to improve ABI stability.
The C++20 standard does not specify which standard library features should be implemented as header units (if any).
This means that some older C++20 compilers may not be able to compile the project.
When using C++23 or newer, cross-platform support is guaranteed, as the entire standard library is imported as a module.
