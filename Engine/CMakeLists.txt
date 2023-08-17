set(MODULE_NAME Engine)
project(${MODULE_NAME} VERSION 0.1.0 LANGUAGES CXX)

####################
### Source files ###
####################
set(MODULE_CORE     ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(MODULE_EVENTS   ${CMAKE_CURRENT_SOURCE_DIR}/src/Events)
set(MODULE_PLATFORMS   ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms)

add_library(${MODULE_NAME} SHARED
    # Precompiled header
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h

    ${MODULE_CORE}/Core.h
    ${MODULE_CORE}/Log.h            ${MODULE_CORE}/Log.cpp
    ${MODULE_CORE}/Application.h    ${MODULE_CORE}/Application.cpp
    ${MODULE_CORE}/EntryPoint.h

    ${MODULE_EVENTS}/ApplicationEvent.h
    ${MODULE_EVENTS}/Event.h
    ${MODULE_EVENTS}/KeyEvent.h
    ${MODULE_EVENTS}/MouseEvent.h

    # Window
    ${MODULE_CORE}/Window.h
    ${MODULE_PLATFORMS}/LinuxWindow.h ${MODULE_PLATFORMS}/LinuxWindow.cpp
)

target_include_directories(${MODULE_NAME} PRIVATE
    src
    #${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
)

target_precompile_headers(${MODULE_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h
)

####################
### Dependencies ###
####################

# GLFW
add_subdirectory(vendor/glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")

# spdlog
add_subdirectory(vendor/spdlog)
target_compile_options(spdlog PRIVATE -fPIC)

target_link_libraries(${MODULE_NAME} PRIVATE
    spdlog
    glfw
)
