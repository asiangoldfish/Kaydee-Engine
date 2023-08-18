set(MODULE_NAME Engine)
project(${MODULE_NAME} VERSION 0.1.0 LANGUAGES CXX)

add_compile_definitions(KD_ENABLE_ASSERTS)

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
    ${MODULE_CORE}/Layer.h          ${MODULE_CORE}/Layer.cpp
    ${MODULE_CORE}/LayerStack.h     ${MODULE_CORE}/LayerStack.cpp

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
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

# Dear imgui
set(IMGUI_SOURCE_DIR    ${VENDOR_DIR}/imgui)
set(IMGUI_BACKENDS_DIR  ${IMGUI_SOURCE_DIR}/backends)
set(GL3W_SOURCE_DIR     ${IMGUI_LIBS_DIR}/gl3w)
set(GLFW_INCLUDE_DIR    ${IMGUI_LIBS_DIR}/glfw/include)
set(GLFW_LIB            ${IMGUI_LIBS_DIR}/glfw/lib-vc2010-64/glfw3.lib)

set(IMGUI_SOURCES
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PRIVATE
    ${IMGUI_SOURCE_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${GL3W_SOURCE_DIR}
    ${GLFW_INCLUDE_DIR}
)

# Find dependencies

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glad)
add_compile_definitions(GLFW_INCLUDE_NONE)

target_link_libraries(${MODULE_NAME} PUBLIC 
    glad
    glfw
    spdlog::spdlog
    OpenGL::GL
    imgui
)
