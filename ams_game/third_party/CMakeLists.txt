set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

set(BUILD_SHARED_LIBS ON)
if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
elseif(APPLE)
  set(BUILD_SHARED_LIBS ON)
else()
  set(BUILD_SHARED_LIBS ON)
endif()

add_subdirectory(glfw)
