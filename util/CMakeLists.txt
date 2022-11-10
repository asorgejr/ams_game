add_subdirectory(third_party)

set(UTIL_NAME convmesh)
add_executable(${UTIL_NAME} ${UTIL_NAME}.cpp)
target_link_libraries(${UTIL_NAME}
  PRIVATE
    ams::game
    argparse::argparse
)
target_include_directories(${UTIL_NAME}
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

set(UTIL_NAME meshpp)
add_executable(${UTIL_NAME} ${UTIL_NAME}.cpp
  BoxComment.hpp)
target_link_libraries(${UTIL_NAME}
  PRIVATE
  ams::game
  argparse::argparse
)
target_include_directories(${UTIL_NAME}
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
