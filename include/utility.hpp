#pragma once

#include <SFML/Graphics.hpp>

constexpr float GRID_SIZE = 800.0/15.0;

sf::Vector2f rotate_vector(sf::Vector2f initialVector, sf::Angle angleOfRotation);

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class SquareLocation {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    CENTER
};

Direction get_direction_to(sf::Vector2i initial_grid, sf::Vector2i final_grid);
Direction get_opposite(Direction direction);
sf::Angle direction_to_angle(Direction direction);
sf::Vector2f direction_to_vector(Direction direction, float magnitude);
sf::Vector2f grid_pos_coordinates(sf::Vector2i position);
sf::Vector2f grid_pos_coordinates(sf::Vector2i position, SquareLocation location_in_square);
sf::Vector2i move_position(sf::Vector2i initialpos, Direction direction);