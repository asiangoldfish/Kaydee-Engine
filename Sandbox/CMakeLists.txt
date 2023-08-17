set(MODULE_NAME Sandbox)

add_executable(${MODULE_NAME} src/SandboxApp.cpp)

target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/include
    ${CMAKE_SOURCE_DIR}/Engine/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor
)

find_package(spdlog REQUIRED)


#target_link_libraries(Sandbox PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../Kaydee/libEngine.so)
target_link_libraries(${MODULE_NAME}
    PRIVATE spdlog::spdlog 
    PRIVATE Engine
)
