#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeConfig {
    constexpr float GRID_SIZE = 800.0/15.0;
    constexpr float UPDATE_RATE = 0.15;
    const std::string GAME_TITLE = "Snake Game";
    constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};
}