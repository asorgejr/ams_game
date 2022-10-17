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
  target_link_libraries(${TEST_NAME} PUBLIC ${TEST_DEPENDENCIES})
  target_include_directories(${TEST_NAME} PUBLIC ${TEST_INCLUDE_DIRS})
  target_link_libraries(${TEST_NAME} PRIVATE gtest_main)
  if (MODULES)
    target_compile_definitions(${TEST_NAME} PUBLIC "TEST_USE_MODULES")
  endif()
  gtest_discover_tests(${TEST_NAME})
endfunction()

add_subdirectory(core)
add_subdirectory(spatial)
add_subdirectory(game)

