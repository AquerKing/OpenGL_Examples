cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

set(LO_GLOBAL_INCLUDE "${CMAKE_SOURCE_DIR}/third-party/glad/include")
set(LO_GLOBAL_SOURCE "${CMAKE_SOURCE_DIR}/third-party/glad/src/gl.c")

find_package(glfw3 REQUIRED)

add_subdirectory(hello_opengl)
