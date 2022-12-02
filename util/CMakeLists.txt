add_subdirectory(third_party)

option(AMS_UTIL_DEBUG "Enable debug mode (waits for input before executing)" OFF)

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
if (AMS_UTIL_DEBUG)
  target_compile_definitions(${UTIL_NAME} PRIVATE AMS_UTIL_DEBUG)
endif()

# IDE Configuration
set_property(TARGET ${UTIL_NAME} PROPERTY FOLDER "Utils")



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
if (AMS_UTIL_DEBUG)
  target_compile_definitions(${UTIL_NAME} PRIVATE AMS_UTIL_DEBUG)
endif()

# IDE Configuration
set_property(TARGET ${UTIL_NAME} PROPERTY FOLDER "Utils")