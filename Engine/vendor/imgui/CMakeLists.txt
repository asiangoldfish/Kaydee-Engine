cmake_minimum_required(VERSION 3.27)
project(imgui)

file(GLOB IMGUI_SOURCE_FILES
    "*.cpp"
    imgui.h
)

add_library(imgui STATIC ${IMGUI_SOURCE_FILES})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
