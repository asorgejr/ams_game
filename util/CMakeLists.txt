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

# symlink exe to CMAKE_SOURCE_DIR/bin
add_custom_command(TARGET ${UTIL_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
  $<TARGET_FILE:${UTIL_NAME}>
  ${CMAKE_SOURCE_DIR}/bin/${UTIL_NAME}
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

# symlink exe to CMAKE_SOURCE_DIR/bin
add_custom_command(TARGET ${UTIL_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink
  $<TARGET_FILE:${UTIL_NAME}>
  ${CMAKE_SOURCE_DIR}/bin/${UTIL_NAME}
)



