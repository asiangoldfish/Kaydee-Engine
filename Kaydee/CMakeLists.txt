set(MODULE_NAME Engine)

####################
### Source files ###
####################
set(MODULE_CORE     ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(MODULE_EVENTS   ${CMAKE_CURRENT_SOURCE_DIR}/src/Events)

add_library(${MODULE_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h

    ${MODULE_CORE}/Core.h

    ${MODULE_CORE}/Log.h            ${MODULE_CORE}/Log.cpp
    ${MODULE_CORE}/Application.h    ${MODULE_CORE}/Application.cpp
    
    ${MODULE_CORE}/EntryPoint.h

    ${MODULE_EVENTS}/ApplicationEvent.h
    ${MODULE_EVENTS}/Event.h
    ${MODULE_EVENTS}/KeyEvent.h
    ${MODULE_EVENTS}/MouseEvent.h
)

target_include_directories(${MODULE_NAME} PRIVATE
    src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include

)

target_precompile_headers(${MODULE_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kdpch.h
)

find_package(spdlog REQUIRED)

target_link_libraries(${MODULE_NAME} PRIVATE
    spdlog::spdlog
)