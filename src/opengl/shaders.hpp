#pragma once

namespace opengl {
    class shaders {
    public:
        shaders();
        ~shaders();

        void bind(bool state) const;
    private:
        std::uint32_t createShader(const char* source, std::uint32_t type) const;

        std::uint32_t program;
    };
}
