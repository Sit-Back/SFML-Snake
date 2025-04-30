#pragma once

#include <queue>
#include <SFML/Graphics.hpp>

const int MOVE_QUEUE_SIZE = 2;

enum Direction { UP, DOWN, LEFT, RIGHT };

sf::Vector2f direction_to_vector(Direction direction, float move_speed);

std::optional<Direction> get_next_direction(std::queue<Direction>& move_queue);

void add_move( std::queue<Direction>& move_queue, const Direction move);