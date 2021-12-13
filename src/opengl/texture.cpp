#include "texture.hpp"

#include <glm/vec2.hpp>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

opengl::texture::texture(std::string_view path) {
    int channels;

    if (const auto data = stbi_load(path.data(), &size.x, &size.y, &channels, 0))
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id, 1, GL_RGBA8, size.x, size.y);

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(id, 0, 0, 0, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
}

opengl::texture::texture(const glm::ivec2& size, const void* data) : size(size) {
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, GL_R8, size.x, size.y);

    constexpr int swizzle[] = { GL_RED, GL_RED, GL_RED, GL_RED };
    glTextureParameteriv(id, GL_TEXTURE_SWIZZLE_RGBA, swizzle);

    glTextureSubImage2D(id, 0, 0, 0, size.x, size.y, GL_RED, GL_UNSIGNED_BYTE, data);
}

opengl::texture::~texture() {
    glDeleteTextures(1, &id);
}

void opengl::texture::bind(std::uint16_t slot) const {
    glBindTextureUnit(slot, id);
}

const glm::ivec2& opengl::texture::getSize() const {
    return size;
}