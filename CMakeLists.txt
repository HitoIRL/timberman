cmake_minimum_required(VERSION 3.21)
project(timberman)

set(CMAKE_CXX_STANDARD 23)

add_executable(timberman src/main.cpp src/main.cpp src/opengl/window.cpp src/opengl/shaders.cpp src/opengl/renderer.cpp src/core/math.cpp src/core/tree.cpp src/core/player.cpp src/opengl/texture.cpp src/core/game.cpp src/opengl/font.cpp src/opengl/font.hpp)

target_precompile_headers(timberman PRIVATE <memory> <string>)

set(dep_dir ${CMAKE_SOURCE_DIR}/deps)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${dep_dir}/glfw)

add_compile_definitions(GLFW_INCLUDE_NONE)

# glad
add_subdirectory(${dep_dir}/glad)

# freetype
add_subdirectory(${dep_dir}/freetype)

# binding(?)
target_link_libraries(timberman glfw glad freetype)
target_include_directories(timberman PUBLIC ${dep_dir}/glm ${dep_dir}/stb/include)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})