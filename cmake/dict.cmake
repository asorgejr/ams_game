
set(_esc "\\")
set(_o_ob "{")
set(_o_cb "}")
set(_a_ob "[")
set(_a_cb "]")
set(_k_sep ":")
set(_v_sep ",")
set(_q "\"")
set(_esc "\\")
set(_dictminlen 7)
set(_kpathsep ".")

function(_d_dbg FN_NAME CTX MSG)
  set(_d_list_ctx "${CMAKE_CURRENT_LIST_FILE}")
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.25)
    cmake_language(GET_MESSAGE_LOG_LEVEL _sev_level)
    if(_sev_level STREQUAL "DEBUG")
      message("[DEBUG] -- [${FN_NAME}->${CTX}]: ${MSG} << parent context: '${_d_list_ctx}:1'")
    endif()
  else()
    message(DEBUG "[${FN_NAME}->${CTX}]: ${MSG} << parent context: '${_d_list_ctx}'")
  endif()
endfunction()

function(_d_err FN_NAME CTX MSG)
  message(FATAL_ERROR "ERROR: in ${FN_NAME}() >> reason: \"${CTX} -- ${MSG}\" << parent context: ${CMAKE_CURRENT_LIST_FILE}")
endfunction()


#[[
find(VAR <out-var> STR <string-to-search> TOKEN <token-symbol> [START <start-pos>][STOP <stop-pos>][REVERSE][MATCH_ESCAPED])
  Finds the position of the first matching symbol.
  Returns the position of the symbol or -1 if not found.
  Arguments:
    VAR: the variable to store the position of the symbol
    STR: the string to search
    TOKEN: the token symbol to search for
    START: the optional position to start searching from (default: 0)
    STOP: the optional position to stop searching from (default: len(STR)-1).
      This value must be set to a number encountered after START in either direction.
      For example, if searching forward: assert(START<STOP). If searching reverse: assert(START>STOP).
  Options:
    MATCH_ESCAPED: if set, a symbol preceded by an escape character is counted
    REVERSE: if set, the search is performed in reverse
]]
function(find_token)
  set(ft_FAIL -1)
  set(options MATCH_ESCAPED REVERSE)
  set(oneValueArgs VAR STR TOKEN START STOP)
  set(multiValueArgs)
  cmake_parse_arguments(FT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: '${FT_VAR}', STR: '${FT_STR}', TOKEN: '${FT_TOKEN}', START: '${FT_START}', MATCH_ESCAPED: '${FT_MATCH_ESCAPED}', REVERSE: '${FT_REVERSE}'")
  if(NOT FT_STR)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid" "search string is empty. returning ${ft_FAIL}")
    set(${FT_VAR} ${ft_FAIL} PARENT_SCOPE)
    return()
  endif()
  if(NOT FT_TOKEN)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-argument" "TOKEN must be specified")
  endif()
  set(ft_substr "${FT_STR}")
  string(LENGTH "${ft_substr}" ft_substrlen)
  if(NOT FT_START)
    set(FT_START 0)
  elseif(FT_START GREATER_EQUAL ft_substrlen OR FT_START LESS 0)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "invalid-argument" "START value: '${FT_START}' out of range '0:${ft_substrlen}-1'. return ${ft_FAIL}")
    set(${FT_VAR} ${ft_FAIL} PARENT_SCOPE)
    return()
  endif()
  if(NOT FT_STOP)
    set(FT_STOP ${ft_substrlen})
    if(REVERSE)
      set(FT_STOP 0)
    endif()
  elseif(NOT FT_REVERSE AND FT_STOP LESS FT_START OR FT_STOP GREATER_EQUAL ${ft_substrlen})
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "invalid-argument" "STOP value: '${FT_STOP}' is out of range. Must be greater or equal to START value: '${FT_START}' and must be between '0:${ft_substrlen}'. return ${ft_FAIL}")
    return()
  elseif(FT_STOP GREATER FT_START OR FT_STOP LESS 0)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "invalid-argument" "STOP value: '${FT_STOP}' is out of range. When REVERSE, value must be less or equal to START value: '${FT_START}' and must be between '0:${ft_substrlen}'. return ${ft_FAIL}")
    return()
  endif()

  set(ft_step 1)
  set(ft_pos ${FT_START})
  set(ft_endpos ${FT_STOP})
  if(FT_REVERSE)
    set(ft_step -1)
    math(EXPR ft_pos "${ft_substrlen} - 1")
    set(ft_remaininglen "${FT_START}")
  endif()
  string(LENGTH "${FT_TOKEN}" ft_tokenlen)
  string(SUBSTRING "${FT_TOKEN}" 0 1 ft_token_firstchar)
  if(ft_substrlen EQUAL 1 AND ft_tokenlen EQUAL 1)
    if(ft_substr STREQUAL "${FT_TOKEN}")
      set(${FT_VAR} 0 PARENT_SCOPE)
      return()
    else()
      set(${FT_VAR} ${ft_FAIL} PARENT_SCOPE)
      return()
    endif()
  endif()
  set(ft_totalmoves 0)
  set(_d_ft_totalinc 0)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "loop-start" "ft_pos: ${ft_pos}, ft_endpos: ${ft_endpos}, ft_step: ${ft_step}, ft_substr: '${ft_substr}', ft_token_firstchar: '${ft_token_firstchar}', ft_tokenlen: '${ft_tokenlen}'")
  foreach(ft_pos RANGE ${ft_pos} ${ft_endpos} ${ft_step})
    string(SUBSTRING "${ft_substr}" ${ft_pos} 1 ft_char)
    if(ft_char STREQUAL "${ft_token_firstchar}")
      if(FT_REVERSE AND ft_totalmoves LESS ft_tokenlen)
        math(EXPR ft_totalmoves "${ft_totalmoves} + 1")
        math(EXPR _d_ft_totalinc "${_d_ft_totalinc} + 1")
        continue()
      endif()
      string(SUBSTRING "${ft_substr}" ${ft_pos} ${ft_tokenlen} _slice)
      if(NOT _slice STREQUAL "${FT_TOKEN}")
        math(EXPR ft_totalmoves "${ft_totalmoves} + 1")
        math(EXPR _d_ft_totalinc "${_d_ft_totalinc} + ${ft_tokenlen}")
        continue()
      endif()
      if(NOT FT_MATCH_ESCAPED)
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "token found at ${ft_pos}. solved in ${_d_ft_totalinc} steps")
        set(${FT_VAR} ${ft_pos} PARENT_SCOPE)
        return()
      endif()
      math(EXPR _beforepos "${ft_pos} - 1")
      if(_beforepos LESS 0)
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "token found at ${ft_pos}. solved in ${_d_ft_totalinc} steps")
        set(${FT_VAR} ${ft_pos} PARENT_SCOPE)
        return()
      endif()
      string(SUBSTRING "${ft_substr}" ${_beforepos} 1 _beforechar)
      math(EXPR _d_ft_totalinc "${_d_ft_totalinc} + 1")
      if(_beforechar STREQUAL "${_esc}")
        math(EXPR ft_totalmoves "${ft_totalmoves} + 1")
        math(EXPR _d_ft_totalinc "${_d_ft_totalinc} + 1")
        continue()
      endif()
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "token found at ${ft_pos}. solved in ${_d_ft_totalinc} steps")
      set(${FT_VAR} ${ft_pos} PARENT_SCOPE)
      return()
    endif()
    math(EXPR ft_totalmoves "${ft_totalmoves} + 1")
    math(EXPR _d_ft_totalinc "${_d_ft_totalinc} + 1")
  endforeach()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-not-found" "token not found. returning ${ft_FAIL}")
  set(${FT_VAR} ${ft_FAIL} PARENT_SCOPE)
endfunction()


#[[ 
find_matching_token(VAR <out-var> STR <string-to-search> OPEN <opening-sym> CLOSE <closing-sym> [START <start-pos>][MATCH_ESCAPED])
  Find a matching closing symbol by counting the amount of opening symbol vs closing symbol.
  If the opening symbol and closing symbol are the same, then the function will simply return
  the position of the first matching symbol.
  Returns the position of the matching closing symbol or -1 if not found.
  Arguments:
    VAR: the variable to store the position of the matching closing symbol
    STR: the string to search
    OPEN: the opening symbol
    CLOSE: the closing symbol
    START: the optional position to start searching from (default: 0)
  Options:
    MATCH_ESCAPED: if set, a closing symbol preceded by an escape character is counted
]]
function(find_matching_token)
  set(fmtk_FAIL -1)
  set(options MATCH_ESCAPED)
  set(oneValueArgs VAR STR OPEN CLOSE START)
  set(multiValueArgs)
  cmake_parse_arguments(FMTK "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT FMTK_START)
    set(FMTK_START 0)
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: ${FMTK_VAR}, STR: '${FMTK_STR}', OPEN: '${FMTK_OPEN}', CLOSE: '${FMTK_CLOSE}', START: ${FMTK_START}")
  string(LENGTH "${FMTK_STR}" _strlen)
  set(fmtk_opensym "${FMTK_OPEN}")
  set(fmtk_closesym "${FMTK_CLOSE}")
  string(LENGTH "${fmtk_opensym}" fmtk_opensym_len)
  string(LENGTH "${fmtk_closesym}" fmtk_closesym_len)
  if(fmtk_opensym LESS 1 OR fmtk_closesym LESS 1)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "OPEN and CLOSE tokens must be specified")
  endif()
  set(fmtk_pos ${FMTK_START})
  set(fmtk_substr "${FMTK_STR}")
  string(LENGTH "${fmtk_substr}" fmtk_substrlen)
  if (fmtk_opensym STREQUAL fmtk_closesym)
    # symbols are identical. find the first occurrence, checking if it is escaped
    # if MATCH_ESCAPED is not set.
    set(fmtk_substr "${FMTK_STR}")
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "begin-search-identical" "searching for first occurrence of identical token")
    if(FMTK_MATCH_ESCAPED)
      find_token(VAR fmtk_pos STR ${fmtk_substr} TOKEN "${fmtk_closesym}" START ${fmtk_pos} MATCH_ESCAPED)
    else()
      find_token(VAR fmtk_pos STR ${fmtk_substr} TOKEN "${fmtk_closesym}" START ${fmtk_pos})
    endif()
    if(fmtk_pos EQUAL ${fmtk_FAIL})
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-notfound" "a matching token could not be found. return -1")
      set(${FMTK_VAR} ${fmtk_FAIL} PARENT_SCOPE)
      return()
    endif()
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found matching token at ${fmtk_pos}")
    set(${FMTK_VAR} ${fmtk_pos} PARENT_SCOPE)
    return()
  else()
    # symbols are not identical. Scan ahead and count the number of occurrences
    set(_opensym_count 0)
    set(_closesym_count 0)
    set(_current_opensym_pos ${FMTK_START})
    set(_current_closesym_pos ${FMTK_START})
    set(_completed_search FALSE)
    while(NOT (_current_opensym_pos LESS 0 AND _current_closesym_pos LESS 0))
      set(fmtk_pos ${_current_closesym_pos})
      #_d_dbg("${CMAKE_CURRENT_FUNCTION}" "loop" "opens = ${_opensym_count}, pos = ${_current_opensym_pos}; closes = ${_closesym_count}, pos = ${_current_closesym_pos}")
      if(FMTK_MATCH_ESCAPED)
        find_token(VAR _current_opensym_pos STR ${fmtk_substr} TOKEN "${fmtk_opensym}" START ${_current_opensym_pos} MATCH_ESCAPED)
        find_token(VAR _current_closesym_pos STR ${fmtk_substr} TOKEN "${fmtk_closesym}" START ${_current_closesym_pos} MATCH_ESCAPED)
      else()
        find_token(VAR _current_opensym_pos STR ${fmtk_substr} TOKEN "${fmtk_opensym}" START ${_current_opensym_pos})
        find_token(VAR _current_closesym_pos STR ${fmtk_substr} TOKEN "${fmtk_closesym}" START ${_current_closesym_pos})
      endif()
      #_d_dbg("${CMAKE_CURRENT_FUNCTION}" "loop-endsearch" "opens = ${_opensym_count}, pos = ${_current_opensym_pos}; closes = ${_closesym_count}, pos = ${_current_closesym_pos}")
      if(_current_opensym_pos GREATER -1)
        math(EXPR _opensym_count "${_opensym_count} + 1")
        math(EXPR _current_opensym_pos "${_current_opensym_pos} + 1")
      endif()
      if(_current_closesym_pos GREATER -1)
        math(EXPR _closesym_count "${_closesym_count} + 1")
        math(EXPR _current_closesym_pos "${_current_closesym_pos} + 1")
      endif()
      if(_current_opensym_pos LESS 0 AND _current_closesym_pos LESS 0)
        if(NOT _opensym_count EQUAL _closesym_count)
          _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-notfound" "a matching token could not be found. return -1")
          set(${FMTK_VAR} ${fmtk_FAIL} PARENT_SCOPE)
          return()
        endif()
      endif()
#[[
      set(_is_esc FALSE)
      string(SUBSTRING "${FMTK_STR}" ${fmtk_pos} ${fmtk_opensym_len} fmtk_opensym_tmp)
      string(SUBSTRING "${FMTK_STR}" ${fmtk_pos} ${fmtk_closesym_len} fmtk_closesym_tmp)
      if(fmtk_opensym_tmp STREQUAL fmtk_opensym)
        if(NOT FMTK_MATCH_ESCAPED)
          # begin lookbehind for \\.
          if(fmtk_pos GREATER ${FMTK_START})
            # get previous char
            string(SUBSTRING "${FMTK_STR}" ${_lastpos} 1 _lastchar)
            if(NOT _lastchar STREQUAL "${_esc}")
              math(EXPR _opensym_count "${_opensym_count} + 1")
            endif()
            # last character was \\. Don't increment.
          else()
            # we are at beginning of string
            math(EXPR _opensym_count "${_opensym_count} + 1")
          endif()
        else()
          # we don't care about escape char. Always increment on match.
          math(EXPR _opensym_count "${_opensym_count} + 1")
        endif()
        math(EXPR fmtk_pos "${fmtk_pos} + ${fmtk_opensym_len} - 1") # if we match, we need to increment by the size of the opening symbol - 1
      elseif(fmtk_closesym_tmp STREQUAL fmtk_closesym)
        # begin lookbehind for \\.
        if(NOT FMTK_MATCH_ESCAPED)
          if(fmtk_pos GREATER ${FMTK_START})
            string(SUBSTRING "${FMTK_STR}" ${_lastpos} 1 _lastchar)
            if(NOT _lastchar STREQUAL "${_esc}")
              math(EXPR _closesym_count "${_closesym_count} + 1")
            endif()
            # last character was \\. Don't increment.
          else()
            # we are at beginning of string
            math(EXPR _closesym_count "${_closesym_count} + 1")
          endif()
        else()
          # we don't care about escape char. Always increment on match.
          math(EXPR _closesym_count "${_closesym_count} + 1")
        endif()
        math(EXPR fmtk_pos "${fmtk_pos} + ${fmtk_closesym_len} - 1") # if we match, we need to increment by the size of the closing symbol - 1
      endif()
      if(_opensym_count EQUAL _closesym_count)
        set(${FMTK_VAR} ${fmtk_pos} PARENT_SCOPE)
        return()
      endif()
      set(_lastpos ${fmtk_pos})
      math(EXPR fmtk_pos "${fmtk_pos} + 1")
]]
    endwhile()
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "a matching token found at ${fmtk_pos}")
    set(${FMTK_VAR} ${fmtk_pos} PARENT_SCOPE)
  endif()
endfunction()


#[[
find_all(VAR <out-list> STR <str-to-search> TOKEN <token-symbol>)
  Finds all occurrences of a token in a string and stores the positions in a list.
  Arguments:
    VAR: the variable to store the list of positions
    STR: the string to search
    TOKEN: the token to search for
  Options:
    MATCH_ESCAPED: if set, a token preceded by an escape character is counted
]]
function(find_all)
  set(options MATCH_ESCAPED)
  set(oneValueArgs VAR STR TOKEN)
  set(multiValueArgs)
  cmake_parse_arguments(FA "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(_pos 0)
  set(_pos_list)
  set(_substr "${FA_STR}")
  while(_pos LESS FA_STRLEN AND _pos GREATER -1)
    string(FIND "${_substr}" "${FA_TOKEN}" _pos "${_pos}")
    if(_pos EQUAL -1 OR _pos EQUAL 0)
      set(_pos -1)
      break()
    endif()
    if(NOT FA_MATCH_ESCAPED)
      math(EXPR _lastpos "${_pos} - 1")
      string(SUBSTRING "${_substr}" "${_pos}" 1 _lastpos)
      if(NOT _prev_char STREQUAL "${_esc}")
        list(APPEND _pos_list ${_pos})
      endif()
    else()
      list(APPEND _pos_list ${_pos})
    endif()
    math(EXPR _pos "${_pos} + 1")
    string(SUBSTRING "${_substr}" "${_pos}" -1 _substr)
  endwhile()
  set(${FA_VAR} ${_pos_list} PARENT_SCOPE)
endfunction()


#[[
dict_unquote_str(<str>)
  Unquotes a string. Removes leading and trailing quotes.
  Arguments:
    <str>: the string to unquote
]]
function(dict_unquote_str quotestr)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "quotestr: '${quotestr}'")
  string(LENGTH "${quotestr}" duq_strlen)
  string(SUBSTRING "${quotestr}" 0 1 duq_strfirstchar)
  if(duq_strfirstchar STREQUAL "${_q}")
    # key is quoted
    string(SUBSTRING "${quotestr}" 1 -1 quotestr)
    string(LENGTH "${quotestr}" duq_strlen)
    string(SUBSTRING "${quotestr}" -1 1 duq_strlastchar)
    if(duq_strlastchar STREQUAL "${_q}")
      # key is quoted
      string(SUBSTRING "${quotestr}" 0 -1 quotestr)
    else()
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-key" "key is invalid")
      set(${D_VAR} ${d_FAIL} PARENT_SCOPE)
      return()
    endif()
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "quotestr: '${quotestr}'")
  set(quotestr ${quotestr} PARENT_SCOPE)
endfunction()


#[[
dict_valid_key(VAR <out-var> STR <keystr>)
  Returns true if the given keystr is a valid keystr.
  A keystr is a string that can be used as a key in a dictionary.
  A keystr is valid if it is a string that does not contain any of the following characters:
    " : { } [ ] , # % & * | \ < > ~ ^ ? ! = ; $ ` @
]]
function(dict_valid_key)
  set(oneValueArgs STR VAR)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: '${D_VAR}', KEY: '${D_KEY}'")
  string(REGEX MATCH "^[^\"{}\[\],#%&*|\\<>~^?!=;$`@]+$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "key is valid.")
    set(${D_VAR} TRUE PARENT_SCOPE)
  else()
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid" "key '${D_KEY}' is valid.")
    set(${D_VAR} FALSE PARENT_SCOPE)
  endif()
endfunction()


#[[
dict_valid_keypath(VAR <out-var> STR <keystr>)
  Returns true if the given keystr path is a valid keystr path.
  A keystr path is a string that can be used to find a key in a dictionary. The '.' character
      is used between keynames. For example, to check the existence of {"foo":{"bar"}}, 
      the keystr path 'foo.bar' would be used.
  A keystr path is valid if it is a string that does not contain any of the following characters:
    " : { } [ ] , # % & * | \ < > ~ ^ ? ! = ; $ ` @
      and must not have a heading or trailing '.'
]]
function(dict_valid_keypath)
  set(oneValueArgs VAR STR)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multtValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: '${D_VAR}', KEY: '${D_KEY}'")
  string(REGEX MATCH "^[^${_kpathsep}].*[^${_kpathsep}]$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "key is valid.")
    set(${D_VAR} TRUE PARENT_SCOPE)
  else()
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid" "key '${D_KEY}' is valid.")
    set(${D_VAR} FALSE PARENT_SCOPE)
  endif()
endfunction()


#[[
dict_valid_value(VAR <out-var> STR <value>)
  Returns true if the given value is a valid value.
  Follows JSON rules for values, i.e. a value can be:
    - a string
    - a number
    - a boolean
    - a null
    - a list
    - a dictionary
  Arguments:
    STR: the value to check
    VAR: the variable to set to true if the value is valid, false otherwise
]]
function(dict_valid_value)
  set(oneValueArgs STR VAR)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  # string
  string(REGEX MATCH "^\".*\"$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found valid string. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  # number (with optional scientific notation)
  string(REGEX MATCH "^-?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found valid number. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  # boolean
  string(REGEX MATCH "^(true|false)$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found valid boolean. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  # null
  string(REGEX MATCH "^null$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found valid null. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  # list
  string(REGEX MATCH "^\[.*\]$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found list. contents not analyzed. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  # dictionary
  string(REGEX MATCH "^\{.*\}$" _valid "${D_STR}")
  if(_valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "found dictionary. contents not analyzed. returning TRUE")
    set(${D_VAR} TRUE PARENT_SCOPE)
    return()
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid" "found invalid value. returning FALSE")
  set(${D_VAR} FALSE PARENT_SCOPE)
endfunction()


#[[
dict_valid_kvp(VAR <out-var> STR <kvp>)
  Returns true if the given kvp is a valid kvp.
  A kvp is a key-value pair, i.e. a string of the form "\"key\": <value>".
  A kvp is valid if the key is a valid keystr and the value is a valid value.
  Arguments:
    VAR: the variable to set to true if the kvp is valid, false otherwise
    STR: the kvp to check
]]
function(dict_valid_kvp)
  set(oneValueArgs STR VAR)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "args = '${ARGV}'")
  # get key part
  find_token(VAR _kpos STR "${D_STR}" TOKEN "${_k_sep}")
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "kvp separator position: '${_kpos}'")
  if(_kpos EQUAL -1)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-kvp" "no key separator found. returning FALSE")
    set(${D_VAR} FALSE PARENT_SCOPE)
    return()
  endif()
  string(SUBSTRING "${D_STR}" 0 "${_kpos}" _key)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "key: '${_key}'")
  dict_valid_key(VAR _valid STR "${_key}")
  if(NOT _valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-key" "key is not valid. returning FALSE")
    set(${D_VAR} FALSE PARENT_SCOPE)
    return()
  endif()
  # get value part
  math(EXPR _vlen "${FA_STRLEN} - ${_kpos} - ${_k_sep_len}")
  string(SUBSTRING "${D_STR}" "${_kpos}" "${_vlen}" _value)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "value: '${_value}'")
  dict_valid_value(VAR _valid STR "${_value}")
  if(NOT _valid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-value" "value is not valid. returning FALSE")
    set(${D_VAR} FALSE PARENT_SCOPE)
    return()
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "kvp is valid. returning TRUE")
  set(${D_VAR} TRUE PARENT_SCOPE)
endfunction()



#[[
dict_get_scope_range(POS1 <out-var> POS2 <out-var> DICT <dict-var> INDEX <pos-idx>)
  Returns the start and end positions of the scope of the given index.
  Arguments:
    POS1: the variable to set to the start position of the scope
    POS2: the variable to set to the end position of the scope
    DICT: the dictionary to search
    INDEX: the index of the scope to find
]]
function(dict_get_scope_range)
  set(oneValueArgs POS1 POS2 DICT INDEX)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "args = '${ARGV}'")
  if(NOT D_DICT)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-dict" "no dict given")
    set(${D_POS1} -1 PARENT_SCOPE)
    set(${D_POS2} -1 PARENT_SCOPE)
    return()
  endif()
  if(NOT D_INDEX)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-index" "no index given")
    set(${D_POS1} -1 PARENT_SCOPE)
    set(${D_POS2} -1 PARENT_SCOPE)
    return()
  endif()
  find_token(VAR _start STR "${${D_DICT}}" TOKEN "${_o_ob}" START ${D_INDEX} REVERSE)
  if(_start EQUAL -1)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-start" "no start brace found")
    set(${D_POS1} -1 PARENT_SCOPE)
    set(${D_POS2} -1 PARENT_SCOPE)
    return()
  endif()
  find_matching_token(VAR _end STR "${${D_DICT}}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${_start})
  if(_end EQUAL -1)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-end" "no end brace found")
    set(${D_POS1} -1 PARENT_SCOPE)
    set(${D_POS2} -1 PARENT_SCOPE)
    return()
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "start: ${_start}, end: ${_end}")
  set(${D_POS1} ${_start} PARENT_SCOPE)
  set(${D_POS2} ${_end} PARENT_SCOPE)
endfunction()


#[[
dict_find_key_position(VAR <out-var> DICT <dict-var> KEY <key-str> [POPEN <out-var>][PCLOSE <out-var>][KVPVAR <out-var>])
  Returns the position of a key if the given dictionary has the given key.
  Arguments:
    VAR: the variable to set if the dictionary has the key, -1 otherwise
    DICT: the dictionary to check
    KEY: the key to check. This can be a path. To find a key
      by path, the '.' character is used between keynames.
      For example, to check the existence of {"foo":{"bar"}}, the key 'foo.bar'
      would be used.
    START: optional starting position. Defaults to 0.
    POPEN: optionally set a variable to the parent opening bracket. If not found, -1
    PCLOSE: optionally set a variable to the parent closing bracket. If not found, -1
    KVPVAR: optionally set a variable to the key-value-pair string if KEY is found. If not found, FALSE
]]
function(dict_find_key_position)
  set(dfk_FAIL -1)
  set(oneValueArgs VAR DICT KEY START POPEN PCLOSE KVPVAR)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: '${D_VAR}', DICT: '${D_DICT}', KEY: '${D_KEY}', START: '${D_START'")
  if(D_POPEN)
    set(${D_POPEN} ${dfk_FAIL} PARENT_SCOPE) # set default
  endif()
  if(D_PCLOSE)
    set(${D_PCLOSE} ${dfk_FAIL} PARENT_SCOPE) # set default
  endif()
  if(D_KVPVAR)
    set(${D_KVPVAR} FALSE PARENT_SCOPE) # set default
  endif()
  if(NOT D_DICT)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-dict" "no dict given")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()
  if(NOT D_KEY)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-key" "no key given")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()

  string(LENGTH "${D_DICT}" _dictlen)
  if(NOT D_START)
    set(D_START 0)
  elseif(D_START LESS 0 OR D_START GREATER_EQUAL _dictlen)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-args" "start position '${D_START}' is out of range '0:${_dictlen}'")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()
  dict_valid_key(VAR _isvalid STR ${D_KEY})
  if(NOT _isvalid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-key" "invalid key given")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()
  dict_valid_keypath(VAR _isvalid STR ${D_KEY})
  if(NOT _isvalid)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-key" "keypath cannot start or end with dot.")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()
  list(GET dfk_keypath 0 dfk_key)
  list(REMOVE_AT dfk_keypath 0)
  set(dfk_cursorpos ${D_START})
  set(dfk_found FALSE)
  set(dfk_dict_var ${D_DICT})
  set(dfk_key ${D_KEY})
  set(dfk_dict ${${D_DICT}})
  
  if(D_POPEN AND D_PCLOSE)
    find_token(VAR _popen STR "${dfk_dict}" TOKEN "${_o_ob}" START ${dfk_cursorpos} REVERSE)
    set(${D_POPEN} ${_popen} PARENT_SCOPE)
    find_matching_token(VAR _pclose STR "${dfk_dict}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${_popen})
    if(_popen LESS 0 OR _pclose LESS 0)
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-brace-mismatch" "dictionary is invalid")
      set(${D_POPEN} ${dfk_FAIL} PARENT_SCOPE)
      set(${D_PCLOSE} ${dfk_FAIL} PARENT_SCOPE)
    endif()
    set(${D_POPEN} ${_popen} PARENT_SCOPE)
    set(${D_PCLOSE} ${_pclose} PARENT_SCOPE)
  else()
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "If POPEN or PCLOSE is specified, both must be specified.")
  endif()

  # parse key (and possible path) to see if a dict entry already exists
  string(REGEX REPLACE "^${_kpathsep}" ";" dfk_key_parts "${dfk_key}")
  # get size of path
  list(LENGTH dfk_key_parts dfk_key_parts_len)
  # we should expect to find a key at this depth.
  # count open braces to make sure we're at the right depth
  find_matching_token(VAR _cb_pos STR "${dfk_dict}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${dfk_cursorpos})
  if(_cbpos EQUAL -1)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-brace-mismatch" "dictionary is invalid")
    set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
    return()
  endif()
  set(_depth 0) # increment positive as we get deeper
  foreach(dfk_keypart IN_LIST dfk_key_parts)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "loop-begin" "keypart = '${dfk_keypart}'")
    # find next open brace
    find_token(VAR dfk_cursorpos STR "${dfk_dict}" TOKEN "${_o_ob}" START ${dfk_cursorpos})
    # and matched close brace
    find_matching_token(VAR _cb_pos STR "${dfk_dict}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${dfk_cursorpos})

    math(EXPR _depth "${_depth} + 1")
    # try to find key
    find_token(VAR dfk_cursorpos STR "${dfk_dict}" TOKEN "\"${dfk_keypart}\"")
    if(dfk_cursorpos EQUAL -1)
      # key not found
      break()
    endif()
    # if _depth == dfk_key_parts_len, we're at the end of the path
    # and we've found the key
    if(_depth EQUAL dfk_key_parts_len)
      set(dfk_found TRUE)
      break()
    endif()
    # if we're not at the end of the path, continue
  endforeach()
  if(dfk_found)
    set(${D_VAR} ${dfk_cursorpos} PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "key found at position ${dfk_cursorpos}")
    return()
  endif()
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-not-found" "key not found")
  set(${D_VAR} ${dfk_FAIL} PARENT_SCOPE)
endfunction()


#[[
dict_enumerate_kvps(VAR <out-var> DICT <dict-var>)
  Returns a list of key-value pairs from the given dictionary. Does not
  perform traversal of the dictionary.
  Arguments:
    VAR: the variable to set if the dictionary has the key, otherwise none
    DICT: the dictionary to enumerate
]]
function(dict_enumerate_kvps)
  set(dek_FAIL FALSE)
  set(oneValueArgs VAR DICT)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT D_DICT)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-dict" "no dict given")
    set(${D_VAR} ${dek_FAIL} PARENT_SCOPE)
    return()
  endif()
  string(STRIP "${${D_DICT}}" _dict)
  find_matching_token(VAR _cb_pos STR "${_dict}" OPEN "${_o_ob}" CLOSE "${_o_cb}")
  set(_ret "")
  if(_cbpos EQUAL -1)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-brace-mismatch" "dictionary is invalid")
    set(${D_VAR} ${dek_FAIL} PARENT_SCOPE)
    return()
  elseif(_cbpos LESS ${_dictminlen})
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-empty" "dictionary is empty")
    set(${D_VAR} ${dek_FAIL} PARENT_SCOPE)
    return()
  else()
    string(SUBSTRING "${_dict}" 1 -2 _ret)
  endif()
    
  string(LENGTH "${_ret}" _len)
  # replace commas with ';'
  set(_cursorpos 0)
  while(_cursorpos LESS _len)
    string(SUBSTRING "${_ret}" ${_cursorpos} 1 _char)
    # avoid all traversal.
    if(_char STREQUAL "${_o_ob}")
      # we're at the start of a dict
      # find the end of the dict
      find_matching_token(VAR _cb_pos STR "${_ret}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${_cursorpos})
      if(_cb_pos EQUAL -1)
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-dict" "dictionary is invalid")
        set(${D_VAR} ${dek_FAIL} PARENT_SCOPE)
        return()
      endif()
      # set cursor to end of dict
      set(_cursorpos ${_cb_pos})
    elseif(_char STREQUAL "${_a_ob}")
      # we're at the start of an array
      # find the end of the array
      find_matching_token(VAR _cb_pos STR "${_ret}" OPEN "${_a_ob}" CLOSE "${_a_cb}" START ${_cursorpos})
      if(_cb_pos EQUAL -1)
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-dict" "dictionary is invalid")
        set(${D_VAR} ${dek_FAIL} PARENT_SCOPE)
        return()
      endif()
      # set cursor to end of array
      set(_cursorpos ${_cb_pos})
    elseif(_char STREQUAL "${_comma}")
      # replace comma with semicolon
      string(SUBSTRING "${_ret}" 0 ${_cursorpos} _ret1)
      string(SUBSTRING "${_ret}" ${_cursorpos} -1 _ret2)
      set(_ret "${_ret1};${_ret2}")
    endif()
    math(EXPR _cursorpos "${_cursorpos} + 1")
  endwhile()
  set(${D_VAR} "${_ret}" PARENT_SCOPE)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "key-value pairs: ${_ret}")
endfunction()



#[[
dict_get_kvp(VAR <out-var> ARR <list-var> KEY <key>)
  Returns the key value pair for the given key.
  Arguments:
    VAR: the variable to set to the key value pair
    ARR: the list of kvps to search
    KEY: the key to search for
]]
function(dict_get_kvp)
  set(dgk_FAIL FALSE)
  set(oneValueArgs VAR ARR KEY)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "ARR: ${D_ARR}, KEY: ${D_KEY}")
  if(NOT D_ARR)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-arr" "no array given")
    set(${D_VAR} ${dgk_FAIL} PARENT_SCOPE)
    return()
  endif()
  if(NOT D_KEY)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-key" "no key given")
    set(${D_VAR} ${dgk_FAIL} PARENT_SCOPE)
    return()
  endif()
  set(d_keytmp "${D_KEY}")
  dict_unquote_str(d_keytmp)
  foreach(_kvp ${${D_ARR}})
    string(REGEX MATCH "^${_q}${D_KEY}${_q}${_k_sep}" _match "${_kvp}")
    if(_match)
      set(${D_VAR} "${_kvp}" PARENT_SCOPE)
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "kvp: ${_kvp}")
      return()
    endif()
  endforeach()
    
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-match" "no match found")
  set(${D_VAR} ${dgk_FAIL} PARENT_SCOPE)
endfunction()
  


#[[
dict_kvp_get_value(VAR <out-var> KVP <kvp>)
  Returns the value of a key-value pair.
  Arguments:
    VAR: the variable to set
    KVP: the key-value pair
]]
function(dict_kvp_get_value)
  set(dkgv_FAIL FALSE)
  set(oneValueArgs VAR KVP)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "VAR: '${D_VAR}', KVP: '${D_KVP}'")
  if(NOT D_KVP)
    set(${D_VAR} ${dkgv_FAIL} PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-kvp" "no kvp given")
    return()
  endif()
  string(REGEX MATCH "^\".*\"${_ksep}(.*)$" _isvalid "${D_KVP}")
  if(NOT _isvalid)
    set(${D_VAR} ${dkgv_FAIL} PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-kvp" "invalid kvp given")
    return()
  endif()
  set(${D_VAR} "${CMAKE_MATCH_1}" PARENT_SCOPE)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "value = '${CMAKE_MATCH_1}'")
endfunction()
  



#[[
dict_get(VAR <out-var> DICT <dict-var> KEY <key-str>)
  Gets the value of the given key in the given dictionary.
  Arguments:
    VAR: the variable to set to the value of the key
    DICT: the dictionary to get the key from
    KEY: the key to get the value of. This can be a path. To retrieve a value
      by path, the '.' character is used between keynames.
      For example, to get the value of {foo:{bar:'value'}}, the key 'foo.bar'
      would be used.
]]
function(dict_get)
  set(oneValueArgs VAR DICT KEY)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT D_DICT)
    _d_err("${CMAKE_FUNCTION_NAME}" "invalid-args" "DICT argument is required")
  endif()
  if(NOT D_KEY)
    _d_err("${CMAKE_FUNCTION_NAME}" "invalid-args" "KEY argument is required")
  endif()
  if(NOT D_VAR)
    _d_err("${CMAKE_FUNCTION_NAME}" "invalid-args" "VAR argument is required")
  endif()
  dict_valid_key(VAR _isvalid STR ${D_KEY})
  if(NOT _isvalid)
    _d_err("${CMAKE_FUNCTION_NAME}" "invalid-args" "KEY argument is not a valid key string")
  endif()
  dict_find_key_position(VAR _keypos DICT ${D_DICT} KEY ${D_KEY})
  if(_keypos EQUAL -1)
    set(${D_VAR} "" PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-key" "no key found")
    return()
  endif()
  dict_get_scope_range(POS1 _start POS2 _end DICT ${D_DICT} INDEX ${_keypos})
  if(_start EQUAL -1 OR _end EQUAL -1)
    set(${D_VAR} "" PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-scope" "no scope found")
    return()
  endif()
  dict_enumerate_kvps(VAR _kvps DICT ${D_DICT})
  dict_get_kvp(VAR _kvp ARR _kvps KEY ${D_KEY})
  dict_kvp_get_value(VAR ${D_VAR} KVP ${_kvp})
endfunction()
  
  



#[[
dict_is_valid(VAR <out-var> DICT <dict-var>)
  Check if a dictionary is valid
  returns 1 if valid, 0 otherwise
  Arguments:
    VAR <out-var>: the variable to store the result
    DICT <dict-var>: the dictionary to check
]]
function(dict_is_valid)
  set(options)
  set(oneValueArgs VAR DICT)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "args = '${ARGV}'")
  if(NOT D_DICT)
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-no-dict" "variable was not set. returning FALSE")
    return()
  endif()
  if(NOT D_DICT MATCHES "^${_o_ob}.*${_o_cb}$")
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-missing-brace" "string does not pass basic JSON format check. returning FALSE")
    return()
  endif()
  set(_dict "${D_DICT}")
  string(STRIP "${_dict}" _dict)
  set(_curly_open_count 0)
  set(_curly_close_count 0)
  set(_square_open_count 0)
  set(_square_close_count 0)
  set(_key_sep_count 0)
  set(_key_count 0)
  set(_value_count 0)
  set(_comma_count 0)
  set(_quote_count 0)
  set(_parent_context "OBJECT") # can be OBJECT or ARRAY
  set(_cursor_pos 0)
  string(LENGTH "${_dict}" _dict_len)
  # Scan ahead for tokens. If a token is encountered, look behind to check for \\ escape char.
  while(_cursor_pos LESS ${_dict_len})
    string(SUBSTRING "${_dict}" ${_cursor_pos} 1 _char)
    unset(_iterator_name)
    if(_char STREQUAL _o_ob)
      set(_iterator_name _curly_open_count)
    elseif(_char STREQUAL _o_cb)
      set(_iterator_name _curly_close_count)
    elseif(_char STREQUAL _a_ob)
      set(_iterator_name _square_open_count)
      set(_parent_context "ARRAY")
    elseif(_char STREQUAL _a_cb)
      set(_iterator_name _square_close_count)
      set(_parent_context "OBJECT")
    elseif(_char STREQUAL _k_sep)
      set(_iterator_name _key_sep_count)
      if(_parent_context STREQUAL "ARRAY")
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-token" "kvp separator token found in array context. returning FALSE")
        set(${D_VAR} FALSE PARENT_SCOPE)
        return()
      endif()
    elseif(_char STREQUAL _v_sep)
      set(_iterator_name _comma_count)
    elseif(_char STREQUAL _q)
      set(_iterator_name _quote_count)
    endif()
    if(_iterator_name)
      # we found a token
      set(_lastchar)
      if(_cursor_pos GREATER 0)
        math(EXPR _lastchar_pos "${_cursor_pos} - 1")
        string(SUBSTRING "${_dict}" ${_lastchar_pos} 1 _lastchar)
      endif()
      set(_pass_checks TRUE)
      # MATCH "  <-lots of edge cases for this
      # when " is matched, cursor will jump to end of string after validating the contents.
      if(_char STREQUAL _q)
        if(_lastchar STREQUAL _esc)
          _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-token" "escaped quote token found outside of string. returning FALSE")
          set(${D_VAR} FALSE PARENT_SCOPE)
          return()
        endif()
        find_matching_token(VAR _closingpos STR "${_dict}" OPEN "${_q}" CLOSE "${_q}" START ${_cursor_pos})
        if(_closingpos EQUAL -1)
          _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-unmatched-quote" "could not find closing quote. returning FALSE")
          set(${D_VAR} FALSE PARENT_SCOPE)
          return()
        else()
          # lookahead to check for : token after str
          math(EXPR _endquote_pos "${_closingpos} + 1")
          string(SUBSTRING "${_dict}" ${_endquote_pos} 1 _after_endquote_char)
          if(_after_endquote_char STREQUAL ${_k_sep})
            if(_parent_context STREQUAL "ARRAY")
              _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-token" "kvp separator token found in array context. returning FALSE")
              set(${D_VAR} FALSE PARENT_SCOPE)
              return()
            endif()
            math(EXPR _kslen "${_endquote_pos} - ${_cursor_pos}")
            string(SUBSTRING "${_dict}" ${_cursor_pos} ${_kslen} _keystr)
            dict_valid_key(STR "${_keystr}" VAR _valid_keystr)
            if(NOT _valid_keystr)
              _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-keystr" "illegal symbol found in keystring. returning FALSE")
              set(${D_VAR} FALSE PARENT_SCOPE)
              return()
            endif()
            math(EXPR _key_count "${_key_count} + 1")
            # we only count values when checking comma and end brace.
          endif()
        endif()
        math(EXPR _cursor_pos "${_closingpos} + 1")
        set(_pass_checks TRUE)
      elseif(_char IN_LIST "${_o_ob};${_a_ob}")
        # match { or [. Fewer edge cases here. Just check that a matching brace exists.
        # also check value validity between : or , and closing brace
        set(_cchar) # close bracket char
        if(_char STREQUAL _o_ob)
          set(_cchar ${_o_cb})
        else()
          set(_cchar ${_a_cb})
        endif()
        find_matching_token(VAR _closingpos STR "${_dict}" OPEN "${_char}" CLOSE "${_cchar}" START ${_cursor_pos})
        if(_closingpos EQUAL -1)
          _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-unmatched-brace" "could not find matching '${_cchar}' token for '${_char}'. returning FALSE")
          set(${D_VAR} FALSE PARENT_SCOPE)
          return()
        endif()
        # check for valid value between : or , and closing brace
        math(EXPR _bracelen "${_closingpos} - ${_cursor_pos}")
        string(SUBSTRING "${_dict}" ${_cursor_pos} ${_bracelen} _bracestr)
        # get last element in _bracestr
        string(REGEX MATCHALL "[^,]+" _bracestr_elements "${_bracestr}")
        list(GET _bracestr_elements -1 _last_element)
        if(_last_element)
          if(_char STREQUAL "[")
            dict_valid_value(STR "${_last_element}" VAR _valid_value)
            if(NOT _valid_value)
              _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-value" "invalid value found. returning FALSE")
              set(${D_VAR} FALSE PARENT_SCOPE)
              return()
            endif()
          else()
            # find : token after keystring
            find_matching_token(VAR _endquotepos STR "${_last_element}" OPEN "${_q}" CLOSE "${_q}" START 0)
            if(_endquotepos EQUAL -1)
              _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-unmatched-quote" "could not find closing quote. returning FALSE")
              set(${D_VAR} FALSE PARENT_SCOPE)
              return()
            endif()
            math(EXPR _colonpos "${_endquotepos} + 1")
            string(SUBSTRING "${_last_element}" ${_colonpos} 1 _colon)
            if(NOT _colon STREQUAL ${_k_sep})
              _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-token" "kvp separator token not found. returning FALSE")
              set(${D_VAR} FALSE PARENT_SCOPE)
              return()
            endif()
          endif()
          math(EXPR _value_count "${_value_count} + 1")
        endif()
        set(_pass_checks TRUE)
      elseif(_char STREQUAL "${_v_sep}")
        
      endif()
      if(_pass_checks)
        math(EXPR ${_iterator_name} "${${_iterator_name}} + 1")
      endif()
    endif()
    set(_nextchar)
    if(_cursor_pos LESS ${_dict_len})
      math(EXPR _nextchar_pos "${_cursor_pos} + 1")
      string(SUBSTRING "${_dict}" ${_nextchar_pos} 1 _nextchar)
    endif()
    if(_char STREQUAL _v_sep AND _lastchar IN_LIST "${_o_cb};${_a_cb};${_q};0;1;2;3;4;5;6;7;8;9")
      # last char is a type of closing bracket, a number or an end-quote. (any valid terminated value)
      if(NOT _nextchar OR NOT _nextchar IN_LIST "${_q};${_a_ob};${_o_ob};0;1;2;3;4;5;6;7;8;9")
        set(${D_VAR} FALSE PARENT_SCOPE)
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-invalid-trailing-comma-char" "invalid character found after comma. returning FALSE")
        return()
      endif()
    endif()
    math(EXPR _cursor_pos "${_cursor_pos} + 1")
  endwhile()
  
  set(_quote_key_expected_count 0)
  math(EXPR _quote_key_expected_count "${_key_count} * 2")
  math(EXPR _quote_even "${_quote_count} % 2")
  if(NOT _curly_open_count EQUAL _curly_close_count)
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-mismatch" "curly brace count mismatch. returning FALSE")
    return()
  elseif(NOT _square_open_count EQUAL _square_close_count)
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-mismatch" "square bracket count mismatch. returning FALSE")
    return()
  elseif(NOT _key_sep_count EQUAL _key_count)
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-mismatch" "key/colon count mismatch. returning FALSE")
    return()
  elseif(NOT _quote_even EQUAL 0 OR _quote_count LESS _quote_key_expected_count)
    set(${D_VAR} FALSE PARENT_SCOPE)
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result-mismatch" "quote count mismatch. returning FALSE")
    return()
  endif()
  set(${D_VAR} 1 PARENT_SCOPE)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "dictionary is valid. returning 1")
endfunction()
  
  
  
  



#[[
dict_set(SET: VAR <dict-var> KEY: STRING <key> VALUE: STRING <value>)
  Arguments:
    <dict-var> - the name of the dictionary variable to push a key-value-pair to
    <key> - the key to set in the dictionary. The key may define a recursive structure by including a dot '.'
            followed by more alphanumeric characters. For example, 'foo.bar' will create an entry in the 
            dictionary with the following structure: {'foo': {'bar': <value>}}
            If the key already exists, the value will be overwritten.
    <value> - the value assigned to the key
]]
function(dict_set)
  set(options)
  set(oneValueArgs DICT KEY VALUE)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "args = '${ARGV}'")
  set(_dict_var ${D_SET})
  set(_key ${D_KEY})
  set(_value ${D_VALUE})
  set(_dict ${${D_SET}})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "dict var = '${_dict_var}', dict = '${_dict}'")
  set(_valid)
  dict_is_valid(VAR _valid DICT ${_dict})
  if(NOT _valid)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-dictionary" "the dict must be a valid dictionary")
  endif()

  # parse key (and possible path) to see if a dict entry already exists
  string(REGEX MATCHALL "[^\.]+" _key_parts "${_key}")
  # check if there are any empty elements, indicating an invalid key
  list(FIND _key_parts "" _empty_key_part)
  if(_empty_key_part GREATER -1)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "(SET ${_dict_var} KEY ${_key} VALUE ${_value})" "invalid key")
  endif()
  # get size of path
  list(LENGTH _key_parts _key_parts_len)
  # recursively search _dict for the key path
  set(_dict_body ${_dict})
  set(_dict_body_path "")
  set(_dict_body_ext_l "")
  set(_dict_body_ext_r "")
  set(_dict_body_len)
  string(LENGTH "${_dict_body}" _dict_body_len)
  # break open outer brackets before iterating over kvp's
  string(FIND ${_dict_body} ${_o_cb} _obpos)
  if(_obpos GREATER -1)
    string(SUBSTRING ${_dict_body} 0 ${_obpos} _dict_body_ext_l)
  endif()
  find_matching_token(VAR _cbpos STR ${_dict_body} OPEN ${_o_ob} CLOSE ${_o_cb})
  if(_cbpos GREATER -1 AND NOT _cbpos EQUAL ${_dict_body_len})
    math(EXPR _cbposend "${_cbpos} + 1")
    string(SUBSTRING ${_dict_body} ${_cbposend} -1 _dict_body_ext_r)
  endif()
  string(SUBSTRING ${_dict_body} ${_obpos} ${_cbpos} _dict_body)
  set(_iter 0)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "preprocessing" "dict body = '${_dict_body}'")
  foreach(_key_part ${_key_parts})
    # now we have the dict body. If it is empty or only whitespace, generate kvp
    _d_dbg("${CMAKE_CURRENT_FUNCTION}" "begin loop" "dict body = '${_dict_body}'")
    string(STRIP "${_dict_body}" _dict_body)
    if(NOT _dict_body)
      # if the dict body is empty, we need to generate a kvp
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "dict body is empty, generating...")
      if(${_key_parts_len} GREATER 1)
        # if the key path is longer than one element, we need to generate another dict.
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "key path is longer than one element. Generating dict")
        # append "key":{ to lhs and prepend } to rhs
        string(APPEND _dict_body_ext_l "${_q}${_key_part}${_q}${_k_sep}${_o_ob}")
        string(PREPEND _dict_body_ext_r "${_o_cb}")
      else()
        # if the key path is only one element, we can generate a kvp
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "processing" "leaf key reached. Generating kvp")
        set(_dict_body "${_q}${_key_part}${_q}${_k_sep}${_q}${_value}${_q}")
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "success" "dict body = '${_dict_body}'")
        set(_key_found TRUE)
      endif()
    else()
      # if the dict body is not empty, search for the key and store the kvp.
      # We need to check brackets to make sure we don't match a key in a nested dict
      set(_key_found FALSE)
      while(NOT _key_found)
        string(LENGTH _dict_body _dict_body_len)
        # find position of key up to colon
        string(FIND "${_dict_body}" "${_q}${_key_part}${_q}${_k_sep}" _key_pos)
        if(_key_pos EQUAL -1)
          # if the key is not found, we need to generate a kvp at the end of the body
          if(${_key_parts_len} GREATER 1)
            # if the key path is longer than one element, we need to generate another dict
            # append "key":{ to lhs and prepend } to rhs
            string(APPEND _dict_body_ext_l "${_q}${_key_part}${_q}${_k_sep}${_o_ob}")
            string(PREPEND _dict_body_ext_r "${_o_cb}")
          else()
            # if the key path is only one element, we can generate a kvp
            string(APPEND _dict_body "${_v_sep}${_q}${_key_part}${_q}${_k_sep}${_q}${_value}${_q}")
          endif()
          set(_key_found TRUE)
        else()
          # if the key is found, we need to check if it is in a nested dict or array
          # first, get positions of open and close curly/square brackets ahead of key position.
          # If we find a close bracket before an open bracket, reject the key and
          # append everything up to the close bracket to the lhs and continue searching
          string(FIND "${_dict_body}" "${_o_ob}" _dict_body_open_bracket_pos ${_key_pos})
          string(FIND "${_dict_body}" "${_o_cb}" _dict_body_close_bracket_pos ${_key_pos})
          string(FIND "${_dict_body}" "${_a_ob}" _array_body_open_bracket_pos ${_key_pos})
          string(FIND "${_dict_body}" "${_a_cb}" _array_body_close_bracket_pos ${_key_pos})
          if(${_dict_body_close_bracket_pos} LESS ${_dict_body_open_bracket_pos} AND NOT ${_dict_body_close_bracket_pos} EQUAL -1)
            math(EXPR _dict_body_close_bracket_pos "${_dict_body_close_bracket_pos} + 1")
            string(SUBSTRING "${_dict_body}" 0 ${_dict_body_close_bracket_pos} _body_ext_l)
            string(APPEND _dict_body_ext_l "${_body_ext_l}")
            string(SUBSTRING "${_dict_body}" ${_dict_body_close_bracket_pos} -1 _dict_body)
          elseif(${_array_body_close_bracket_pos} LESS ${_array_body_open_bracket_pos} AND NOT ${_array_body_close_bracket_pos} EQUAL -1)
            math(EXPR _array_body_close_bracket_pos "${_array_body_close_bracket_pos} + 1")
            string(SUBSTRING "${_dict_body}" 0 ${_array_body_close_bracket_pos} _body_ext_l)
            string(APPEND _dict_body_ext_l "${_body_ext_l}")
            string(SUBSTRING "${_dict_body}" ${_array_body_close_bracket_pos} -1 _dict_body)
          else()
            # if the key is not in a nested dict or array, we can store the kvp
            # append everything up to the key to the lhs
            string(SUBSTRING "${_dict_body}" 0 ${_key_pos} _body_ext_l)
            string(APPEND _dict_body_ext_l "${_body_ext_l}")
            string(SUBSTRING "${_dict_body}" ${_key_pos} -1 _dict_body)
            # find the end position of the kvp. If this is the leaf key, we will simply
            # overwrite the kvp.
            if(${_key_parts_len} GREATER 1)
              # if the key path is longer than one element, we need to generate another dict
              # append "key":{ to lhs and prepend } to rhs
              string(APPEND _dict_body_ext_l "${_q}${_key_part}${_q}${_k_sep}${_o_ob}")
              string(PREPEND _dict_body_ext_r "${_o_cb}")
            else()
              # If colon pos+1 is a quote, we need to find the next quote
              # if colon pos+1 is a curly bracket, we need to find the matching closing bracket.
              # if colon pos+1 is a square bracket, we need to find the matching closing bracket.
              string(FIND "${_dict_body}" "${_k_sep}" _colon_pos)
              math(EXPR _colon_pos "${_colon_pos} + 1")
              string(SUBSTRING "${_dict_body}" ${_colon_pos} 1 _colon_pos_char)
              set(_val_endpos -1)
              if(${_colon_pos_char} STREQUAL ${_q})
                string(FIND "${_dict_body}" "${_q}" _val_endpos ${_colon_pos})
              elseif(${_colon_pos_char} STREQUAL ${_o_ob})
                find_matching_token(VAR _val_endpos STR "${_dict_body}" OPEN "${_o_ob}" CLOSE "${_o_cb}" START ${_colon_pos})
              elseif(${_colon_pos_char} STREQUAL ${_a_ob})
                find_matching_token(VAR _val_endpos STR "${_dict_body}" OPEN "${_a_ob}" CLOSE "${_a_cb}" START ${_colon_pos})
              endif()
              if(${_val_endpos} EQUAL -1)
                # if we can't find the end of the value, body is malformed
                _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-dictionary" "Malformed body: '${_dict_body}'")
              else()
                # prepend everything after the kvp to the rhs
                math(EXPR _val_endpos "${_val_endpos} + 1")
                string(SUBSTRING "${_dict_body}" ${_val_endpos} -1 _body_ext_r)
                string(PREPEND _dict_body_ext_r "${_body_ext_r}")
                set(_key_found TRUE)
              endif()
            endif()
          endif()
        endif()
      endwhile()
    endif()
    math(EXPR _key_parts_len "${_key_parts_len} - 1")
    math(EXPR _iter "${_iter} + 1")
  endforeach()
  # join the lhs and rhs
  string(APPEND _dict_body_ext_l "${_dict_body}" "${_dict_body_ext_r}")
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "${D_SET} = '${_dict_body_ext_l}'")
  set(${D_SET} "${_dict_body_ext_l}" PARENT_SCOPE)
endfunction()

 

#[[
dict(SET <dict-var>)
  Creates an empty dictionary string. If the string is already valid dictionary, it is left as-is.
  Arguments:
    <dict-var> - the name of the variable to set to the empty dictionary
dict(SET <dict-var> KEY <key> VALUE <value>)
  Sets a key in a dictionary string.
  Arguments:
    <dict-var> - the name of the dictionary variable to push a key-value-pair to
    <key> - the key to set in the dictionary. The key may define a recursive structure by including a dot '.'
            followed by more alphanumeric characters. For example, 'foo.bar' will create an entry in the 
            dictionary with the following structure: {'foo': {'bar': <value>}}
            If the key already exists, the value will be overwritten.
    <value> - the value assigned to the key
dict(POP <dict-var> KEY)
  Removes a key from a dictionary string.
  Arguments:
    <dict-var> - the name of the dictionary variable to pop a key-value-pair from
    <key> - the key to pop from the dictionary. The key may define a recursive structure by including a dot '.'
            followed by more alphanumeric characters. For example, 'foo.bar' will pop the key 'bar' from the
            dictionary with the following structure: {'foo': {'bar': <value>}}. 'foo' will remain in the dictionary.
]]
function(dict)
  set(options)
  set(oneValueArgs
      #[[commands:]] SET POP
      #[[args:]]     KEY VALUE)
  set(multiValueArgs)
  cmake_parse_arguments(D "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "start" "args = '${ARGV}'")
  # store specified commands in list for ease of diagnostic error checking
  set(_commands SET POP)
  # check how many commands are present. It must be only 1 to be valid.
  set(_command_count 0)
  foreach(_command ${_commands})
    if(D_${_command})
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "parsing-args" "found command '${_command}'")
      math(EXPR _command_count "${_command_count} + 1")
    endif()
  endforeach()
  if(${_command_count} EQUAL 0)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "a command must be present, followed by arguments")
  elseif(${_command_count} GREATER 1)
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "only one command may be specified")
  endif()
  set(_varname)
  set(_cmd)
  foreach(_command ${_commands})
    if(D_${_command})
      set(_varname ${D_${_command}})
      set(_cmd ${_command})
      break()
    endif()
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "a command must be present, followed by arguments")
  endforeach()
  set(_dict "${${_varname}}")
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "info" "varname = '${_varname}', val = '${_dict}'")
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "execute" "command: '${_cmd}'")
  
  if(D_SET)
    if(NOT D_KEY AND NOT D_VALUE)
      dict_is_valid(VAR _is_valid STR "${_dict}")
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "SET-no-args" "SET called with no args. Validating dictionary")
      if(${_is_valid})
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "SET-result" "dictionary already exists, leaving as-is")
        return()
      else()
        _d_dbg("${CMAKE_CURRENT_FUNCTION}" "SET-result" "dictionary does not exist or is invalid, creating empty dictionary")
        set(_dict "${_o_ob}${_o_cb}")
      endif()
    elseif(NOT D_KEY)
      _d_err("${CMAKE_CURRENT_FUNCTION}" "SET-invalid-args" "SET called with no key")
    elseif(NOT D_VALUE)
      _d_err("${CMAKE_CURRENT_FUNCTION}" "SET-invalid-args" "SET called with no value")
    else()
      _d_dbg("${CMAKE_CURRENT_FUNCTION}" "SET-args" "arguments provided. Will set key-value-pair.")
      dict_set(DICT _dict KEY ${D_KEY} VALUE ${D_VALUE})
    endif()
  elseif(D_POP)
    dict_pop(DICT ${_dict} KEY ${D_KEY})
  else()
    _d_err("${CMAKE_CURRENT_FUNCTION}" "invalid-arguments" "a command must be present, followed by arguments")
  endif()
  set(${_varname} "${_dict}" PARENT_SCOPE)
  _d_dbg("${CMAKE_CURRENT_FUNCTION}" "result" "${_varname} = '${_dict}'")
endfunction()
