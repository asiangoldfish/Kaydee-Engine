# Define the Events module library
add_library(Events
    ApplicationEvent.h
    Event.h
    KeyEvent.h
    MouseEvent.h
)

# Include directories for KaydeeEvents library
target_include_directories(Events PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    # ... other include directories ...
)

set_target_properties(Events PROPERTIES LINKER_LANGUAGE CXX)
