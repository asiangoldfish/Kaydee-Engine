project(kaydee_imgui)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/imgui # Lib
    ImGuiLayer.h                            ImGuiLayer.cpp
    ImGuiBuild.cpp
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
	imgui
	glm
	glfw
	glad
)