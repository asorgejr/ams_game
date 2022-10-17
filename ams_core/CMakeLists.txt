set(COMPONENT_NAME core)


find_package(Boost 1.75 REQUIRED)

add_subdirectory(third_party)

file(GLOB_RECURSE ${COMPONENT_NAME}_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
if (ENABLE_MODULES)
  file(GLOB_RECURSE ${COMPONENT_NAME}_MODULES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/modules/*.cppm
  )
else()
  file(GLOB_RECURSE ${COMPONENT_NAME}_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
  )
endif()


## Create library
  add_library(${COMPONENT_NAME} SHARED
  ${${COMPONENT_NAME}_SOURCES}
)
add_library(${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})

set_target_properties(${COMPONENT_NAME}
  PROPERTIES
  LINKER_LANGUAGE CXX
  VERSION ${${PROJECT_NAME}_VERSION}
)
target_link_libraries(${COMPONENT_NAME}
  PUBLIC
    Boost::boost
    gcem
)
if(ENABLE_MODULES)
  set(MODULES_LIST " ")
  files_to_interface(VAR MODULES_LIST
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/modules
    INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/include/modules
    FILES ${${COMPONENT_NAME}_MODULES})
  target_sources(${COMPONENT_NAME} PUBLIC ${MODULES_LIST})
else()
  target_include_directories(${COMPONENT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    ${GCEM_INCLUDE_DIR}
  )
endif()

if (ENABLE_MODULES)
  message(STATUS "Modules enabled")
  #    target_compile_options(${PROJECT_NAME} PRIVATE -fmodules-ts)
  target_compile_definitions(${COMPONENT_NAME}
    PUBLIC
      AMS_MODULES
  )
  #if compiler is gnu or clang and version is less than 12, use -fmodules-ts
  if(GNU OR CLANG)
    if(AMS_COMPILER_VERSION LESS 12)
      target_compile_options(${COMPONENT_NAME} PUBLIC -fmodules-ts)
      message(STATUS "Using -fmodules-ts")
    endif()
  endif()
endif()


#### INSTALLATION ####

install(TARGETS ${COMPONENT_NAME} EXPORT ${COMPONENT_NAME}-targets
  COMPONENT ${COMPONENT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT ${COMPONENT_NAME}-targets
  FILE ${PROJECT_NAME}-${COMPONENT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  COMPONENT ${COMPONENT_NAME}
)

install(FILES ${${COMPONENT_NAME}_MODULES}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/modules/${PROJECT_NAME}")
install(FILES ${${COMPONENT_NAME}_INCLUDES}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

