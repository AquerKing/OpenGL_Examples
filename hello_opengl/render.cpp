#include "render.h"

#include <vector>
#include <string>

std::vector<float> vertices = {
    // clang-format off
    // -0.5f, -0.5f, 0.0f,
    //  0.5f, -0.5f, 0.0f,
    //  0.0f,  0.5f, 0.0f,
    -0.5f,  0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
    // clang-format on
};

std::vector<unsigned int> indices = {0, 3, 1, 1, 3, 2};

std::string vertex_shader_source = R"(

#version 430 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}

)";

std::string fragment_shader_source = R"(

#version 430 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

)";