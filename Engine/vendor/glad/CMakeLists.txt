project(Glad)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
