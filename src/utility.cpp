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

std::optional<Direction> get_next_direction(std::queue<Direction>& move_queue) {
    if (move_queue.size() > 0) {
        Direction direction = move_queue.front();
        move_queue.pop();
        
        return direction;
    }

    return std::nullopt;
}

void add_move( std::queue<Direction>& move_queue, const Direction move) {
    if ((move_queue.empty() || move_queue.back() != move) 
        && move_queue.size() < MOVE_QUEUE_SIZE) 
    {move_queue.push(move);}
}