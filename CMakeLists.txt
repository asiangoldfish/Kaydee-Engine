###############
### Version ###
###############

cmake_minimum_required(VERSION 3.18)
project(Kaydee VERSION 1.0 LANGUAGES CXX)
configure_file(KaydeeConfig.h.in KaydeeConfig.h)
set(CMAKE_CXX_STANDARD              17  )
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON  )
set(CMAKE_CXX_STANDARD_REQUIRED     ON  )
set(CMAKE_CXX_EXTENSIONS            OFF )

###################
### Build types ###
###################

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# make sure __cplusplus is defined when using msvc and enable parallel build
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME MATCHES "CYGWIN" OR CMAKE_SYSTEM_NAME MATCHES "MSYS")
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

# Enable profiling
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_definitions(KD_PROFILE="1")
endif()

######################
### Master project ###
######################

# Check if Kaydee is used directly or via add_subdirectory. Allow overriding
if(NOT DEFINED KAYDEE_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(KAYDEE_MASTER_PROJECT ON)
    else()
        set(KAYDEE_MASTER_PROJECT OFF)
    endif()
endif()

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(Sandbox)

######################
### Installation   ###
######################
install(
    TARGETS Sandbox
    RUNTIME
    DESTINATION bin
    COMPONENT applications
)

# Define NSIS installation types
set(CPACK_ALL_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_SOURCE_GENERATOR "ZIP")

#set( CPACK_NSIS_CREATE_ICONS_EXTRA 
#"
#CreateShortcut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\SDK Documentation.lnk\\\" \\\"$INSTDIR\\\\doc\\\\html\\\\index.html\\\"
#" )
#
#set( CPACK_NSIS_DELETE_ICONS_EXTRA 
#"
#Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\SDK Documentation.lnk\\\"
#" )

set (CPACK_NSIS_MODIFY_PATH "ON")
#set(CPACK_NSIS_MENU_LINKS ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
include(CPack)