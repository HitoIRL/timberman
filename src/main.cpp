#include "opengl/window.hpp"
#include "opengl/shaders.hpp"

#include <glad/glad.h>

int main() {
    auto window = std::make_unique<opengl::window>("timberman", glm::uvec2(1280, 720));

    float vertices[] = { // position (vec2), color (vec3)
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom left
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top
    };

    std::uint32_t vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::uint32_t vbo;
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 2));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    auto shaders = std::make_unique<opengl::shaders>();

    window->setBackground({ 0.1f, 0.1f, 0.1f });
    while (window->open()) {
        shaders->bind(true);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    return 0;
}