option(TEST_OLC_PIXEL_GAME_ENGINE "Build the tests for the olcPixelGameEngine" OFF)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
if (WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
elseif(GNU)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
endif()
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


# CREATE A TEST MODULE
function(add_test_module)
  set(options)
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES DEPENDENCIES INCLUDE_DIRS)
  cmake_parse_arguments(TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  add_executable(${TEST_NAME} ${TEST_SOURCES})
  target_link_libraries(${TEST_NAME} PRIVATE gtest_main)
  target_link_libraries(${TEST_NAME} PRIVATE ${TEST_DEPENDENCIES})
  target_include_directories(${TEST_NAME} PRIVATE ${TEST_INCLUDE_DIRS})
  if (MODULES)
    target_compile_definitions(${TEST_NAME} PUBLIC "TEST_USE_MODULES")
  endif()
  gtest_discover_tests(${TEST_NAME})
endfunction()


add_test_module(NAME ams_game
  SOURCES
    test_Math.cpp
    test_Matrix.cpp
    test_Vec.cpp
  DEPENDENCIES Game
  INCLUDE_DIRS
    ${Game_INCLUDE_DIR}
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)


add_test_module(NAME gfx_test
  SOURCES
    test_gfx.cpp
  DEPENDENCIES Game
  INCLUDE_DIRS
    ${Game_INCLUDE_DIR}
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)


if (TEST_OLC_PIXEL_GAME_ENGINE)
  find_package(PixelGameEngine REQUIRED)
  
  add_test_module(NAME olc_test
    SOURCES test_olc.cpp
    DEPENDENCIES
      olc::PixelGameEngine
    INCLUDE_DIRS
      ${Core_INCLUDE_DIR}
      ${PixelGameEngine_INCLUDE_DIR}
      "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
      "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
      "$<INSTALL_INTERFACE:include>"
  )
endif()