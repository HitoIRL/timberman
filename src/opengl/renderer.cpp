#include "renderer.hpp"

#include <glad/glad.h>

opengl::renderer::renderer(const glm::mat4& projection, std::uint32_t maxSprites) : maxVertices(maxSprites * 4), maxIndices(maxSprites * 6), vertices(std::make_unique<vertex[]>(maxVertices)), vertexCount(0), _shaders(std::make_unique<shaders>()), textureSlot(0), _font(std::make_unique<font>()) {
    // vao
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vbo
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * static_cast<std::uint32_t>(sizeof(vertex)), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, textureCoord)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, textureIndex)));

    // ebo
    std::unique_ptr<std::uint32_t[]> indices(new std::uint32_t[maxIndices]);
    std::uint32_t offset = 0;

    for (std::uint32_t i = 0; i < maxIndices; i += 6)
    {
        indices[i] = offset;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset;

        offset += 4;
    }

    glCreateBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * static_cast<std::uint32_t>(sizeof(std::uint32_t)), indices.get(), GL_STATIC_DRAW);

    // unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // textures
    int samplers[16];
    for (std::uint16_t i = 0; i < 16; i++)
        samplers[i] = i;

    // shaders
    _shaders->bind(true);
    _shaders->uniformMat4("projection", projection);
    _shaders->uniform1iv("samplers", samplers, sizeof(samplers));
    _shaders->bind(false);
}

opengl::renderer::~renderer() {
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void opengl::renderer::render() {
    if (vertexCount == 0)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<std::uint32_t>(sizeof(vertex)) * vertexCount, vertices.get());

    for (std::uint16_t i = 0; i < textureSlot; i++)
        textures[i]->bind(i);

    _shaders->bind(true);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<int>(vertexCount * 1.5), GL_UNSIGNED_INT, nullptr); // vertex count * 1.5 = index count

    // reset
    vertexCount = 0;
    textureSlot = 0;
}

void opengl::renderer::add(const glm::vec2& position, const glm::vec2& size, const glm::uvec2& offset, const glm::vec2& spriteSize, const std::shared_ptr<texture>& texture) {
    if (vertexCount >= maxVertices)
        render();

    // find texture index
    float textureIndex = 0.0f;

    for (std::uint16_t i = 0; i < textureSlot; i++)
    {
        if (texture == textures[i])
        {
            textureIndex = static_cast<float>(i);
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        if (textureSlot >= 16)
            render();

        textureIndex = static_cast<float>(textureSlot);
        textures[textureSlot] = texture;
        textureSlot++;
    }

    // render
    const glm::vec2 positions[] = {
            { position.x, position.y + size.y }, // left top
            { position.x, position.y }, // left bottom
            { position.x + size.x, position.y }, // right bottom
            { position.x + size.x, position.y + size.y } // right top
    };

    const auto textureSize = texture->getSize();
    const glm::vec2 coords[] = {
            { (offset.x * spriteSize.x) / textureSize.x, (offset.y * spriteSize.y) / textureSize.y },
            { (offset.x * spriteSize.x) / textureSize.x, ((offset.y + 1) * spriteSize.y) / textureSize.y },
            { ((offset.x + 1) * spriteSize.x) / textureSize.x, ((offset.y + 1) * spriteSize.y) / textureSize.y },
            { ((offset.x + 1) * spriteSize.x) / textureSize.x, (offset.y * spriteSize.y) / textureSize.y }
    };

    for (std::uint16_t i = 0; i < 4; i++) {
        vertices[vertexCount] = {
                positions[i],
                coords[i],
                textureIndex
        };

        vertexCount++;
    }
}

void opengl::renderer::add(const glm::vec2& position, std::string_view text, bool centered) {
    auto offset = static_cast<std::uint32_t>(position.x);

    for (const auto character : text)
    {
        const auto& current = _font->getCharacter(character);

        if (current.texture) {
            const glm::vec2 pos = {
                    static_cast<float>(offset + current.bearing.x) - (centered ? _font->getTextSize(text).x / 2.0f : 0),
                    position.y - static_cast<float>(current.texture->getSize().y - current.bearing.y)
            };

            add(pos, current.texture->getSize(), { 0, 0 }, current.texture->getSize(), current.texture);
        }

        offset += current.advance;
    }
}
