add_test_module(NAME test_game
  SOURCES
    test_Game.cpp
    test_GameUtil.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS
  ${game_INCLUDE_DIR}
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
  "$<INSTALL_INTERFACE:include>"
  )

add_test_module(NAME test_Mesh
  SOURCES
  test_Mesh.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS
  ${game_INCLUDE_DIR}
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
  "$<INSTALL_INTERFACE:include>"
)

target_compile_definitions(test_Mesh PRIVATE
  TEST_RESOURCES_DIR="${CMAKE_SOURCE_DIR}/test/resources"
)

add_test_module(NAME test_Window
  SOURCES
    test_Window.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS
  ${game_INCLUDE_DIR}
  "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
  "$<INSTALL_INTERFACE:include>"
)


add_executable(test_gfx test_gfx.cpp)
target_link_libraries(test_gfx PUBLIC ams::game)
target_include_directories(test_gfx PUBLIC ${game_INCLUDE_DIR})

add_executable(profile_Game profile_Game.cpp)
target_link_libraries(profile_Game PRIVATE ams::game)
target_include_directories(profile_Game PRIVATE ${game_INCLUDE_DIR})

