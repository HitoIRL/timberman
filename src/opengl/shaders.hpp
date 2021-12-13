#pragma once

#include <unordered_map>

#include <glm/mat4x2.hpp>

namespace opengl {
    class shaders {
    public:
        shaders();
        ~shaders();

        void bind(bool state) const;

        void uniformMat4(std::string_view name, const glm::mat4& matrix);
        void uniform1iv(std::string_view name, int* arr, int size);
    private:
        std::uint32_t createShader(const char* source, std::uint32_t type) const;
        int getLocation(std::string_view name); // get uniform location

        std::uint32_t program;
        mutable bool binded;
        std::unordered_map<std::string_view, int> cache; // uniform location cache
    };
}
