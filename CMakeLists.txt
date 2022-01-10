cmake_minimum_required(VERSION 3.7)

project(TryForC VERSION 1 LANGUAGES NONE)

option(TryForC_DEVELOPER_MODE "Enable developer mode" OFF)

set(TryForC_IS_TOP_LEVEL NO)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(TryForC_IS_TOP_LEVEL YES)
endif()

if(NOT CMAKE_SKIP_INSTALL_RULES)
  set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "")

  include(CMakePackageConfigHelpers)
  include(GNUInstallDirs)

  write_basic_package_version_file(
      TryForCConfigVersion.cmake
      COMPATIBILITY SameMajorVersion
  )

  set(
      TryForC_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/TryForC"
      CACHE PATH "CMake package config location relative to the install prefix"
  )
  mark_as_advanced(TryForC_INSTALL_CMAKEDIR)

  install(
      FILES
      cmake/try.h.in
      cmake/TryForCConfig.cmake
      "${PROJECT_BINARY_DIR}/TryForCConfigVersion.cmake"
      DESTINATION "${TryForC_INSTALL_CMAKEDIR}"
  )
endif()

if(TryForC_IS_TOP_LEVEL AND TryForC_DEVELOPER_MODE)
  include(CTest)
  if(BUILD_TESTING)
    list(APPEND CMAKE_PREFIX_PATH "${PROJECT_BINARY_DIR}")
    configure_file(cmake/try.h.in try.h.in COPYONLY)
    configure_file(cmake/TryForCConfig.cmake TryForCConfig.cmake COPYONLY)
    add_subdirectory(test)
  endif()
endif()
