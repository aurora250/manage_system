# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_INNOSETUP "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system;D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENTS_ALL "Unspecified;devel")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/Qt/Tools/CMake_64/share/cmake-3.29/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "manage_system built using CMake")
set(CPACK_GENERATOR "7Z;ZIP")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALLED_DIRECTORIES "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/manage_system")
set(CPACK_MODULE_PATH "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/cmake/modules")
set(CPACK_NSIS_DISPLAY_NAME "manage_system 0.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "manage_system 0.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "D:/Qt/Tools/mingw1120_64/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "D:/Qt/Tools/mingw1120_64/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Daniel Nicoletti <dantti12@gmail.com>")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/Qt/Tools/CMake_64/share/cmake-3.29/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QXlsx library.")
set(CPACK_PACKAGE_FILE_NAME "manage_system-0.1-Source")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "manage_system 0.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "manage_system 0.1")
set(CPACK_PACKAGE_NAME "manage_system")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Daniel Nicoletti")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_READELF_EXECUTABLE "D:/Qt/Tools/mingw1120_64/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "D:/Qt/Tools/CMake_64/share/cmake-3.29/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/QXlsx/../README.md")
set(CPACK_RESOURCE_FILE_WELCOME "D:/Qt/Tools/CMake_64/share/cmake-3.29/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "manage_system-0.1-Source")
set(CPACK_SOURCE_TOPLEVEL_TAG "win64-Source")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "D:/Workspace/Cpp Workspace/Qt Workspace/manage_system/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
