#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct GLFWwindow;

namespace opengl {
    class window {
    public:
        window(std::string_view title, const glm::uvec2& size);
        ~window();

        bool open() const;

        void setBackground(const glm::vec3& color) const;
    private:
        GLFWwindow* _window;
    };
}
