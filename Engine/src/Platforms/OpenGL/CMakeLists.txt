project(platforms_opengl)

add_library(${PROJECT_NAME} STATIC
    OpenGLContext.h              OpenGLContext.cpp
    OpenGLBuffer.h               OpenGLBuffer.cpp
    OpenGLRendererAPI.h          OpenGLRendererAPI.cpp
    OpenGLVertexArray.h          OpenGLVertexArray.cpp
    OpenGLShader.h               OpenGLShader.cpp
    OpenGLTexture.h              OpenGLTexture.cpp
    OpenGLFramebuffer.h          OpenGLFramebuffer.cpp
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
    glad
    glm
    glfw

    renderer
)