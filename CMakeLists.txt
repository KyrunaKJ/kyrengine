cmake_minimum_required(VERSION 3.17)

project (test LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_definitions(-DCMAKE_BUILD)

add_executable(test ${SOURCES})

# Link GLFW, GLEW, and any other necessary libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(test glfw GLEW /usr/lib/x86_64-linux-gnu/libGL.so.1)