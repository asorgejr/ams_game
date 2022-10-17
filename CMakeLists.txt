#include(cmake/HunterGate.cmake)
#HunterGate(
#  URL "https://github.com/cpp-pm/hunter/archive/v0.24.7.tar.gz"
#  SHA1 "908ddcb223f25fa155315baae64ce0ab48a38bf7"
#)


option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_MODULES "c++20+ Module Library" OFF)
option(AMS_EXCEPTIONS "Enable exceptions" ON)

cmake_minimum_required(VERSION 3.16)
project(ams
  LANGUAGES C CXX
  VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_STANDARD LESS 20)
  message(FATAL_ERROR "C++20 or greater is required")
endif()

include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)
include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(cmake/Utils.cmake)

if (BUILD_TESTS)
    set(CMAKE_CXX_EXTENSIONS OFF)
    enable_testing()
endif()


if (AMS_EXCEPTIONS)
  add_compile_definitions(AMS_EXCEPTIONS)
endif()


# Discover system and platform information
set(AMS_OS "Unknown")
set(AMS_OS_VERSION 0)
set(AMS_COMPILER "Unknown")
set(AMS_COMPILER_VERSION 0)
set(AMS_ARCH "Unknown")
set(AMS_CPU_CORES 1)
set(AMS_LIBRARY_VERSION ${PROJECT_VERSION})

system_discovery(UPPERCASE
  OS_NAME AMS_OS
  OS_VERSION AMS_OS_VERSION
  COMPILER AMS_COMPILER
  COMPILER_VERSION AMS_COMPILER_VERSION
  ARCH AMS_ARCH
  CPU_CORES AMS_CPU_CORES
)


message("Configuration:
OS: ${AMS_OS} ${AMS_OS_VERSION}
Compiler: ${AMS_COMPILER} ${AMS_COMPILER_VERSION}
Architecture: ${AMS_ARCH}
CPU Cores: ${AMS_CPU_CORES}
Library Version: ${AMS_LIBRARY_VERSION}"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_subdirectory(ams_core)
add_subdirectory(ams_spatial)
add_subdirectory(ams_game)


if (BUILD_TESTS)
    add_subdirectory(test)
endif()


#### INSTALLATION ####

configure_package_config_file(cmake/${PROJECT_NAME}-config.cmake.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
