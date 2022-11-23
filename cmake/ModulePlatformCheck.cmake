# ModulePlatformCheck.cmake
# Checks if the platform + compiler supports C++ modules

# Check if the compiler supports c++ modules
function(check_compiler_supports_modules mpc_cmp_result)
  # Get info about the system
  set (_mpc_compiler_supports_modules FALSE)
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # MSVC supports c++ modules since version 19.20
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.20)
      set(_mpc_compiler_supports_modules TRUE)
    endif()
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Clang supports c++ modules since version 9.0
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9.0)
      set(_mpc_compiler_supports_modules TRUE)
    endif()
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # GCC supports c++ modules since version 10.0
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10.0)
      set(_mpc_compiler_supports_modules TRUE)
    endif()
  endif()
  set(${mpc_cmp_result} ${_mpc_compiler_supports_modules} PARENT_SCOPE)
endfunction()

# Check if cmake supports c++ modules
function(check_cmake_supports_modules mpc_cmk_result)
  set (_mpc_cmake_supports_modules FALSE)
  if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.16)
    set(${_mpc_cmake_supports_modules} TRUE)
  else()
    set(${_mpc_cmake_supports_modules} FALSE)
  endif()
  set(${mpc_cmk_result} TRUE PARENT_SCOPE)
endfunction()


# Check if the compiler can compile c++ modules using the current cmake version
# MSVC >= 19.30 can compile modules with cmake >= 3.16, but only with MSBuild for versions of MSVC < 19.34.
# MSVC >= 19.34 with cmake >= 3.20 can compile modules with MSBuild and Ninja.
# Clang >= 10.0 with cmake >= 3.20 can compile modules with Ninja. (very experimental). 
# GCC >= 10.0 with cmake >= 3.20 can compile modules with Ninja. (very experimental).
function(check_compiler_can_compile_modules mpc_final_result)
  check_compiler_supports_modules(_mpc_compiler_supports_modules)
  if (NOT _mpc_compiler_supports_modules)
    message(WARNING "Compiler version does not support c++ modules")
    set(${mpc_final_result} FALSE PARENT_SCOPE)
    return()
  else()
    check_cmake_supports_modules(_mpc_cmake_supports_modules)
    if (NOT _mpc_cmake_supports_modules)
      message(WARNING "CMake version does not support c++ modules")
      set(${mpc_final_result} FALSE PARENT_SCOPE)
      return()
    endif()
  endif()
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if ((CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.30 AND CMAKE_GENERATOR MATCHES "MSBuild")
      OR (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.34 AND (CMAKE_GENERATOR MATCHES "Ninja" OR CMAKE_GENERATOR MATCHES "MSBuild"))
    )
      set(${mpc_final_result} TRUE PARENT_SCOPE)
      return()
    endif()
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13.0 AND CMAKE_GENERATOR MATCHES "Ninja") # TODO Version greater than existing Clang because it is experimental
    set(${mpc_final_result} TRUE PARENT_SCOPE)
    return()
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13.0 AND CMAKE_GENERATOR MATCHES "Ninja") # TODO Version greater than existing GCC because it is experimental
    set(${mpc_final_result} TRUE PARENT_SCOPE)
    return()
  else()
    message(WARNING "Compiler version does not support c++ modules with the current cmake version and generator")
    set(${mpc_final_result} FALSE PARENT_SCOPE)
    return()
  endif()
endfunction()
