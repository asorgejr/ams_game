
add_test_module(NAME test_core
  SOURCES
    test_Array.cpp
    test_Math.cpp
    test_List.cpp
    test_uuid.cpp
  DEPENDENCIES ams::core
  INCLUDE_DIRS
    ${core_INCLUDE_DIR}
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${BUILD_INTERFACE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

#if(AMS_EXCEPTIONS)
#  target_compile_definitions(test_core PRIVATE AMS_EXCEPTIONS)
#endif()