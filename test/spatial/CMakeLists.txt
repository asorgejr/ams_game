

add_test_module(NAME test_spatial
  SOURCES
    test_Matrix.cpp
    test_Vec.cpp
    test_Quaternion.cpp
  DEPENDENCIES
    ams::spatial
  INCLUDE_DIRS
    ${spatial_INCLUDE_DIR}
)

add_executable(testv_spatial testv_matrix.cpp)
target_link_libraries(testv_spatial PRIVATE
  ams::spatial
)

#target_link_options(test_spatial PRIVATE
#  "$<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>"
#  )

if (TEST_OLC_PIXEL_GAME_ENGINE)
  find_package(PixelGameEngine REQUIRED)
  add_test_module(NAME olc_test
    SOURCES test_olc.cpp
    DEPENDENCIES
      olc::PixelGameEngine
    INCLUDE_DIRS
      ${core_INCLUDE_DIR}
      ${PixelGameEngine_INCLUDE_DIR}
  )
endif()
