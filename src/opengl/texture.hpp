#pragma once

#include <glm/vec2.hpp>

namespace opengl {
    class texture {
    public:
        texture(std::string_view path);
        texture(const glm::ivec2& size, const void* data);
        ~texture();

        void bind(std::uint16_t slot) const;

        const glm::ivec2& getSize() const;
    private:
        std::uint32_t id;
        glm::ivec2 size;
    };
}