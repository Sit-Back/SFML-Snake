#pragma once

#include <SFML/Graphics.hpp>

constexpr float GRID_SIZE = 800.0/15.0;

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

Direction getDirectionTo(sf::Vector2i initialGrid, sf::Vector2i finalGrid);
Direction getOpposite(Direction direction);
sf::Angle directionToAngle(Direction direction);
sf::Vector2f directionToVector(Direction direction, float magnitude);
sf::Vector2f gridCoordinates(sf::Vector2i position);
sf::Vector2f gridCoordinates(sf::Vector2i position, SquareLocation locationInSquare);
void shiftPosition(sf::Vector2i& initialPosition, Direction direction);
sf::Vector2f rotateVector(sf::Vector2f initialVector, sf::Angle angleOfRotation);
bool pointInRect(sf::Vector2i point, sf::Vector2i pos1, sf::Vector2i pos2);