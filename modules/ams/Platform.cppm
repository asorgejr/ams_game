//
// Created by asorgejr on 10/5/2022.
//
module;
export module ams.Platform;

import <string>;

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
};

}


export const ams::SystemInfo System {
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
#elif defined(AMS_COMPILER_CLANG)
  ams::Compiler::Clang,
#elif defined(AMS_COMPILER_GNU) || defined(AMS_COMPILER_GCC)
  ams::Compiler::GCC,
#else
  ams::Compiler::Unknown,
#endif

  .compiler_version=AMS_COMPILER_VERSION,

  .cpu_count=AMS_CPU_CORES
};


#if defined(AMS_OS_WINDOWS)
#define AMS_EXPORT __declspec(dllexport)
#define AMS_IMPORT __declspec(dllimport)
#elif defined(AMS_OS_LINUX)
#define AMS_EXPORT __attribute__((visibility("default")))
#define AMS_IMPORT __attribute__((visibility("default")))
#elif defined(AMS_OS_MACOS)
#define AMS_EXPORT __attribute__((visibility("default")))
#define AMS_IMPORT __attribute__((visibility("default")))
#else
#error "Unsupported platform"
#endif

