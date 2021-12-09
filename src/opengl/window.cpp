#include "window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

opengl::window::window(std::string_view title, const glm::uvec2 &size) {
    // glfw
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1); // vertical sync

    // glad
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    glViewport(0, 0, size.x, size.y);
}

opengl::window::~window() {
    glfwTerminate();
}

bool opengl::window::open() const {
    glfwSwapBuffers(_window);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, 1);

    return !glfwWindowShouldClose(_window);
}

void opengl::window::setBackground(const glm::vec3 &color) const {
    glClearColor(color.r, color.g, color.b, 1.0f);
}
