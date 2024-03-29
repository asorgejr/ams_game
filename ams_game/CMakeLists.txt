set(COMPONENT_NAME game)

find_package(OpenGL REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Vulkan 1.3)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nameof CONFIG REQUIRED)


option(AMS_REQUIRE_OPENGL "Require OpenGL" OFF)
option(AMS_REQUIRE_VULKAN "Require Vulkan" OFF)
option(AMS_GRAPHICS_DEBUG "Enable graphics debug" OFF)
set(AMS_GRAPHICS_DEBUG_SEVERITY 3 CACHE STRING
"Graphics debug message severity level (0==Fatal, 1==Error, 2==Warning, 3==Info, 4==Debug, 5==Verbose).
This option is only applicable when AMS_GRAPHICS_DEBUG == ON"
)
# convert AMS_GRAPHICS_DEBUG_SEVERITY to number
string(REGEX REPLACE "[^0-9]" "" AMS_GRAPHICS_DEBUG_SEVERITY "${AMS_GRAPHICS_DEBUG_SEVERITY}")
if (NOT AMS_GRAPHICS_DEBUG_SEVERITY)
  set(AMS_GRAPHICS_DEBUG_SEVERITY 3)
endif()

if (NOT Vulkan_FOUND)
  if (AMS_REQUIRE_VULKAN)
    message(FATAL_ERROR "Vulkan not found")
  else()
    message(WARNING "Vulkan not found")
  endif()
  set(AMS_REQUIRE_OPENGL ON CACHE BOOL "Require OpenGL" FORCE)
else()
  find_path(VULKAN_HPP_INCLUDE_DIRS "vulkan/vulkan.hpp" REQUIRED)
endif()

if (AMS_ENABLE_MODULES)
  file(GLOB_RECURSE ${COMPONENT_NAME}_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ams/*.cppm
    )
else()
  file(GLOB_RECURSE ${COMPONENT_NAME}_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ams/*.hpp
    )
endif()
file(GLOB_RECURSE ${COMPONENT_NAME}_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


## Create library
add_library(game
  ${${COMPONENT_NAME}_INCLUDES}
  ${${COMPONENT_NAME}_SOURCES}
)
add_library(${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})
set_target_properties(${COMPONENT_NAME}
  PROPERTIES
  LINKER_LANGUAGE CXX
  VERSION ${${PROJECT_NAME}_VERSION}
)
# api export header
string(TOUPPER ${PROJECT_NAME}_${COMPONENT_NAME} API_MACRO_NAME)
GENERATE_EXPORT_HEADER(${COMPONENT_NAME}
  BASE_NAME ${COMPONENT_NAME}
  EXPORT_MACRO_NAME ${API_MACRO_NAME}_EXPORT
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}_${COMPONENT_NAME}_export.hpp
  STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)
# include headers as interface
target_include_directories(${COMPONENT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
if (NOT AMS_REQUIRE_OPENGL AND Vulkan_FOUND)
  target_include_directories(${COMPONENT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${Vulkan_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${VULKAN_HPP_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${VULKAN_HPP_INCLUDE_DIRS}>
  )
  target_compile_definitions(${COMPONENT_NAME}
    PUBLIC
    VULKAN_HPP_NO_CONSTRUCTORS
  )
endif()
target_compile_definitions(${COMPONENT_NAME} PUBLIC
#  AMS_CXX_STANDARD=${CMAKE_CXX_STANDARD}
#  AMS_OS_${AMS_OS}
#  AMS_OS_VERSION=\"${AMS_OS_VERSION}\"
#  AMS_COMPILER_${AMS_COMPILER}
#  AMS_COMPILER_VERSION=\"${AMS_COMPILER_VERSION}\"
#  AMS_ARCH_${AMS_ARCH}
#  AMS_CPU_COUNT=${AMS_CPU_CORES}
#  AMS_LIBRARY_VERSION=\"${AMS_LIBRARY_VERSION}\"
  GLFW_DLL
)

# configure header so defines with integer values are not wrapped in quotes. 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ams_game_sysinfo.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/ams_game_sysinfo.hpp)

add_subdirectory(third_party)

target_link_libraries(${COMPONENT_NAME}
  PUBLIC
    core
    spatial
    OpenGL::GL
    glfw
    glm::glm
  PRIVATE
    assimp::assimp
    spdlog::spdlog
    nameof::nameof
)

if (AMS_REQUIRE_OPENGL)
  target_compile_definitions(${COMPONENT_NAME}
    PUBLIC
    AMS_REQUIRE_OPENGL
  )
elseif (AMS_REQUIRE_VULKAN)
  target_compile_definitions(${COMPONENT_NAME}
    PUBLIC
    AMS_REQUIRE_VULKAN
  )
endif()
if (AMS_GRAPHICS_DEBUG)
  if (AMS_GRAPHICS_DEBUG_SEVERITY LESS 0 OR AMS_GRAPHICS_DEBUG_SEVERITY GREATER 5)
    message(FATAL_ERROR "Invalid AMS_GRAPHICS_DEBUG_SEVERITY value")
  endif()
  target_compile_definitions(${COMPONENT_NAME}
    PUBLIC
      AMS_GRAPHICS_DEBUG
      AMS_GRAPHICS_DEBUG_SEVERITY=${AMS_GRAPHICS_DEBUG_SEVERITY}
)
endif()



#### INSTALLATION ####

install(TARGETS ${COMPONENT_NAME} EXPORT ${COMPONENT_NAME}-targets
  COMPONENT ${COMPONENT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT ${COMPONENT_NAME}-targets
  FILE ${PROJECT_NAME}-${COMPONENT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  COMPONENT ${COMPONENT_NAME}
)

install(FILES ${${COMPONENT_NAME}_INCLUDES}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
