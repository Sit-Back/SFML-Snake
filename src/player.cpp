#include <queue>
#include <cmath>
#include "player.hpp"
#include "grid.hpp"

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::get_position() {
    return sprite.getPosition();
}

Player::MovementDirection Player::get_move_direction() {
    return direction;
}

void Player::set_move_direction(Player::MovementDirection new_direction) {
    direction = new_direction;
}

void Player::update() {
    if (!input_buffer.empty()) {
        sf::Vector2f position = get_position();
        if (std::fmod(position.x, GRID_SIZE) < 0.01f && std::fmod(position.y, GRID_SIZE) < 0.01f) {
            set_move_direction(*get_next_direction());
        }
    }

    sf::Vector2f movement_vector = direction_to_vector(direction, MOVEMENT_SPEED);
    sprite.move(sf::Vector2f{(float)movement_vector.x, (float)movement_vector.y});
}

void Player::add_move_to_buffer(const Player::MovementDirection move) {
    if ((input_buffer.empty() || input_buffer.back() != move) 
        && input_buffer.size() < MOVE_QUEUE_SIZE) 
    {input_buffer.push(move);}
}

sf::Vector2f direction_to_vector(Player::MovementDirection direction, float magnitude) {
    switch (direction) {
        case (Player::MovementDirection::UP):
            return sf::Vector2f{0, -magnitude};
        case (Player::MovementDirection::DOWN):
            return sf::Vector2f{0, magnitude};
        case (Player::MovementDirection::LEFT):
            return sf::Vector2f{-magnitude, 0};
        case (Player::MovementDirection::RIGHT):
            return sf::Vector2f{magnitude, 0};
    }

    throw std::invalid_argument("Invalid direction supplied");
}

std::optional<Player::MovementDirection> Player::get_next_direction() {
    if (input_buffer.size() > 0) {
        Player::MovementDirection direction = input_buffer.front();
        input_buffer.pop();
        
        return direction;
    }

    return std::nullopt;
}