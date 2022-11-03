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
module;
export module ams.game.Platform;

import <string>;
import <thread>;

export namespace ams {

enum class Platform {
  Windows,
  Linux,
  MacOS,
  Android,
  iOS,
  Web,
  Unknown
};

enum class Architecture {
  x86,
  x64,
  ARM,
  ARM64,
  Unknown
};

enum class Compiler {
  MSVC,
  Clang,
  GCC,
  Unknown
};

struct SystemInfo {
  const Platform os;
  const std::string os_version;
  const Architecture architecture;
  const Compiler compiler;
  const std::string compiler_version;
  const int cpu_count;
} const System {
.os=
#if defined(AMS_OS_WINDOWS)
ams::Platform::Windows,
#elif defined(AMS_OS_MACOS)
ams::Platform::MacOS,
#elif defined(AMS_OS_LINUX)
  ams::Platform::Linux,
#elif defined(AMS_OS_ANDROID)
  ams::Platform::Android,
#elif defined(AMS_OS_IOS)
  ams::Platform::iOS,
#elif defined(AMS_OS_WEB)
  ams::Platform::Web,
#else
  ams::Platform::Unknown,
#endif

.os_version=AMS_OS_VERSION,

.architecture=
#if defined(AMS_ARCH_X86)
ams::Architecture::x86,
#elif defined(AMS_ARCH_X64)
ams::Architecture::x64,
#elif defined(AMS_ARCH_ARM)
ams::Architecture::ARM,
#elif defined(AMS_ARCH_ARM64)
  ams::Architecture::ARM64,
#else
  ams::Architecture::Unknown,
#endif

.compiler=
#if defined(AMS_COMPILER_MSVC)
ams::Compiler::MSVC,
#elif defined(AMS_COMPILER_CLANG) || defined(AMS_COMPILER_APPLECLANG)
ams::Compiler::Clang,
#elif defined(AMS_COMPILER_GNU) || defined(AMS_COMPILER_GCC)
  ams::Compiler::GCC,
#else
  ams::Compiler::Unknown,
#endif

.compiler_version=AMS_COMPILER_VERSION,

.cpu_count=static_cast<int>(std::thread::hardware_concurrency())
};

} // ams

