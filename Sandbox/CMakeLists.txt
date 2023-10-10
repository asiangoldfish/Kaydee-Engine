set(MODULE_NAME Sandbox)

add_executable(${MODULE_NAME} 
    src/Sandbox2D.h     src/Sandbox2D.cpp
    src/SandboxApp.cpp
    src/ExampleLayer.h  src/ExampleLayer.cpp)

target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/include
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor

    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#target_link_libraries(Sandbox PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Kaydee/libEngine.so)
target_link_libraries(${MODULE_NAME} PRIVATE
    Engine
)

# Set CWD
set_target_properties(
    Sandbox PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Copy assets directory to binary destination
set (source "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set (destination "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
add_custom_target (COPY_ASSETS
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination}
)
add_dependencies (${MODULE_NAME} COPY_ASSETS)