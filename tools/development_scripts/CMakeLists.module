# Define the module name
set(MODULE_NAME ${module_name})

# Add all source files in the module directory
file(GLOB_RECURSE SOURCES \${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS \${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Create the module library
add_library(\${MODULE_NAME} \${SOURCES} \${HEADERS})

# Add include directories for the module
target_include_directories(\${MODULE_NAME} PUBLIC \${CMAKE_CURRENT_SOURCE_DIR})

# Link the necessary libraries (e.g., OpenGL, GLAD, GLM)
target_link_libraries(\${MODULE_NAME} PUBLIC OpenGL::GL GLAD::GLAD glm)

# Set any additional compiler flags or options if needed
# target_compile_options(\${MODULE_NAME} PRIVATE ...)

# Set any preprocessor definitions if needed
# target_compile_definitions(\${MODULE_NAME} PRIVATE ...)

# Set the module output directory (optional)
# set_target_properties(\${MODULE_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "\${CMAKE_BINARY_DIR}/modules")
