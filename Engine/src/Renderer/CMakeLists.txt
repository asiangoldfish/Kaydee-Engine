project(renderer)

add_library(${PROJECT_NAME} STATIC
    Buffer.h                             Buffer.cpp
    GraphicsContext.h                    GraphicsContext.cpp
    Renderer.h                           Renderer.cpp
    VertexArray.h                        VertexArray.cpp
    RendererAPI.h                        RendererAPI.cpp
    Shader.h                             Shader.cpp
    RenderCommand.h                      RenderCommand.cpp
    OrthographicCamera.h                 OrthographicCamera.cpp
    Texture.h                            Texture.cpp
    SubTexture2D.h                       SubTexture2D.cpp
    OrthographicCameraController.h       OrthographicCameraController.cpp
    Renderer2D.h                         Renderer2D.cpp
    Framebuffer.h                        Framebuffer.cpp
)

target_include_directories(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

PRIVATE 
	${CMAKE_SOURCE_DIR}/Engine/src
	${CMAKE_SOURCE_DIR}/Engine/vendor
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	spdlog
    glm
    glad

    core
)