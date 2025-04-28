#include "utility.hpp"

sf::Vector2f direction_to_vector(Direction direction, float move_speed) {
    switch (direction) {
        case (Direction::UP):
            return sf::Vector2f{0, -move_speed};
        case (Direction::DOWN):
            return sf::Vector2f{0, move_speed};
        case (Direction::LEFT):
            return sf::Vector2f{-move_speed, 0};
        case (Direction::RIGHT):
            return sf::Vector2f{move_speed, 0};
    }

    throw std::invalid_argument("Invalid direction supplied");
}

std::optional<Direction> InputBuffer::get_next_direction() {
    if (move_queue.size() > 0) {
        Direction direction = move_queue.front();
        move_queue.pop();

        return direction;
    }

    return std::nullopt;
}

void InputBuffer::add_move(Direction move) {
    if (move_queue.size() < buffer_size) {
        move_queue.push(move);
    } 
}

bool InputBuffer::empty() {
    return move_queue.empty();
}

sf::VertexArray generate_grid(sf::Vector2u dimensions, float size) {
    int grid_square_count = dimensions.x * dimensions.y;
    sf::VertexArray verticies(sf::PrimitiveType::Triangles, grid_square_count*6);
    int square_counter = 0;
    sf::Color square_color;

    for (int column = 0; column < dimensions.x; column++) {
       for (int row = 0; row < dimensions.y; row++) {
            if ((column+row)%2 == 0) {
                square_color.r = 163;
                square_color.g = 201;
                square_color.b = 173;
            } else {
                square_color.r = 122;
                square_color.g = 163;
                square_color.b = 133;
            }

            sf::Vector2f top_left = {column*size, row*size};
            sf::Vector2f top_right{column*size + size, row*size};
            sf::Vector2f bottom_left{column*size, row*size+size};
            sf::Vector2f bottom_right{column*size + size, row*size+size};

            verticies[square_counter*6].position = top_left;
            verticies[square_counter*6].color = square_color;
            verticies[square_counter*6+1].position = top_right;
            verticies[square_counter*6+1].color = square_color;
            verticies[square_counter*6+2].position = bottom_right;
            verticies[square_counter*6+2].color = square_color;

            verticies[square_counter*6+3].position = top_left;
            verticies[square_counter*6+3].color = square_color;
            verticies[square_counter*6+4].position = bottom_right;
            verticies[square_counter*6+4].color = square_color;
            verticies[square_counter*6+5].position = bottom_left;
            verticies[square_counter*6+5].color = square_color;

            square_counter++;
       }
    }

    return verticies;
};