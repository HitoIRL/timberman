#pragma once

#include <glm/mat4x2.hpp>

#include "../opengl/window.hpp"
#include "../opengl/renderer.hpp"
#include "tree.hpp"

namespace core {
    class game {
    public:
        game(const glm::uvec2& windowSize);

        void render() const;

        bool open() const;
    private:
        void reset();
        void keyCallback(int key, int action);
        static void _keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

        const glm::mat4 projection;
        const glm::vec2 center;

        const std::unique_ptr<opengl::window> window;
        const std::shared_ptr<opengl::renderer> renderer;

        std::unique_ptr<core::tree> tree;

        std::uint32_t points;
    };
}