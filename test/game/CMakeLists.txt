add_test_module(NAME test_game
  SOURCES
    test_ApplicationAndScene.cpp
    test_ComponentAndEntity.cpp
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


add_test_module(NAME test_gfx
  SOURCES test_gfx.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS ${game_INCLUDE_DIR})


add_test_module(NAME profile_Game
  SOURCES profile_Game.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS ${game_INCLUDE_DIR})


# no graphics debugging needed after this point
remove_definitions(-DAMS_GRAPHICS_DEBUG)
add_test_module(NAME test_Log
  SOURCES
    test_Log.cpp
  DEPENDENCIES ams::game
  INCLUDE_DIRS
    ${game_INCLUDE_DIR}
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
  )


