#include "core/game.hpp"


int main() {
    auto game = std::make_unique<core::game>(glm::uvec2(1280, 720));

    while (game->open()) {
        game->render();
    }
}