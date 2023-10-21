set(MODULE_NAME Engine)
project(${MODULE_NAME} VERSION 0.1.0 LANGUAGES CXX)

add_compile_definitions(KD_ENABLE_ASSERTS)

####################
### Source files ###
####################
set(MODULE_VENDOR       ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

add_library(${MODULE_NAME} STATIC
    # Precompiled header
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h
    
    # Vendor
    # TODO: Fix cmakelists so we dont need to add the internal imgui code to our library.
    ${MODULE_VENDOR}/imgui/backends/imgui_impl_glfw.h       ${MODULE_VENDOR}/imgui/backends/imgui_impl_glfw.cpp
    ${MODULE_VENDOR}/imgui/backends/imgui_impl_opengl3.h    ${MODULE_VENDOR}/imgui/backends/imgui_impl_opengl3.cpp
    ${MODULE_VENDOR}/stb/stb_image.h                        ${MODULE_VENDOR}/stb/stb_image.cpp
)
    
target_include_directories(${MODULE_NAME} PUBLIC
    include
    src
    vendor
)

target_precompile_headers(${MODULE_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h
)

####################
### Dependencies ###
####################

# Find dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

add_subdirectory(vendor/glad)
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory(vendor/imgui)
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
target_compile_options(imgui PRIVATE -fPIC)

add_subdirectory(vendor/entt)

# Custom modules
add_subdirectory(src/Core)
add_subdirectory(src/Debug)
add_subdirectory(src/Events)
add_subdirectory(src/ImGui)
add_subdirectory(src/Platforms)
add_subdirectory(src/Renderer)
add_subdirectory(src/Scene)

target_link_libraries(${MODULE_NAME} PUBLIC 
# External modules
    glad
    glfw
    spdlog
    OpenGL::GL
    imgui
    glm
    entt

# Custom modules
    core
    debug
    events
    kaydee_imgui
    platforms_linux
    platforms_opengl
    renderer
    scene
)
