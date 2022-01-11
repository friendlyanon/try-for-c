cmake_minimum_required(VERSION 3.7)

set(_TryForC_DIRECTORY "${CMAKE_CURRENT_LIST_FILE}")
get_filename_component(_TryForC_DIRECTORY "${_TryForC_DIRECTORY}" DIRECTORY)

function(generate_try_for_c)
  set(one_args ERROR_TYPE OK_VALUE INCLUDE_GUARD CUSTOM_CONTENT FILE_NAME IS_ERROR_OP)
  cmake_parse_arguments(PARSE_ARGV 0 TRY "" "${one_args}" HEADERS)

  set(headers "")
  foreach(header IN LISTS TRY_HEADERS)
    string(APPEND headers "#include <${header}>\n")
  endforeach()
  if(NOT headers STREQUAL "")
    string(APPEND headers "\n")
  endif()

  set(is_error_op "((left) != (right))")
  if(DEFINED TRY_IS_ERROR_OP AND NOT TRY_IS_ERROR_OP STREQUAL "")
    set(is_error_op "${TRY_IS_ERROR_OP}")
  endif()

  set(guard_begin "#pragma once\n\n")
  set(guard_end "")
  if(DEFINED TRY_INCLUDE_GUARD AND NOT TRY_INCLUDE_GUARD STREQUAL "")
    set(guard "${TRY_INCLUDE_GUARD}")
    set(guard_begin "#ifndef ${guard}\n#define ${guard}\n\n")
    set(guard_end "\n\n#endif  /* ${guard} */")  
  endif()

  set(custom "")
  if(DEFINED TRY_CUSTOM_CONTENT AND NOT TRY_CUSTOM_CONTENT STREQUAL "")
    set(custom "\n\n${TRY_CUSTOM_CONTENT}")
  endif()

  set(file_name try_for_c/try.h)
  if(DEFINED TRY_FILE_NAME AND NOT TRY_FILE_NAME STREQUAL "")
    set(file_name "${TRY_FILE_NAME}")
  endif()

  configure_file("${_TryForC_DIRECTORY}/try.h.in" "${file_name}" @ONLY)
endfunction()
