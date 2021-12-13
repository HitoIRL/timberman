#pragma once

#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "texture.hpp"

namespace opengl {
    struct character
    {
        std::shared_ptr<texture> texture;
        glm::ivec2 bearing;
        std::uint32_t advance;
        std::uint32_t width;
    };

    class font {
    public:
        font();

        const character& getCharacter(std::uint8_t ch) const;
        glm::uvec2 getTextSize(std::string_view text) const;
    private:
        void addCharacter(std::uint8_t ch);

        FT_Library ft;
        FT_Face face;

        std::unordered_map<std::uint8_t, character> characters;
    };
}