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

#####################
### Build options ###
#####################

######################
### Git Submodules ###
######################

# find_package(Git QUIET)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     option(GIT_SUBMODULE "Check submodules during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update")
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                         RESULT_VARIABLE GIT_SUBMOD_RESULT)
#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules!")
#         endif()
#     endif()
# endif()

# # CHECK ALL SUBMODULES
# if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
#     message(FATAL_ERROR "The GLFW submodules was not downloaded! GIT_SUBMODULE was turned off or failed.")
# endif()

# Output directories
set(BITSIZE 64)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}")

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(Sandbox)
