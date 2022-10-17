add_test_module(NAME test_game
  SOURCES
    test_Game.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS
  ${game_INCLUDE_DIR}
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
  "$<INSTALL_INTERFACE:include>"
  )


add_executable(test_gfx test_gfx.cpp)
target_link_libraries(test_gfx PRIVATE ams::game)
target_include_directories(test_gfx PRIVATE ${game_INCLUDE_DIR})
