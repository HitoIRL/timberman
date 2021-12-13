#include "shaders.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

// todo: move to file
constexpr auto Vertex = R"glsl(
#version 460 core

in vec2 position;
in vec2 textureCoord;
in float textureIndex;

struct fragmentData {
    vec2 textureCoord;
	float textureIndex;
};

out fragmentData data;

uniform mat4 projection;

void main() {
	gl_Position = projection * vec4(position, 0.0, 1.0);

    data.textureCoord = textureCoord;
	data.textureIndex = textureIndex;
}
)glsl";

constexpr auto Fragment = R"glsl(
#version 460 core

struct fragmentData {
    vec2 textureCoord;
	float textureIndex;
};

in fragmentData data;

out vec4 color;

uniform sampler2D samplers[16];

void main() {
	color = texture(samplers[int(data.textureIndex)], data.textureCoord);
}
)glsl";

opengl::shaders::shaders() : program(glCreateProgram()), binded(false) {
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
    if (binded == state)
        return;

    glUseProgram(state ? program : 0);

    binded = state;
}

std::uint32_t opengl::shaders::createShader(const char *source, std::uint32_t type) const {
    const auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    glAttachShader(program, shader);
    return shader;
}

void opengl::shaders::uniformMat4(std::string_view name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void opengl::shaders::uniform1iv(std::string_view name, int* arr, int size) {
    glUniform1iv(getLocation(name), size, arr);
}

int opengl::shaders::getLocation(std::string_view name) {
    if (cache.contains(name))
        return cache[name];

    int location = glGetUniformLocation(program, name.data());

    cache[name] = location;
    return location;
}