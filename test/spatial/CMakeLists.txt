

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


add_test_module(NAME testv_spatial
  SOURCES testv_matrix.cpp
  DEPENDENCIES ams::spatial
  INCLUDE_DIRS ${spatial_INCLUDE_DIR})


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
