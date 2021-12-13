#include "font.hpp"

#include <vector>

#include <freetype/ftglyph.h>
#include <freetype/ftstroke.h>

opengl::font::font() {
    FT_Init_FreeType(&ft);
    FT_New_Face(ft, "res/upheaval.ttf", 0, &face); // todo: path argument
    FT_Set_Pixel_Sizes(face, 0, 48);

    for (std::uint8_t i = 0; i < 128; i++)
        addCharacter(i);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void opengl::font::addCharacter(std::uint8_t ch) {
    FT_Load_Char(face, ch, FT_LOAD_RENDER);

    characters[ch] = {
            ch == ' ' ? nullptr : std::make_shared<texture>(glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), face->glyph->bitmap.buffer),
            { face->glyph->bitmap_left, face->glyph->bitmap_top },
            static_cast<std::uint32_t>(face->glyph->advance.x >> 6),
            static_cast<std::uint32_t>(face->glyph->metrics.width >> 6)
    };
}

const opengl::character& opengl::font::getCharacter(std::uint8_t ch) const {
    return characters.at(ch);
}

glm::uvec2 opengl::font::getTextSize(std::string_view text) const {
    glm::uvec2 temp(0.0f);

    for (const auto c : text)
    {
        const auto& current = getCharacter(c);

        temp.x += current.advance;
        temp.y = current.bearing.y;
    }

    const auto& last = characters.at(text.back());
    temp.x -= last.advance - last.width;

    return temp;
}
