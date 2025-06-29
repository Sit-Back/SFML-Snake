#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeConfig {
    constexpr float GRID_SIZE = 800.0/15.0;
    constexpr float UPDATE_RATE = 0.15;
    const std::string GAME_TITLE = "Snake Game";
    constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};
    static constexpr int MOVE_QUEUE_SIZE = 2;
    constexpr sf::Vector2i GRID_DIMENSIONS = {15, 15};
}