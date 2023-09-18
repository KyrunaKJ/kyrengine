cmake_minimum_required(VERSION 3.17)
project (hellogl)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIRS
    src
    src/data
    src/graphics
    src/utils
)

# Add all your source files from these directories
foreach(SOURCE_DIR ${SOURCE_DIRS})
    file(GLOB SOURCES_${SOURCE_DIR} "${SOURCE_DIR}/*.cpp")
    list(APPEND SOURCES ${SOURCES_${SOURCE_DIR}})
endforeach()

add_definitions(-DCMAKE_BUILD)

add_executable(testc ${SOURCES})

# Link GLFW, GLEW, and any other necessary libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(testc glfw GLEW /usr/lib/x86_64-linux-gnu/libGL.so.1)
target_include_directories(testc PRIVATE ${CMAKE_SOURCE_DIR}/include)
