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

    # Core
    ${MODULE_CORE}/Core.h
    ${MODULE_CORE}/Log.h            ${MODULE_CORE}/Log.cpp
    ${MODULE_CORE}/Application.h    ${MODULE_CORE}/Application.cpp
    ${MODULE_CORE}/EntryPoint.h
    ${MODULE_CORE}/Layer.h          ${MODULE_CORE}/Layer.cpp
    ${MODULE_CORE}/LayerStack.h     ${MODULE_CORE}/LayerStack.cpp

    # Events
    ${MODULE_EVENTS}/ApplicationEvent.h
    ${MODULE_EVENTS}/Event.h
    ${MODULE_EVENTS}/KeyEvent.h
    ${MODULE_EVENTS}/MouseEvent.h

    # Window
    ${MODULE_CORE}/Window.h
    ${MODULE_PLATFORMS}/Linux/LinuxWindow.h ${MODULE_PLATFORMS}/Linux/LinuxWindow.cpp

    # OpenGL
    ${MODULE_PLATFORMS}/OpenGL/ImGuiOpenGLRenderer.h ${MODULE_PLATFORMS}/OpenGL/ImGuiOpenGLRenderer.cpp

    # ImGui Library
    ${IMGUI_SOURCES}
    
    # Imgui
    ${MODULE_IMGUI}/ImGuiLayer.h    ${MODULE_IMGUI}/ImGuiLayer.cpp
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
)
