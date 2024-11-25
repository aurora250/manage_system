# Install script for directory: D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/manage_system")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/Qt/Tools/llvm-mingw1706_64/bin/llvm-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/libQXlsxQt6.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QXlsxQt6" TYPE FILE FILES
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxabstractooxmlfile.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxabstractsheet.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxabstractsheet_p.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxcellformula.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxcell.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxcelllocation.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxcellrange.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxcellreference.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxchart.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxchartsheet.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxconditionalformatting.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxdatavalidation.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxdatetype.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxdocument.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxformat.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxglobal.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxrichstring.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxworkbook.h"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/header/xlsxworksheet.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/CMakeFiles/QXlsx.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake"
         "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/QXlsxQt6Config.cmake"
    "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_llvm_mingw_64_bit-Debug/QXlsx/QXlsxQt6ConfigVersion.cmake"
    )
endif()

