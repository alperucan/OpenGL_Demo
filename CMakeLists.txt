cmake_minimum_required(VERSION 3.0.0)
project(hello_window VERSION 1.0.0)



if(CMAKE_COMPILER_IS_GNUCXX)

endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glfw EXCLUDE_FROM_ALL)

add_executable(hello_window 
    src/config.h 
    src/config.cpp
    src/main.cpp 
    src/glad.c
    src/triangle_mesh.cpp
    src/material.cpp
)

target_include_directories(hello_window PRIVATE dependencies)
target_link_libraries(hello_window glfw OpenGL::GL)
