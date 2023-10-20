project(platforms_linux)

add_library(${PROJECT_NAME} STATIC
	LinuxWindow.h LinuxWindow.cpp
    LinuxInput.cpp
)

target_include_directories(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

PRIVATE 
	${CMAKE_SOURCE_DIR}/Engine/src
	${CMAKE_SOURCE_DIR}/Engine/vendor
)

target_link_libraries(${PROJECT_NAME} PRIVATE
# External	
	spdlog
	glfw
	glm

# Custom
	platforms_opengl
	core
)