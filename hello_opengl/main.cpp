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
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // set clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // opengl objects
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind vertex arrays
    glBindVertexArray(VAO);

    // set up buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // set up shaders
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    {
        const char *vertex_shader_source_ptr = vertex_shader_source.data();
        glShaderSource(vertex_shader, 1, &vertex_shader_source_ptr, nullptr);
        glCompileShader(vertex_shader);

        int success;
        char info_log[512];
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << info_log << std::endl;
        }
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    {
        const char *fragment_shader_source_ptr = fragment_shader_source.data();
        glShaderSource(fragment_shader, 1, &fragment_shader_source_ptr,
                       nullptr);
        glCompileShader(fragment_shader);

        int success;
        char info_log[512];
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << info_log << std::endl;
        }
    }

    // set up shader program
    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    {
        int success;
        char info_log[512];
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
            std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                      << info_log << std::endl;
        }
    }

    // clean shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // link vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // set up something for drawing
    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

        // clear viewport with specified color
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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