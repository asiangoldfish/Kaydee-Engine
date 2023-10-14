set(MODULE_NAME Engine)
project(${MODULE_NAME} VERSION 0.1.0 LANGUAGES CXX)

add_compile_definitions(KD_ENABLE_ASSERTS)

####################
### Source files ###
####################
set(MODULE_CORE         ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(MODULE_EVENTS       ${CMAKE_CURRENT_SOURCE_DIR}/src/Events)
set(MODULE_IMGUI        ${CMAKE_CURRENT_SOURCE_DIR}/src/ImGui)
set(MODULE_PLATFORMS    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platforms)
set(MODULE_RENDERER     ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer)
set(MODULE_DEBUG        ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
set(MODULE_VENDOR       ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(MODULE_UTILS        ${CMAKE_CURRENT_SOURCE_DIR}/Utils)

add_library(${MODULE_NAME} STATIC
    # Precompiled header
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h

    # Core
    ${MODULE_CORE}/Core.h
    ${MODULE_CORE}/Log.h                                    ${MODULE_CORE}/Log.cpp
    ${MODULE_CORE}/Application.h                            ${MODULE_CORE}/Application.cpp
    ${MODULE_CORE}/EntryPoint.h                             ${MODULE_CORE}/EntryPoint.cpp
    ${MODULE_CORE}/Layer.h                                  ${MODULE_CORE}/Layer.cpp
    ${MODULE_CORE}/LayerStack.h                             ${MODULE_CORE}/LayerStack.cpp
    ${MODULE_CORE}/Timestep.h                               ${MODULE_CORE}/Timestep.cpp
    ${MODULE_CORE}/Input.h
    
    ${MODULE_CORE}/Window.h
    
    # Events
    ${MODULE_EVENTS}/ApplicationEvent.h
    ${MODULE_EVENTS}/Event.h
    ${MODULE_EVENTS}/KeyEvent.h
    ${MODULE_EVENTS}/MouseEvent.h
    
    # Platforms
    ${MODULE_PLATFORMS}/Linux/LinuxWindow.h                 ${MODULE_PLATFORMS}/Linux/LinuxWindow.cpp
    ${MODULE_PLATFORMS}/Linux/LinuxInput.h                  ${MODULE_PLATFORMS}/Linux/LinuxInput.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLContext.h              ${MODULE_PLATFORMS}/OpenGL/OpenGLContext.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLBuffer.h               ${MODULE_PLATFORMS}/OpenGL/OpenGLBuffer.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLRendererAPI.h          ${MODULE_PLATFORMS}/OpenGL/OpenGLRendererAPI.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLVertexArray.h          ${MODULE_PLATFORMS}/OpenGL/OpenGLVertexArray.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLShader.h               ${MODULE_PLATFORMS}/OpenGL/OpenGLShader.cpp
    ${MODULE_PLATFORMS}/OpenGL/OpenGLTexture.h              ${MODULE_PLATFORMS}/OpenGL/OpenGLTexture.cpp
    
    # Imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui # Lib
    ${MODULE_IMGUI}/ImGuiLayer.h                            ${MODULE_IMGUI}/ImGuiLayer.cpp
    ${MODULE_IMGUI}/ImGuiBuild.cpp
    
    # Renderer
    ${MODULE_RENDERER}/Buffer.h                             ${MODULE_RENDERER}/Buffer.cpp
    ${MODULE_RENDERER}/GraphicsContext.h                    ${MODULE_RENDERER}/GraphicsContext.cpp
    ${MODULE_RENDERER}/Renderer.h                           ${MODULE_RENDERER}/Renderer.cpp
    ${MODULE_RENDERER}/VertexArray.h                        ${MODULE_RENDERER}/VertexArray.cpp
    ${MODULE_RENDERER}/RendererAPI.h                        ${MODULE_RENDERER}/RendererAPI.cpp
    ${MODULE_RENDERER}/Shader.h                             ${MODULE_RENDERER}/Shader.cpp
    ${MODULE_RENDERER}/RenderCommand.h                      ${MODULE_RENDERER}/RenderCommand.cpp
    ${MODULE_RENDERER}/OrthographicCamera.h                 ${MODULE_RENDERER}/OrthographicCamera.cpp
    ${MODULE_RENDERER}/Texture.h                            ${MODULE_RENDERER}/Texture.cpp
    ${MODULE_RENDERER}/SubTexture2D.h                       ${MODULE_RENDERER}/SubTexture2D.cpp
    ${MODULE_RENDERER}/OrthographicCameraController.h       ${MODULE_RENDERER}/OrthographicCameraController.cpp
    ${MODULE_RENDERER}/Renderer2D.h                         ${MODULE_RENDERER}/Renderer2D.cpp
    
    # Vendor
    ${MODULE_VENDOR}/imgui/backends/imgui_impl_glfw.h       ${MODULE_VENDOR}/imgui/backends/imgui_impl_glfw.cpp
    ${MODULE_VENDOR}/imgui/backends/imgui_impl_opengl3.h    ${MODULE_VENDOR}/imgui/backends/imgui_impl_opengl3.cpp
    ${MODULE_VENDOR}/stb/stb_image.h                        ${MODULE_VENDOR}/stb/stb_image.cpp
)
    
target_include_directories(${MODULE_NAME} PRIVATE
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

target_link_libraries(${MODULE_NAME} PUBLIC 
    glad
    glfw
    spdlog
    OpenGL::GL
    imgui
    glm
)
