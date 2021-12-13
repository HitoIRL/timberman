#include "tree.hpp"

#include "math.hpp"

core::tree::tree(const glm::vec2& position, const glm::vec2& size) : texture(std::make_unique<opengl::texture>("res/tree.png")) {
    this->position = { position.x - size.x / 2.0f, position.y };
    this->size = size;

    chunks.reserve(8);

    for (std::uint16_t i = 0; i < 8; i++)
        generateChunk();
}

void core::tree::render(const std::shared_ptr<opengl::renderer>& renderer) const {
    for (auto& chunk : chunks) {
        const auto y = position.y + chunk.yOffset;
        renderer->add({ position.x, y }, size, { 0, 0 }, { 320.0f, 256.0f }, texture); // log

        if (chunk.side != 2)
            renderer->add({ position.x + (chunk.side == 0 ? -size.x : size.x), y }, size, { chunk.side == 0 ? 2 : 3, 0 }, { 320.0f, 256.0f }, texture); // branch
    }
}

void core::tree::generateChunk() {
    float index = chunks.size();
    std::uint16_t side = 2;

    if (lastSide == 2)
        side = math::generateRandom(0, 1);

    chunk temp = { size.y * index, side };
    chunks.emplace_back(temp);

    lastSide = side;
}

bool core::tree::chop(std::uint16_t side) {
    const auto& first = chunks.begin();

    if (side == first->side)
        return false;

    chunks.erase(first);

    for (auto& chunk : chunks) {
        chunk.yOffset -= size.y;
    }

    generateChunk();
    return true;
}