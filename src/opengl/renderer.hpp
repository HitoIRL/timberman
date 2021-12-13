#pragma once

#include <array>

#include "texture.hpp"
#include "shaders.hpp"
#include "font.hpp"

namespace opengl {
    class renderer {
    public:
        renderer(const glm::mat4& projection, std::uint32_t maxSprites);
        ~renderer();

        void render();

        void add(const glm::vec2& position, const glm::vec2& size, const glm::uvec2& offset, const glm::vec2& spriteSize, const std::shared_ptr<texture>& texture);
        void add(const glm::vec2& position, std::string_view text, bool centered);
    private:
        struct vertex {
            glm::vec2 position;
            glm::vec2 textureCoord;
            float textureIndex;
        };

        const std::uint32_t maxVertices, maxIndices;
        std::uint32_t vao, vbo, ebo;

        std::unique_ptr<vertex[]> vertices;
        std::uint32_t vertexCount;

        std::unique_ptr<shaders> _shaders;

        std::array<std::shared_ptr<texture>, 16> textures;
        std::uint16_t textureSlot;

        std::unique_ptr<font> _font;
    };
}