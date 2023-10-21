set(MODULE_NAME KaydeeEditor)

add_executable(${MODULE_NAME} 
    EditorLayer.h     EditorLayer.cpp
    KaydeeEditorApp.cpp
)

#############
## Modules
#############
add_subdirectory(src)

#############
## Linking
#############
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

target_compile_definitions(${MODULE_NAME} PRIVATE GAME_ASSETS="assets/game/")

# TODO: Create better and cleaner configuration for Debug and Release mode.
# They must compile on both Linux and MS Windows using Visual Studio 2022
# Output directories
set(BITSIZE 64)
if ( MSVC )
    set_target_properties(
        ${MODULE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}" )
    set_target_properties( 
        ${MODULE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}" )
    set_target_properties( 
        ${MODULE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}" )
    # etc for the other available configuration types (MinSizeRel, RelWithDebInfo)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}")
endif ( MSVC )

# Set CWD
set(CWD "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}${BITSIZE}/${CMAKE_BUILD_TYPE}")

set_target_properties(
    ${MODULE_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CWD}")

# Copy assets directory to binary destination
set (source "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set (destination "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
add_custom_target (COPY_ASSETS_EDITOR
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination}
)
add_dependencies (${MODULE_NAME} COPY_ASSETS)