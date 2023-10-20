project(scene)

add_library(${PROJECT_NAME} STATIC
	Scene.h Scene.cpp
	Components.h
)

target_include_directories(${PROJECT_NAME} 
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

PRIVATE 
	${CMAKE_SOURCE_DIR}/Engine/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	spdlog
	glm
	entt
)