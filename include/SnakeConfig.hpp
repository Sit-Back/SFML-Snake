#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeConfig {
    constexpr float GRID_SIZE = 800.0/15.0;
    constexpr float UPDATE_RATE = 0.15;
    const std::string GAME_TITLE = "Snake Game";
    constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};
    static constexpr int MOVE_QUEUE_SIZE = 2;
    constexpr sf::Vector2i GRID_DIMENSIONS = {15, 15};
    constexpr int AVAILIABLE_SQUARES = GRID_DIMENSIONS.x * GRID_DIMENSIONS.y;

    const sf::Vector2f BUTTON_1_POS = {
        static_cast<float>(SnakeConfig::WINDOW_DIMENSIONS.x)/2, 
        2*static_cast<float>(SnakeConfig::WINDOW_DIMENSIONS.y)/3
    };

    const sf::Vector2f BUTTON_2_POS = {
        static_cast<float>(SnakeConfig::WINDOW_DIMENSIONS.x)/2, 
        2*static_cast<float>(SnakeConfig::WINDOW_DIMENSIONS.y)/3+50
    };
    const sf::Vector2f LOGO_POSITION{
        static_cast<float>(WINDOW_DIMENSIONS.x)/2,
        200
    };

    const sf::Vector2f SUBTEXT_POSITION{
        static_cast<float>(WINDOW_DIMENSIONS.x)/2,
        300
    };
}