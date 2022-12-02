include(ProcessorCount)


#[[
  ams_log([INVOCATION|TRACE|NOTRACE <trace-kind>]
          [FATAL_ERROR|ERROR|WARNING|NOTICE|STATUS|DEBUG|VERBOSE <severity-level>]
          <message> [OVERRIDE_SEVERITY <severity-level>])
    Logs a message custom formatted for this project.
    Arguments:
      <trace-kind> -- The kind of trace to log. Options are:
        INVOCATION (default)* -- Logs the file:line where ams_log() was called. (Default for most <severity-level> options.)
        TRACE -- Logs the file:line where ams_log() was called, and the call stack.
        NOTRACE -- Disables tracing for the current message.
      <severity-level> -- The severity level of the message. Options are:
        FATAL_ERROR -- Logs a fatal error message.
        ERROR -- Error information. If <trace-kind> is not specified, defaults to TRACE.
        WARNING -- Warning information. If <trace-kind> is not specified, defaults to TRACE.
        NOTICE -- Notice information. If <trace-kind> is not specified, defaults to NOTRACE.
        STATUS (default) -- Status information.
        DEBUG -- Debugging information.
        VERBOSE -- TMI. If <trace-kind> is not specified, defaults to NOTRACE.
      <message> -- The message to log.
      OVERRIDE_SEVERITY <severity-level> -- The severity level to set for the current message. If SEVERITY_OVERRIDE <severity-level>
            are found as the last arguments, the message filtering level specified by CMAKE_MESSAGE_LOG_LEVEL will
            temporarily be overridden with <severity-level>. This is useful for function-level filtering of messages.
  ams_log(<configuration>)
    Configures the logger with particular settings. These settings are stored to CACHE.
    Arguments:
      <configuration> -- A JSON string of key-value-pairs to configure the logger.
]]
function(ams_log)
  if(NOT ams_log_FAIL_VERSION_CHECK AND CMAKE_VERSION VERSION_LESS 3.19)
    message("ams_log is not supported in CMake < 3.19. Message: '${ARGV}'")
    set(ams_log_FAIL_VERSION_CHECK TRUE CACHE INTERNAL "")
  endif()
  set(_sev_level "STATUS")
  set(_trc_level "INVOCATION")
  set(_msg "")
  set(_SEV_LEVELS_CMAKE "FATAL_ERROR" "SEND_ERROR" "WARNING" "AUTHOR_WARNING" "DEPRECATION" "NOTICE" "STATUS" "VERBOSE" "DEBUG" "TRACE")
  set(_SEV_LEVELS ${_SEV_LEVELS_CMAKE}) # non-cmake commands may be added here eventually.
  set(_TRC_LEVELS "TRACE" "NOTRACE" "INVOCATION")
  set(_SEV_LEVELS_PRINT_MAP "{
    \"FATAL_ERROR\": \"FATAL ERROR\",
    \"SEND_ERROR\": \"ERROR\",
    \"ERROR\": \"ERROR\",
    \"WARNING\": \"WARNING\",
    \"AUTHOR_WARNING\": \"AUTHOR WARNING\",
    \"DEPRECATION\": \"DEPRECATION\",
    \"NOTICE\": \"NOTICE\",
    \"STATUS\": \"STATUS\",
    \"DEBUG\": \"DEBUG\",
    \"VERBOSE\": \"VERBOSE\"
  }")
  string(JOIN "|" _SEV_LEVEL_OPTIONS_RGX "${_SEV_LEVELS}")
  string(JOIN "|" _TRC_LEVEL_OPTIONS_RGX "${_TRC_LEVELS}")
  # Severity order of precidence: FATAL_ERROR, ERROR, WARNING, STATUS, VERBOSE, DEBUG
  # Trace order of precidence: TRACE, NOTRACE, INVOCATION
  if(NOT ARGV) # empty invocation
    return()
  endif()
  set(_found_trclvl FALSE)
  set(_found_sevlvl FALSE)
  list(GET ARGV 0 _arg)
  string(TOUPPER "${_arg}" _arg) # allow case-insensitivity because option is position-dependent.
  if(_arg IN_LIST _TRC_LEVELS)
    set(_trc_level ${ARGV0})
    set(_found_trclvl TRUE)
    list(REMOVE_AT ARGV 0)
  elseif(_arg IN_LIST _SEV_LEVELS)
    set(_sev_level ${ARGV0})
    set(_found_sevlvl TRUE)
    list(REMOVE_AT ARGV 0)
  endif()
  if(NOT ARGV) # option specified with no message.
    message(DEBUG "${CMAKE_CURRENT_FUNCTION}: Invalid arguments: '${ARGV}'")
    return()
  endif()
  
  list(GET ARGV 0 _arg)
  string(TOUPPER "${_arg}" _arg)
  set(_elem1 "")
  if(NOT _found_sevlvl AND _arg IN_LIST _SEV_LEVELS)
    set(_trc_level ${ARGV0})
    set(_found_trclvl TRUE)
    set(_elem1 ${ARGV0})
    list(REMOVE_AT ARGV 0)
  elseif(NOT _found_trclvl AND _arg IN_LIST _TRC_LEVELS)
    set(_sev_level ${ARGV0})
    set(_found_sevlvl TRUE)
    set(_elem1 ${ARGV0})
    list(REMOVE_AT ARGV 0)
  endif()
  # if ERROR or WARNING, set _trc_level to TRACE
  if(_sev_level MATCHES "^(FATAL_ERROR|SEND_ERROR|WARNING|AUTHOR_WARNING)$" AND NOT _found_trclvl)
    set(_trc_level "TRACE")
  elseif(NOT _found_trclvl AND _sev_level MATCHES "^VERBOSE$")
    set(_trc_level "NOTRACE")
  endif()
  
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.25)
    cmake_language(GET_MESSAGE_LOG_LEVEL _cmake_global_sev_level)
    if(NOT CMAKE_MESSAGE_LOG_LEVEL OR CMAKE_MESSAGE_LOG_LEVEL STREQUAL "NOTSET")
      set(CMAKE_MESSAGE_LOG_LEVEL ${_cmake_global_sev_level} CACHE STRING "The default severity level for messages." FORCE)
    endif()
  endif()
  
  list(FIND _SEV_LEVELS_CMAKE "${CMAKE_MESSAGE_LOG_LEVEL}" _cmake_global_sev_level_idx)
  if(_cmake_global_sev_level_idx EQUAL -1)
    if(NOT CMAKE_MESSAGE_LOG_LEVEL)
      set(CMAKE_MESSAGE_LOG_LEVEL "STATUS" CACHE STRING "The default severity level for messages." FORCE)
    else() # CMake added features recently...
      message(AUTHOR_WARNING "${CMAKE_CURRENT_FUNCTION}: Unknown CMAKE_MESSAGE_LOG_LEVEL '${CMAKE_MESSAGE_LOG_LEVEL}'. Defaulting to 'STATUS'.  "
              "This is a bug, please report this message.  CMAKE_VERSION: '${CMAKE_VERSION}'; OS: '${CMAKE_HOST_SYSTEM_NAME}'.")
      set(CMAKE_MESSAGE_LOG_LEVEL "STATUS" CACHE STRING "The default severity level for messages." FORCE)
    endif()
  endif()
  
  set(_cmake_msg_ctx_tmp ${CMAKE_MESSAGE_CONTEXT})
  set(_cmake_msg_ctx_show_tmp ${CMAKE_MESSAGE_CONTEXT_SHOW})
  set(_cmake_msg_lvl_tmp ${CMAKE_MESSAGE_LOG_LEVEL})
  
  list(LENGTH ARGV _arg_size)
  math(EXPR _arg_size_minus_two "${_arg_size} - 2")
  list(GET ARGV ${_arg_size_minus_two} _arg)
  if(_arg STREQUAL "OVERRIDE_SEVERITY")
    math(EXPR _arg_size_minus_one "${_arg_size} - 1")
    list(GET ARGV ${_arg_size_minus_one} _arg)
    string(TOUPPER "${_arg}" _arg)
    if(_arg IN_LIST _SEV_LEVELS_CMAKE)
      set(CMAKE_MESSAGE_LOG_LEVEL ${_arg})
      list(REMOVE_AT ARGV ${_arg_size_minus_one})
      list(REMOVE_AT ARGV ${_arg_size_minus_two})
    endif()
  endif()
  
  list(FIND _SEV_LEVELS_CMAKE "${CMAKE_MESSAGE_LOG_LEVEL}" _cmake_global_sev_level_idx) # find index again in case OVERRIDE_SEVERITY was specified
  list(FIND _SEV_LEVELS_CMAKE ${_sev_level} _sev_level_cmake_idx)
  
  if(_sev_level_cmake_idx EQUAL -1) # should theoretically never happen, but just in case
    message(AUTHOR_WARNING "${CMAKE_CURRENT_FUNCTION} error: Unknown severity level '${_sev_level}'. "
            "This is a bug, please report this message.  CMAKE_VERSION: '${CMAKE_VERSION}'; OS: '${CMAKE_HOST_SYSTEM_NAME}'."
            "\nMessage: '${ARGV}'")
    return()
  endif()
  
  if(NOT ARGV AND _found_sevlvl AND _found_trclvl)
    if(CMAKE_MESSAGE_LOG_LEVEL STREQUAL "DEBUG")
      message(DEBUG "ams_log parsing error: Invalid arguments.")
    endif()
    message(${_sev_level} "${_elem1}")
    return()
  endif()
  
  if(_sev_level_cmake_idx GREATER _cmake_global_sev_level_idx) # Message Severity is less important than minimum global setting
    return()
  endif()
  
  set(CMAKE_MESSAGE_CONTEXT_SHOW ON)
  set(CMAKE_MESSAGE_CONTEXT "${PROJECT_NAME}" "${_sev_level}")
  set(_msg "${ARGV}")
  if(_msg MATCHES "\n")
    string(REGEX REPLACE "\n" ";" _msg "${_msg}")
    set(_ctx_len 2)
    string(JOIN "." ctx_str ${CMAKE_MESSAGE_CONTEXT})
    string(LENGTH ${ctx_str} _ctx_len)
    math(EXPR _ctx_len "${_ctx_len} + 2 + 2")
    string(REPEAT " " ${_ctx_len} _default_indent)
  endif()
  # _msg gets modified after this point
  if(_trc_level STREQUAL "INVOCATION")
    set(_msg "${_msg} << at ${CMAKE_CURRENT_LIST_FILE}") #:${CMAKE_CURRENT_LIST_LINE}") doesn't work when deep stack'
  endif()
  
  # BEGIN PRINT SECTION
  if(_sev_level MATCHES "^(FATAL_ERROR|SEND_ERROR)$")
    set(_indent "")
    foreach(msgline ${_msg})
      message("${_indent}${msgline}")
      set(CMAKE_MESSAGE_CONTEXT_SHOW OFF)
      set(_indent "${_default_indent}")
    endforeach()
    set(CMAKE_MESSAGE_CONTEXT_SHOW OFF)
    set(_trc_level "TRACE")
  elseif(_sev_level MATCHES "^(STATUS|VERBOSE)$")
    set(_indent "-- ")
    foreach(msgline ${_msg})
      message("${_indent}${msgline}")
      set(_indent "    ")
      set(CMAKE_MESSAGE_CONTEXT_SHOW OFF)
    endforeach()
  else()
    set(_indent "")
    foreach(msgline ${_msg})
      message("${_indent}${msgline}")
      set(CMAKE_MESSAGE_CONTEXT_SHOW OFF)
      set(_indent "${_default_indent}")
    endforeach()
  endif()
  # END PRINT SECTION
  if(_trc_level STREQUAL "TRACE")
    set(CMAKE_MESSAGE_CONTEXT_SHOW OFF)
    set(CMAKE_MESSAGE_LOG_LEVEL "TRACE" CACHE STRING "The default severity level for messages." FORCE)
    list(APPEND CMAKE_MESSAGE_INDENT ${_default_indent})
    message(AUTHOR_WARNING "")
    list(POP_BACK CMAKE_MESSAGE_INDENT)
    if(_sev_level STREQUAL "FATAL_ERROR")
      set(CMAKE_MESSAGE_LOG_LEVEL ${_cmake_msg_lvl_tmp} CACHE STRING "The default severity level for messages." FORCE)
      message(FATAL_ERROR)
    endif()
  endif()
  set(CMAKE_MESSAGE_CONTEXT_SHOW ${_cmake_msg_ctx_show_tmp})
  set(CMAKE_MESSAGE_CONTEXT ${_cmake_msg_ctx_tmp})
  set(CMAKE_MESSAGE_LOG_LEVEL ${_cmake_msg_lvl_tmp} CACHE STRING "The default severity level for messages." FORCE)
endfunction()

  

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

function(files_to_interface_d)
  set(options)
  set(oneValueArgs VAR SOURCE_DIR INSTALL_DIR)
  set(multiValueArgs FILES)
  cmake_parse_arguments(FTI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT FTI_SOURCE_DIR)
    message(FATAL_ERROR "files_to_interface: SOURCE_DIR not specified")
  endif()
  if(NOT FTI_INSTALL_DIR)
    message(FATAL_ERROR "files_to_interface: INSTALL_DIR not specified")
  endif()
  set(changed " ")
  foreach(file ${FTI_FILES})
    get_filename_component(dir ${file} DIRECTORY)
    get_filename_component(name ${file} NAME)
    # warn if file is not in source dir. String path replacement will not work if true.
    string(FIND ${dir} ${FTI_SOURCE_DIR} index)
    if(index EQUAL -1)
      message(WARNING "files_to_interface: '${file}' is not in source dir '${FTI_SOURCE_DIR}'")
    endif()
    list(APPEND ${changed} $<BUILD_INTERFACE:${dir}/${name}>)
    set(idir " ")
    string(REPLACE ${FTI_SOURCE_DIR} ${FTI_INSTALL_DIR} idir ${dir})
    list(APPEND ${changed} $<INSTALL_INTERFACE:${idir}/${name}>)
  endforeach()
  set(${FTI_VAR} ${${changed}} PARENT_SCOPE)
endfunction()


#[[
  dirset(<var> [DIRS <dir>...] [FILES <file>...])
   Set <var> to a list of files specified in FILES (but only if they are found on the filesystem).
   Files which have an absolute path and exist on the filesystem will be added to <var> with no
   modifications to the path. If the file is a relative path, it will be checked against each dir
   in DIRS. If a match is found on the filesystem, the file will be added to <var> with its
   respective directory prepended to the path.
   Arguments:
     <var> - The variable to set
     DIRS - A list of directories to check relative files against
     FILES - A list of files to check
]]
function(dirset)
set(options)
  # The first argument is the variable to set.
  set(multiValueArgs DIRS FILES)
  cmake_parse_arguments(DS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  # var name:
  set(varname ${DS_UNPARSED_ARGUMENTS})
  list(GET varname 0 varname)
  if(NOT DS_DIRS OR NOT DS_FILES)
    message(FATAL_ERROR "dirset: DIRS and FILES must be specified")
  endif()
  set(_ds_files)
  foreach(dir ${DS_DIRS})
    if(NOT IS_ABSOLUTE ${dir})
      get_filename_component(dir ${CMAKE_CURRENT_SOURCE_DIR}/${dir} ABSOLUTE)
    endif()
    foreach(file ${DS_FILES})
      if(IS_ABSOLUTE ${file} AND EXISTS ${file})
        cmake_path(SET file NORMALIZE "${file}")
        list(APPEND _ds_files ${file}) # file does not need processing
        continue()
      endif()
      cmake_path(GET file RELATIVE_PART file)
      set(_try_file ${dir}/${file})
      if(EXISTS ${_try_file})
        cmake_path(SET _try_file NORMALIZE "${_try_file}")
        list(APPEND _ds_files ${_try_file})
        continue()
      else()
        message(WARNING "dirset: ${_try_file} does not exist")
      endif()
    endforeach()
  endforeach()
  set(${varname} ${_ds_files} PARENT_SCOPE)
endfunction()


#[[
  files_to_interface(<var> INSTALL_DIR <dir> BASE_DIRS <dir>... FILES <file>...)
    Takes a list of FILES which are relative to the BASE_DIRS and converts them to
    $<BUILD_INTERFACE:<base-dir>/<file>> and $<INSTALL_INTERFACE:<install-dir>/<file>>.
  Arguments:
    <var> - The name of the variable to set.
    INSTALL_DIR - The install directory to use for the INSTALL_INTERFACE.
    BASE_DIRS - The base directories to use for the BUILD_INTERFACE.
    FILES - The list of files to convert.
]]
function(files_to_interface)
  set(options)
  set(oneValueArgs INSTALL_DIR)
  set(multiValueArgs BASE_DIRS FILES)
  cmake_parse_arguments(FTI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_fti_varname ${ARGV0})
  if(NOT FTI_INSTALL_DIR)
    message(FATAL_ERROR "files_to_interface: INSTALL_DIR not specified")
  endif()
  if(NOT FTI_BASE_DIRS)
    message(FATAL_ERROR "files_to_interface: BASE_DIRS not specified")
  endif()
  set(changed " ")
  foreach(file ${FTI_FILES})
    # warn if file is not in source dir. String path replacement will not work if true.
    set(found FALSE)
    foreach(base_dir ${FTI_BASE_DIRS})
      cmake_path(IS_PREFIX base_dir ${file} NORMALIZE _dir_is_base)
      if(_dir_is_base)
        set(found TRUE)
        cmake_path(RELATIVE_PATH file BASE_DIRECTORY ${base_dir} OUTPUT_VARIABLE _rel_file)
        list(APPEND ${changed} $<BUILD_INTERFACE:${base_dir}/${_rel_file}>)
        list(APPEND ${changed} $<INSTALL_INTERFACE:${FTI_INSTALL_DIR}/${_rel_file}>)
        break()
      endif()
    endforeach()
    if(NOT found)
      message(WARNING "files_to_interface: '${file}' is not in any of the base dirs: '${_fti_nrm_base_dirs}'")
    endif()
  endforeach()
  set(${_fti_varname} ${${changed}} PARENT_SCOPE)
endfunction()


function(parse_os_name)
  set(options)
  set(oneValueArgs VAR)
  set(multiValueArgs)
  cmake_parse_arguments(OSNAME "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(${OSNAME_VAR} "macos" PARENT_SCOPE)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(${OSNAME_VAR} "linux" PARENT_SCOPE)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(${OSNAME_VAR} "windows" PARENT_SCOPE)
  else()
    set(${OSNAME_VAR} "unknown" PARENT_SCOPE)
  endif()
endfunction()


function(get_target_arch)
  set(options)
  set(oneValueArgs VAR)
  set(multiValueArgs)
  cmake_parse_arguments(TARGET_ARCH "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    set(${TARGET_ARCH_VAR} "x86_64" PARENT_SCOPE)
  elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "i386")
    set(${TARGET_ARCH_VAR} "i386" PARENT_SCOPE)
  elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set(${TARGET_ARCH_VAR} "arm" PARENT_SCOPE)
  else()
    set(${TARGET_ARCH_VAR} "unknown" PARENT_SCOPE)
  endif()
endfunction()


#[[
  Discover platform and system information and set variables
  Options:
    UPPERCASE - If set, all values will be in uppercase
  Arguments:
    OS_NAME <os-name-var>
    OS_VERSION <os-version-var>
    ARCH <arch-var>
    COMPILER <compiler-var>
    COMPILER_VERSION <compiler-version-var>
    COMPILER_ID <compiler-id-var>
    CORE_COUNT <core-count-var>
]]
function(system_discovery)
  set(options UPPERCASE)
  set(oneValueArgs OS_NAME OS_VERSION OS_ARCH TARGET_ARCH COMPILER COMPILER_VERSION CPU_CORES)
  set(multiValueArgs)
  cmake_parse_arguments(SD "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_sd_os_name " ")
  parse_os_name(VAR _sd_os_name)
  set(_sd_os_arch ${CMAKE_HOST_SYSTEM_PROCESSOR})
  if(_sd_os_arch STREQUAL "AMD64" OR _sd_os_arch STREQUAL "x86_64")
    set(_sd_os_arch "x64")
  endif()
  set(_sd_target_arch ${CMAKE_SYSTEM_PROCESSOR})
  if(_sd_target_arch STREQUAL "AMD64" OR _sd_target_arch STREQUAL "x86_64")
    set(_sd_target_arch "x64")
  endif()
  set(_sd_compiler ${CMAKE_CXX_COMPILER_ID})
  set(_sd_cpu_core_count 1)
  ProcessorCount(_sd_cpu_core_count)
  if (SD_UPPERCASE)
    string(TOUPPER ${_sd_os_name} _sd_os_name)
    string(TOUPPER ${_sd_os_arch} _sd_os_arch)
    string(TOUPPER ${_sd_target_arch} _sd_target_arch)
    string(TOUPPER ${_sd_compiler} _sd_compiler)
  endif()
  set(${SD_OS_NAME} ${_sd_os_name} PARENT_SCOPE)
  set(${SD_OS_VERSION} ${CMAKE_SYSTEM_VERSION} PARENT_SCOPE)
  set(${SD_OS_ARCH} ${_sd_os_arch} PARENT_SCOPE)
  set(${SD_TARGET_ARCH} ${_sd_target_arch} PARENT_SCOPE)
  set(${SD_COMPILER} ${_sd_compiler} PARENT_SCOPE)
  set(${SD_COMPILER_VERSION} ${CMAKE_CXX_COMPILER_VERSION} PARENT_SCOPE)
  set(${SD_CPU_CORES} ${_sd_cpu_core_count} PARENT_SCOPE)
endfunction()


#[[
  itarget_sources(<target> <PRIVATE|PUBLIC|INTERFACE>
                  FILE_SET <file-set-name> [NAME_PREFIX <name>][NAME_SUFFIX <name>]
                  TYPE <type> INSTALL_DIR <dir> BASE_DIRS <dir>... FILES <file>...)
]]
function(itarget_sources)
  set(options)
  set(oneValueArgs FILE_SET NAME_PREFIX NAME_SUFFIX TYPE INSTALL_DIR)
  set(multiValueArgs BASE_DIRS FILES)
  cmake_parse_arguments(IT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_it_target_name ${ARGV0})
  set(_it_scope ${ARGV1})
  if(IT_NAME_PREFIX)
    set(_it_name_prefix "${IT_NAME_PREFIX}")
  else()
    set(_it_name_prefix "")
  endif()
  if(IT_NAME_SUFFIX)
    set(_it_name_suffix "${IT_NAME_SUFFIX}")
  else()
    set(_it_name_suffix "${IT_TYPE}")
  endif()
  files_to_interface(_it_files INSTALL_DIR "${IT_INSTALL_DIR}" BASE_DIRS ${IT_BASE_DIRS} FILES ${IT_FILES})
  set(_it_file_set "${_it_name_prefix}${IT_FILE_SET}${_it_name_suffix}")
  target_sources(${_it_target_name} ${_it_scope}
    FILE_SET ${_it_file_set}
      TYPE ${IT_TYPE} BASE_DIRS ${IT_BASE_DIRS} FILES ${_it_files})
  message(DEBUG "itarget_sources: created FILE_SET '${_it_file_set}' with sources: '${_it_files}'")
endfunction()

    

#[[
  module_sources(<target> [NAME_PREFIX <name>] [INSTALL_PREFIX <dir>]
                 [INCLUDE_DIRS <dir>...][PUBLIC_DIRS <dir>...][PRIVATE_DIRS <dir>...]
                 [HEADERS <file>...][HEADER_UNITS <file>...][PUBLIC_MODULES <file>...][PRIVATE_MODULES <file>...])
    Add source files to a target. The source files are specified in the same way as the
    dirset() function. The NAME_PREFIX will prepend the specified prefix to the FILE_SET name.
    HEADERS, HEADER_UNITS and MODULE_INTERFACES will be scanned against PUBLIC_DIRS as a base path.
    MODULES will be scanned against PRIVATE_DIRS as a base path.
    Outputted file set variable(s) will be formatted as <name_prefix><target>_<TYPE(of fileset)>
  Arguments:
    NAME_PREFIX - Prefix to prepend to the file set name
    INSTALL_PREFIX - The directory to use for $<INSTALL_INTERFACE>
    INCLUDE_DIRS - Directories to search for headers
    PUBLIC_DIRS - Directories to search for header units and public modules
    PRIVATE_DIRS - Directories to search for private modules
    HEADERS - Header files to add to the target
    HEADER_UNITS - Header units to add to the target
    PUBLIC_MODULES - Public modules to add to the target
    PRIVATE_MODULES - Private modules to add to the target
  Options:
    MSBUILD - Use the MSBuild spec for targeting modules
]]
function(module_sources)
  set(options MSBUILD)
  set(oneValueArgs NAME_PREFIX INSTALL_ROOT)
  set(multiValueArgs PUBLIC_DIRS INCLUDE_DIRS PRIVATE_DIRS
      HEADERS HEADER_UNITS PUBLIC_MODULES PRIVATE_MODULES)
  cmake_parse_arguments(MS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT MS_NAME_PREFIX)
    set(MS_NAME_PREFIX "")
  endif()
  if(NOT MS_INSTALL_PREFIX)
    set(MS_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
  endif()
  set(_ms_target ${MS_UNPARSED_ARGUMENTS})
  list(GET _ms_target 0 _ms_target)
  if(MS_HEADERS)
    if(NOT MS_INCLUDE_DIRS)
      message(FATAL_ERROR "module_sources: HEADERS specified but INCLUDE_DIRS not specified")
    endif()
    itarget_sources(${_ms_target} PUBLIC NAME_PREFIX ${MS_NAME_PREFIX} NAME_SUFFIX _HEADERS
                    FILE_SET ${_ms_target} TYPE HEADERS
                    INSTALL_DIR "${MS_INSTALL_PREFIX}/include"
                    BASE_DIRS ${MS_INCLUDE_DIRS} FILES ${MS_HEADERS})
  endif()
  if(MS_HEADER_UNITS)
    if(NOT MS_PUBLIC_DIRS)
      message(FATAL_ERROR "module_sources: HEADER_UNITS specified but PUBLIC_DIRS not specified")
    endif()
    itarget_sources(${_ms_target} PUBLIC NAME_PREFIX ${MS_NAME_PREFIX} NAME_SUFFIX _HEADER_UNITS
                    FILE_SET ${_ms_target} TYPE CXX_MODULE_HEADER_UNITS
                    INSTALL_DIR "${MS_INSTALL_PREFIX}/include"
                    BASE_DIRS ${MS_PUBLIC_DIRS} FILES ${MS_HEADER_UNITS})
  endif()
  if(MS_PUBLIC_MODULES)
    if(NOT MS_PUBLIC_DIRS)
      message(FATAL_ERROR "module_sources: PUBLIC_MODULES specified but PUBLIC_DIRS not specified")
    endif()
    itarget_sources(${_ms_target} PUBLIC NAME_PREFIX ${MS_NAME_PREFIX} NAME_SUFFIX _PUBLIC_MODULES
                    FILE_SET ${_ms_target} TYPE CXX_MODULES
                    INSTALL_DIR "${MS_INSTALL_PREFIX}/public"
                    BASE_DIRS ${MS_PUBLIC_DIRS} FILES ${MS_PUBLIC_MODULES})
  endif()
  if(MS_PRIVATE_MODULES)
    if(NOT MS_PRIVATE_DIRS)
      message(FATAL_ERROR "module_sources: PRIVATE_MODULES specified but PRIVATE_DIRS not specified")
    endif()
    itarget_sources(${_ms_target} PUBLIC NAME_PREFIX ${MS_NAME_PREFIX} NAME_SUFFIX _PRIVATE_MODULES
                    FILE_SET ${_ms_target} TYPE CXX_MODULES
                    INSTALL_DIR "${MS_INSTALL_PREFIX}/src"
                    BASE_DIRS ${MS_PRIVATE_DIRS} FILES ${MS_PRIVATE_MODULES})
  endif()
endfunction()


#[[
  get_file_set_install_command_args(<out-var> FILE_SET_ARGS <args>...)
    Get the install command arguments for a file set command list
  Arguments:
    out_var - The variable to output the install command arguments to as a JSON string
    FILE_SET_ARGS - The list of file set commands to get the install command arguments for
]]
function(get_file_set_install_command_args)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs FILE_SET_ARGS)
  cmake_parse_arguments(GFS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_varname ${ARGV0})
  string(_gfs_out "{}")
  list(LENGTH GFS_FILE_SET_ARGS _gfs_size)
  foreach(_idx RANGE 0 ${_gfs_size})
    math(EXPR _gfs_last_idx "${_idx} - 1")
    ams_log(VERBOSE "idx: ${_idx} last_idx: ${_gfs_last_idx}")
    list(GET GFS_FILE_SET_ARGS ${_gfs_last_idx} _gfs_last_param)
    if(_gfs_last_param STREQUAL "FILE_SET")
      list(GET GFS_FILE_SET_ARGS ${_idx} _gfs_param)
      string(JSON _gfs_out SET _gfs_out "FILE_SET" ${_gfs_param})
    elseif(_gfs_last_param STREQUAL "DESTINATION")
      list(GET GFS_FILE_SET_ARGS ${_idx} _gfs_param)
      string(JSON _gfs_out SET _gfs_out "DESTINATION" ${_gfs_param})
    endif()
  endforeach()
  set(${_varname} ${_gfs_out} PARENT_SCOPE)
endfunction()
  

#[[
  module_install(VAR <variable-to-modify> TARGETS <target> EXPORT <export-target-name>
                 [DESTINATIONS <destination-declarations>...]
                 [INSTALL_FILE_SET <TRUE|FALSE>][FILE_SET <file-sets>]
                 [INSTALL][LOG_LEVEL <NONE|DEBUG|VERBOSE>])
  Builds the parameter list for the install() command. This allows for a more procedural
  approach to invoking install().
  Arguments:
    VAR (required) - The variable to modify procedureally
    TARGETS (required if 'TARGETS <foo>' is not present in VAR) - The target to install
    EXPORT (required if 'EXPORT <foo>' is not present in VAR) - The export target name to use for the install(EXPORT) command
    DESTINATIONS - The destinations, such as LIBRARY|RUNTIME|PUBLIC_HEADER to install to.
    FILE_SET - The file set to append to the list of FILE_SET to install if INSTALL_FILE_SET evaluates to TRUE.
  Options:
    INSTALL_FILE_SET - If TRUE and a FILE_SET is specified, append FILE_SET to the list of items to install.
    INSTALL - If set, parses all instructions from VAR and passes the parsed arguments to install().
        This occurrs after all other arguments have been processed.
    LOG_LEVEL - When specified to something other than NONE, log additional information.
]]
function(install_arguments_builder)
  include(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/dict.cmake)
  set(options INSTALL)
  set(oneValueArgs VAR TARGETS EXPORT INSTALL_FILE_SET LOG_LEVEL)
  set(multiValueArgs DESTINATIONS FILE_SET)
  cmake_parse_arguments(IA "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  ams_log(VERBOSE "install_arguments_builder: args = '${IA_UNPARSED_ARGUMENTS}'" OVERRIDE_SEVERITY ${IA_LOG_LEVEL})
  
  if(NOT IA_VAR)
    ams_log(SEND_ERROR "install_arguments_builder: VAR not specified")
  endif()
  set(_output "${${IA_VAR}}")
  ams_log("output = '${_output}'")
  if(_output STREQUAL "")
    set(_output [[{}]])
  endif()
  # set or validate TARGET in VAR
  set(_var_target)
  string(JSON _var_target ERROR_VARIABLE _json_err GET "${_output}" TARGETS)
  if(_json_err)
    if(NOT IA_TARGETS)
      ams_log(FATAL_ERROR "install_arguments_builder: TARGETS not specified")
    endif()
    #dict(SET _output KEY TARGETS VALUE ${IA_TARGETS})
    ams_log("output gen target = '${_output}'")
    string(JSON _var_target ERROR_VARIABLE _json_err SET "${_output}" "TARGETS" "${IA_TARGETS}")
    if(_json_err)
      ams_log(FATAL_ERROR "install_arguments_builder: Failed to set TARGETS: ${_json_err}")
    endif()
  endif()
  # set or validate EXPORT in VAR
  set(_var_export)
  string(JSON _var_export ERROR_VARIABLE _json_err GET "${_output}" EXPORT)
  if(_json_err)
    if(NOT IA_EXPORT)
      ams_log(FATAL_ERROR "install_arguments_builder: EXPORT not specified")
    endif()
    string(JSON _var_export ERROR_VARIABLE _json_err SET "${_output}" EXPORT "${IA_EXPORT}")
    if(_json_err)
      ams_log(FATAL_ERROR "install_arguments_builder: Failed to set EXPORT: ${_json_err}")
    endif()
  endif()
  # set or replace DESTINATIONS in VAR
  if(IA_DESTINATIONS)
    string(JSON _var_destinations ERROR_VARIABLE _json_err SET "${_output}" DESTINATIONS "${IA_DESTINATIONS}")
    if(_json_err)
      ams_log(FATAL_ERROR "install_arguments_builder: Failed to set DESTINATIONS: ${_json_err}")
    endif()
  endif()
  # add a FILE_SET to FILE_SETS in VAR, if INSTALL_FILE_SET
  if(IA_INSTALL_FILE_SET)
    if(NOT IA_FILE_SET OR NOT IA_FILE_SET MATCHES "${_file_set_re}")
      ams_log(FATAL_ERROR "install_arguments_builder: INSTALL_FILE_SET specified but FILE_SET not specified or invalid.")
    endif()
    get_file_set_install_command_args(_fs_json FILE_SET_ARGS ${IA_FILE_SET})
    string(JSON _var_file_sets ERROR_VARIABLE _json_err GET "${_output}" FILE_SETS)
    if(_json_err)
      string(JSON _var_file_sets ERROR_VARIABLE _json_err SET "${_output}" FILE_SETS "${IA_FILE_SET}")
      if(_json_err)
        ams_log(FATAL_ERROR "install_arguments_builder: Failed to set FILE_SETS: ${_json_err}")
      endif()
    else()
      list(APPEND _var_file_sets "${_fs_json}")
      string(JSON _var_file_sets ERROR_VARIABLE _json_err SET "${_output}" FILE_SETS "${_var_file_sets}")
      if(_json_err)
        ams_log(FATAL_ERROR "install_arguments_builder: Failed to append FILE_SETS: ${_json_err}")
      endif()
    endif()
  endif()
  set(${IA_VAR} ${_output} PARENT_SCOPE)
endfunction()

