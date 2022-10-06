include(ProcessorCount)

function(change_ext)
  set(options)
  set(oneValueArgs VAR EXT)
  set(multiValueArgs FILES)
  cmake_parse_arguments(CEXT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(changed " ")
  foreach(file ${CEXT_FILES})
    get_filename_component(dir ${file} DIRECTORY)
    get_filename_component(name ${file} NAME_WE)
    list(APPEND ${changed} ${dir}/${name}${CEXT_EXT})
  endforeach()
  set(${CEXT_VAR} ${${changed}} PARENT_SCOPE)
endfunction()


function(copy_files)
  set(options)
  set(oneValueArgs VAR DEST)
  set(multiValueArgs FILES)
  cmake_parse_arguments(COPY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(new_files " ")
  foreach(file ${COPY_FILES})
    file(COPY ${file} DESTINATION ${COPY_DEST})
    get_filename_component(name ${file} NAME)
    list(APPEND ${new_files} ${COPY_DEST}/${name})
  endforeach()
  set(${COPY_VAR} ${${new_files}} PARENT_SCOPE)
endfunction()


function(find_replace)
  set(options)
  set(oneValueArgs VAR FIND REPLACE)
  set(multiValueArgs STRINGS)
  cmake_parse_arguments(FR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(changed " ")
  foreach(string ${FR_STRINGS})
    string(REPLACE ${FR_FIND} ${FR_REPLACE} new_string ${string})
    list(APPEND ${changed} ${new_string})
  endforeach()
  set(${FR_VAR} ${${changed}} PARENT_SCOPE)
endfunction()


function(rename_files)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs FILES DEST)
  cmake_parse_arguments(RENAME "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  foreach(file ${RENAME_FILES})
    get_filename_component(dir ${file} DIRECTORY)
    get_filename_component(name ${file} NAME_WE)
    file(RENAME ${file} ${RENAME_DEST}/${name}.cpp)
  endforeach()
endfunction()

# Discover platform and system information and set variables
# Options:
#   UPPERCASE - If set, all values will be in uppercase
# Variables:
#   OS_NAME
#   OS_VERSION
#   ARCH
#   COMPILER
#   COMPILER_VERSION
#   COMPILER_ID
#   CORE_COUNT
function(system_discovery)
  set(options UPPERCASE)
  set(oneValueArgs OS_NAME OS_VERSION ARCH COMPILER COMPILER_VERSION CORE_COUNT)
  set(multiValueArgs)
  cmake_parse_arguments(SD "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_sd_os_name ${CMAKE_SYSTEM_NAME})
  set(_sd_arch ${CMAKE_SYSTEM_PROCESSOR})
  if(_sd_arch STREQUAL "AMD64" OR _sd_arch STREQUAL "x86_64")
    set(_sd_arch "x64")
  endif()
  set(_sd_compiler ${CMAKE_CXX_COMPILER_ID})
  set(_sd_cpu_core_count 1)
  ProcessorCount(_sd_cpu_core_count)
  if (SD_UPPERCASE)
    string(TOUPPER ${_sd_os_name} _sd_os_name)
    string(TOUPPER ${_sd_arch} _sd_arch)
    string(TOUPPER ${_sd_compiler} _sd_compiler)
  endif()
  set(${SD_OS_NAME} ${_sd_os_name} PARENT_SCOPE)
  set(${SD_OS_VERSION} ${CMAKE_SYSTEM_VERSION} PARENT_SCOPE)
  set(${SD_ARCH} ${_sd_arch} PARENT_SCOPE)
  set(${SD_COMPILER} ${_sd_compiler} PARENT_SCOPE)
  set(${SD_COMPILER_VERSION} ${CMAKE_CXX_COMPILER_VERSION} PARENT_SCOPE)
  set(${SD_CORE_COUNT} ${_sd_cpu_core_count} PARENT_SCOPE)
endfunction()
