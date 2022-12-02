#include(cmake/HunterGate.cmake)
#HunterGate(
#  URL "https://github.com/cpp-pm/hunter/archive/v0.24.7.tar.gz"
#  SHA1 "908ddcb223f25fa155315baae64ce0ab48a38bf7"
#)
option(AMS_BUILD_TESTS "Build tests" OFF)
option(AMS_ENABLE_MODULES "c++20+ Module Library" OFF)
option(AMS_EXCEPTIONS "Enable exceptions" ON)
option(AMS_NEGATIVE_INDEXING "Enable negative indexing for ams container types" OFF)
option(AMS_ENABLE_BOOST "Enable Boost" OFF)
option(AMS_CMAKE_DEBUG "Outputs CMake debug information" OFF)

cmake_minimum_required(VERSION 3.23)
project(ams
  LANGUAGES CXX
  VERSION 0.1
)

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_CXX_STANDARD LESS 20)
  ams_log(FATAL_ERROR "C++20 or greater is required")
endif()

include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)
include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(cmake/Utils.cmake)
include(cmake/ModulePlatformCheck.cmake)
include(cmake/dict.cmake)

dict(SET _test_dict)
message("[test] SET return default_dict: '${_test_dict}'")
dict(SET _test_dict KEY "test-key" VALUE "strval")
message("[test] kvp str val: '${_test_dict}'")


return()

if (AMS_BUILD_TESTS)
  set(CMAKE_CXX_EXTENSIONS OFF)
  enable_testing()
endif()


if (AMS_EXCEPTIONS)
  add_compile_definitions(AMS_EXCEPTIONS)
endif()

if (AMS_CMAKE_DEBUG)
  set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)
endif()

check_compiler_can_compile_modules(_modules_supported)

if (_modules_supported)
  add_compile_definitions(AMS_MODULES)
  # enable cmake experimental features
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
  if (WIN32)
#    include(msvc_modules.cmake)
  elseif(GNU)
    include(gcc_modules.cmake)
  endif()
  ams_log(STATUS "C++ Modules enabled")
  if (CMAKE_CXX_STANDARD GREATER_EQUAL 23)
    add_compile_definitions(AMS_MODULES_STD)
  endif()
endif()

# IDE Configuration
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")


# Discover system and platform information
set(AMS_OS "Unknown")
set(AMS_OS_VERSION 0)
set(AMS_COMPILER "Unknown")
set(AMS_COMPILER_VERSION 0)
set(AMS_OS_ARCH "Unknown")
set(AMS_TARGET_ARCH "Unknown")
set(AMS_CPU_CORES 1)
set(AMS_LIBRARY_VERSION ${PROJECT_VERSION})

system_discovery(UPPERCASE
  OS_NAME AMS_OS
  OS_VERSION AMS_OS_VERSION
  COMPILER AMS_COMPILER
  COMPILER_VERSION AMS_COMPILER_VERSION
  OS_ARCH AMS_OS_ARCH
  TARGET_ARCH AMS_TARGET_ARCH
  CPU_CORES AMS_CPU_CORES
)

ams_log(DEBUG "Configuration:
OS: ${AMS_OS} ${AMS_OS_VERSION}
Generator: ${CMAKE_GENERATOR}
Compiler: ${AMS_COMPILER} ${AMS_COMPILER_VERSION}
System Architecture: ${AMS_OS_ARCH}
Target Architecture: ${AMS_TARGET_ARCH}
CPU Cores: ${AMS_CPU_CORES}
Library Version: ${AMS_LIBRARY_VERSION}
C++ Standard: ${CMAKE_CXX_STANDARD}"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_subdirectory(ams_core)
add_subdirectory(ams_spatial)
add_subdirectory(ams_game)


if (AMS_BUILD_TESTS)
  ams_log(STATUS "Building tests")
  add_subdirectory(test)
endif()


add_subdirectory(util)



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
