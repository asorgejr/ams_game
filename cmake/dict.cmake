function(make_keystr)
  set(options)
  set(oneValueArgs VAR KEY)
  set(multiValueArgs)
  cmake_parse_arguments(MK "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT MK_VAR OR NOT MK_KEY)
    message(FATAL_ERROR "make_keystr requires VAR and KEY")
  endif()
  set(${MK_VAR} "${MK_KEY}" PARENT_SCOPE)
endfunction()

function(make_valuestr)
  set(options)
  set(oneValueArgs VAR VALUE)
  set(multiValueArgs)
  cmake_parse_arguments(MV "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT MV_VAR OR NOT MV_VALUE)
    message(FATAL_ERROR "make_valuestr requires VAR and VALUE")
  endif()
  set(${MV_VAR} "${MV_VALUE}" PARENT_SCOPE)
endfunction()

#[[
dict(<dict> GET|SET|DEL|NEW|KEYS|COUNT KEY <key|key-list> [VALUE <value>])
  Modifies the dictionary string <dict> by adding, removing or setting the value of a specific key.
  This uses jq to parse and modify the dictionary string.
  Arguments:
    DICT <dict>:  the dictionary to modify
    KEY: the key to use. If this is a list (or uses a dot '.' between keys), it is treated as a
      path to a nested dictionary key
    VALUE: the value to assign to the key.
  Commands:
    GET <out-val>: returns the value of the key
    SET: sets the value of the key
    DEL: deletes the key
    NEW: creates a new dictionary if no arguments are given, or, if only a key is given, create
      a key with null value. If a value is given, it is assigned to the key.
    KEYS <out-keys>: returns a list of keys in the dictionary
    COUNT <out-count>: returns the number of keys in the dictionary
]]
function(dict)
  set(_DICT_TMP_FILE_UNPARSED "${CMAKE_BINARY_DIR}/tmp/dict_tmpfile_unparsed")
  set(_DICT_TMP_FILE_STDOUT "${CMAKE_BINARY_DIR}/tmp/dict_tmpfile_stdout")
  set(command_flags SET DEL NEW)
  set(command_val_flags GET KEYS COUNT)
  set(options ${command_flags} ${options})
  set(oneValueArgs ERROR_VARIABLE ${command_val_flags})
  set(multiValueArgs KEY VALUE)
  cmake_parse_arguments(PARSE_ARGV 1 D "${options}" "${oneValueArgs}" "${multiValueArgs}")
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->START: args: '${ARGN}'")
  # get first element of D_UNPARSED_ARGUMENTS
  set(_keywords ${options} ${oneValueArgs} ${multiValueArgs})
  string(REGEX MATCHALL "[^;]+" _args "${ARGV}")
  list(GET _args 0 _arg0)
  foreach(_keyword ${_keywords})
    if(_arg0 STREQUAL ${_keyword})
      message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: the first argument must be a variable name and found: '${_arg0}'")
    endif()
  endforeach()
  set(dict_var ${_arg0})
  if(NOT dict_var)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: DICT is required")
  endif()

  set(_dict ${${dict_var}})
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->PARSING: found dict '${dict_var}': '${_dict}'")
  
  set(_command_count 0)
  set(_command_name "")
  set(_value_command FALSE)
  foreach(_keyword ${_keywords})
    if(${_keyword} STREQUAL ${dict_var})
      message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: a variable was expected, but found a keyword: '${dict_var}'")
    endif()
  endforeach()
  # count number of commands
  foreach(_arg ${ARGN})
    if(_arg IN_LIST command_flags)
      math(EXPR _command_count "${_command_count} + 1")
      set(_command_name ${_arg})
    elseif(_arg IN_LIST command_val_flags)
      math(EXPR _command_count "${_command_count} + 1")
      set(_value_command TRUE)
      set(_command_name ${_arg})
    endif()
  endforeach()
  if(${_command_count} EQUAL 0)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: a command must be present, followed by arguments")
  elseif(${_command_count} GREATER 1)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: only one command can be present")
  endif()
  set(_command_args --input "${_DICT_TMP_FILE_UNPARSED}")
  unset(_key)
  if(D_KEY)
    make_keystr(VAR _key KEY "${D_KEY}")
  endif()
  unset(_vals)
  if(D_VALUE)
    foreach(_value ${D_VALUE})
      make_valuestr(VAR _val VALUE "${_value}")
      list(APPEND _vals "${_val}")
    endforeach()
  endif()
  if((D_SET OR D_GET OR D_DEL) AND NOT _key)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: SET, GET, and DEL require a KEY")
  endif()
  if(D_SET AND NOT D_VALUE)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ARGUMENTS: SET requires a VALUE")
  endif()

  # get environment python
  find_program(PYTHON_EXECUTABLE python)
  if(NOT PYTHON_EXECUTABLE)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->INVALID-ENVIRONMENT: python not found")
  endif()
  if(D_GET)
    set(_command_args "${_command_args}" --get --key "${_key}")
  elseif(D_SET)
    set(_command_args "${_command_args}" --set --key "${_key}" --value "${_vals}")
  elseif(D_DEL)
    set(_command_args "${_command_args}" --del --key "${_key}")
  elseif(D_NEW)
    set(_command_args "${_command_args}" --new)
  elseif(D_KEYS)
    set(_command_args "${_command_args}" --keys)
  elseif(D_COUNT)
    set(_command_args "${_command_args}" --count)
  endif()
  set(_command_args "${_command_args}" --output "${_DICT_TMP_FILE_STDOUT}")
  # create temporary file to store the dictionary
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->PROCESSING: creating tmp file '${_DICT_TMP_FILE_UNPARSED}' with initial contents '${_dict}'")
  file(WRITE "${_DICT_TMP_FILE_UNPARSED}" "${_dict}")
  # create temporary file to store the stdout of the command
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->PROCESSING: creating tmp file '${_DICT_TMP_FILE_STDOUT}'")
  file(WRITE "${_DICT_TMP_FILE_STDOUT}" "")
  # make the command
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->EXECUTING: executing command '${_command_name}' with command line '${PYTHON_EXECUTABLE} dict.py ${_command_args}'")
  # invoke python script to parse the dictionary
  execute_process(
    COMMAND ${PYTHON_EXECUTABLE} dict.py ${_command_args}
    OUTPUT_VARIABLE _result
    RESULT_VARIABLE _result_code
    ERROR_VARIABLE _error
    WORKING_DIRECTORY "${CMAKE_CURRENT_FUNCTION_LIST_DIR}"
  )
  # read the result from the temporary file
  file(READ "${_DICT_TMP_FILE_STDOUT}" _script_output)
  message(DEBUG "${CMAKE_CURRENT_FUNCTION}->POST-EXECUTION: result: '${_script_output}', result_code: '${_result_code}'")
  # remove temporary file
  # file(REMOVE "${_DICT_TMP_FILE_UNPARSED}" "${_DICT_TMP_FILE_STDOUT}")
  if(D_ERROR_VARIABLE)
    if(${_result_code} EQUAL 0)
      unset(${D_ERROR_VARIABLE} PARENT_SCOPE)
    else()
      set(${D_ERROR_VARIABLE} ${_error} PARENT_SCOPE)
    endif()
  elseif(NOT ${_result_code} EQUAL 0)
    message(FATAL_ERROR "${CMAKE_CURRENT_FUNCTION}->RESULT-SCRIPT-ERROR: error executing command: '${_command_name}'. result: '${_result_code}'. error: ${_error}")
  endif()
  if(_value_command)
    message(DEBUG "${CMAKE_CURRENT_FUNCTION}->RESULT: setting value variable '${D_${_command_name}}' to '${_script_output}'")
    set(${D_${_command_name}} "${_script_output}" PARENT_SCOPE)
  else()
    message(DEBUG "${CMAKE_CURRENT_FUNCTION}->RESULT: setting dict variable '${dict_var}' to '${_script_output}'")
    set(${dict_var} "${_script_output}" PARENT_SCOPE)
  endif()
endfunction()