#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include <iostream>

#include "render.h"

void Initialize();

GLFWwindow *CreateGLFWWindow(int width, int height, const std::string &title);

void FrameBuffer_Size_Callback(GLFWwindow *window, int width, int height);

void ProcessInput(GLFWwindow *window);

int main() {
    Initialize();

    GLFWwindow *window = CreateGLFWWindow(800, 600, "Hello, OpenGL!");
    assert(window != nullptr);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    // set up frame buffer size callback function
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Size_Callback);

    // set clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // opengl objects
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // set up buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

        // clear viewport with specified color
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void Initialize() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *CreateGLFWWindow(int width, int height, const std::string &title) {
    GLFWwindow *window =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        return window;
    }

    glfwMakeContextCurrent(window);
    return window;
}

void FrameBuffer_Size_Callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) {
        glfwSetWindowShouldClose(window, true);
    }
}