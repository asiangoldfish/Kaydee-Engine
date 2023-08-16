# CMakeLists.txt in Kaydee/Core directory

# Define the Core module library
add_library(Core STATIC
    Application.cpp
    Application.h
    EntryPoint.h
    Log.cpp
    Log.h
)

# Include directories for KaydeeCore library
target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    # ... other include directories ...
)
