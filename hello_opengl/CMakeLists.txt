cmake_minimum_required(VERSION 3.10)

add_executable(
    hello_opengl

    ${LO_GLOBAL_SOURCE}
    main.cpp
)

target_include_directories(
    hello_opengl
    PUBLIC
    ${LO_GLOBAL_INCLUDE}
)

target_link_libraries(
    hello_opengl
    PRIVATE
    glfw
)