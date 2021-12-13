#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x2.hpp>

struct GLFWwindow;

namespace opengl {
    class window {
    public:
        window(std::string_view title, const glm::uvec2& size);
        ~window();

        bool open() const;

        void setBackground(const glm::vec3& color) const;
        void setKeyCallback(void (* callback)(GLFWwindow* window, int key, int scanCode, int action, int mods)) const;
        void setUserPointer(void* pointer) const;
        const glm::uvec2& getSize() const;
    private:
        GLFWwindow* _window;
        const glm::uvec2 size;
    };
}
