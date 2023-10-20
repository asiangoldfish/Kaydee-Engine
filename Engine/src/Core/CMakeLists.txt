project(core)

add_library(${PROJECT_NAME} STATIC
    Core.h
    Log.h Log.cpp
    Application.h Application.cpp
    EntryPoint.h EntryPoint.cpp
    Layer.h Layer.cpp
    LayerStack.h LayerStack.cpp
    Timestep.h Timestep.cpp
    Input.h
    Window.h
)

target_include_directories(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

PRIVATE 
	${CMAKE_SOURCE_DIR}/Engine/src
	${CMAKE_SOURCE_DIR}/Engine/vendor
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glm
    glfw
    spdlog
)