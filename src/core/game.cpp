#include "game.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

core::game::game(const glm::uvec2& windowSize) : projection(glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y))), center(static_cast<glm::vec2>(windowSize) / 2.0f), window(std::make_unique<opengl::window>("timberman", windowSize)), renderer(std::make_shared<opengl::renderer>(projection, 10000)), points(0) {
    tree = std::make_unique<core::tree>(glm::vec2(center.x, 0.0f), glm::vec2(128.0f, 90.0f));

    window->setBackground({ 0.52f, 0.8f, 0.92f });
    window->setUserPointer(this);
    window->setKeyCallback(_keyCallback);
}

void core::game::render() const {
    tree->render(renderer);
    renderer->add({ center.x, static_cast<float>(window->getSize().y - 150.0f) }, std::to_string(points), true);
    renderer->render();
}

bool core::game::open() const {
    return window->open();
}

void core::game::reset() {
    // todo: show lose scene
    points = 0;
}

void core::game::keyCallback(int key, int action) {
    if (action == GLFW_PRESS && (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)) {
        std::uint16_t side = key == GLFW_KEY_LEFT ? 0 : 1;

        if (tree->chop(side))
            points++;
        else
            reset();
    }
}

void core::game::_keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    auto _this = reinterpret_cast<game*>(glfwGetWindowUserPointer(window));
    _this->keyCallback(key, action);
}