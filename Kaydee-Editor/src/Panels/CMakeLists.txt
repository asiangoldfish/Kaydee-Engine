set(MODULE_NAME EditorPanels)

add_library(${MODULE_NAME} STATIC 
    SceneHierarchyPanel.h           SceneHierarchyPanel.cpp
)

################
## Includes
################
target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

################
## Linking
################
target_link_libraries(${MODULE_NAME} PRIVATE
    imgui

    Engine
)