set(EIGEN_BUILD_DOC OFF CACHE BOOL "Build the documentation")
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "Build the pkg-config file")
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Build the tests")
set(EIGEN_DEFAULT_TO_ROW_MAJOR ON CACHE BOOL "Default to row-major storage")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/eigen)