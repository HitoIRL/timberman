#include "shaders.hpp"

#include <glad/glad.h>

// todo: export to file
constexpr auto Vertex = R"glsl(
#version 460 core

in vec2 position;
in vec3 color;

struct fragmentData {
	vec3 color;
};

out fragmentData data;

out vec3 o_color;

void main() {
	gl_Position = vec4(position, 0.0, 1.0);

    data.color = color;
}
)glsl";

constexpr auto Fragment = R"glsl(
#version 460 core

struct fragmentData {
	vec3 color;
};

in fragmentData data;

out vec4 color;

void main() {
	color = vec4(data.color, 1.0);
}
)glsl";

opengl::shaders::shaders() : program(glCreateProgram()) {
    const auto vertex = createShader(Vertex, GL_VERTEX_SHADER);
    const auto fragment = createShader(Fragment, GL_FRAGMENT_SHADER);

    glLinkProgram(program);

    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

opengl::shaders::~shaders() {
    glDeleteProgram(program);
}

void opengl::shaders::bind(bool state) const {
    // todo: optimize
    glUseProgram(state ? program : 0);
}

std::uint32_t opengl::shaders::createShader(const char *source, std::uint32_t type) const {
    const auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    glAttachShader(program, shader);
    return shader;
}
