#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

enum Direction { UP, DOWN, LEFT, RIGHT };

sf::Vector2f direction_to_vector(Direction direction, float move_speed);

sf::VertexArray generate_grid(sf::Vector2u dimensions, float size);

class InputBuffer {
    public:
        InputBuffer(int buffer_size) : buffer_size(buffer_size) {}

        std::optional<Direction> get_next_direction();

        void add_move(Direction move);

        bool empty();

    private:
        int buffer_size;
        std::queue<Direction> move_queue;
};