option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_MODULES "c++20+ Module Library" OFF)

cmake_minimum_required(VERSION 3.16)
project(Game
  LANGUAGES CXX
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

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


if (BUILD_TESTS)
    set(CMAKE_CXX_EXTENSIONS OFF)
    enable_testing()
endif()

file(GLOB HEADERS
  include/ams/*.hpp
)

file(GLOB SOURCES
  src/ams/*.cpp
)

file(GLOB MODULES
  modules/ams/*.cppm
)

set(CODE " ")

if (ENABLE_MODULES)
    set(CODE ${MODULES} ${SOURCES})
else()
    set(CODE ${HEADERS} ${SOURCES})
endif()


## Create library
add_library(${PROJECT_NAME}
    ${CODE}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  LINKER_LANGUAGE CXX
  VERSION ${${PROJECT_NAME}_VERSION}
#  SOVERSION 1
#  INTERFACE_${PROJECT_NAME}_MAJOR_VERSION 1
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    glfw
)


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

target_compile_definitions(${PROJECT_NAME} PUBLIC 
    "AMS_CXX_STANDARD=${CMAKE_CXX_STANDARD}"
    "AMS_OS_${AMS_OS}"
    "AMS_OS_VERSION=\"${AMS_OS_VERSION}\""
    "AMS_COMPILER_${AMS_COMPILER}"
    "AMS_COMPILER_VERSION=\"${AMS_COMPILER_VERSION}\""
    "AMS_ARCH_${AMS_ARCH}"
    "AMS_CPU_CORES=${AMS_CPU_CORES}"
    "AMS_LIBRARY_VERSION=${AMS_LIBRARY_VERSION}"
    "AMS_VEC_SWIZZLE_METHODS"
    "GLFW_DLL"
)


message("Configuration:
OS: ${AMS_OS} ${AMS_OS_VERSION}
Compiler: ${AMS_COMPILER} ${AMS_COMPILER_VERSION}
Architecture: ${AMS_ARCH}
CPU Cores: ${AMS_CPU_CORES}
Library Version: ${AMS_LIBRARY_VERSION}
")


target_include_directories(${PROJECT_NAME}
  PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
  PRIVATE
  ${OPENGL_INCLUDE_DIRS}
)


if (ENABLE_MODULES)
    message(STATUS "Modules enabled")
#    target_compile_options(${PROJECT_NAME} PRIVATE -fmodules-ts)
    target_compile_definitions(${PROJECT_NAME} 
      PUBLIC 
        "AMS_MODULES")
    #if compiler is gnu or clang and version is less than 12, use -fmodules-ts
    if(GNU OR CLANG)
        if(AMS_COMPILER_VERSION LESS 12)
            target_compile_options(${PROJECT_NAME} PUBLIC -fmodules-ts)
            message(STATUS "Using -fmodules-ts")
        endif()
    endif()
endif()


if (BUILD_TESTS)
    add_subdirectory(test)
endif()


#### INSTALLATION ####

configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion)


install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY
  INCLUDES
  ARCHIVE
  PUBLIC_HEADER)

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ams::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
