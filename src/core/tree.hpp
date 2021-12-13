#pragma once

#include <glm/vec2.hpp>

#include "../opengl/renderer.hpp"

namespace core {
    class tree {
    public:
        tree(const glm::vec2& position, const glm::vec2& size);

        void render(const std::shared_ptr<opengl::renderer>& renderer) const;

        bool chop(std::uint16_t side);
    private:
        struct chunk {
            float yOffset;
            std::uint16_t side; // 0 = left, 1 = right, 2 = none
        };

        void generateChunk();

        glm::vec2 position, size;
        std::vector<chunk> chunks;
        std::uint16_t lastSide;
        std::shared_ptr<opengl::texture> texture;
    };
}