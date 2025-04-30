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

Direction Player::get_move_direction() {
    return direction;
}

void Player::set_move_direction(Direction new_direction) {
    direction = new_direction;
}

void Player::update(std::queue<Direction>& input_buffer) {
    if (!input_buffer.empty()) {
        sf::Vector2f position = get_position();
        if (std::fmod(position.x, GRID_SIZE) < 0.01f && std::fmod(position.y, GRID_SIZE) < 0.01f) {
            set_move_direction(*get_next_direction(input_buffer));
        }
    }

    sf::Vector2f movement_vector = direction_to_vector(direction, MOVEMENT_SPEED);
    sprite.move(sf::Vector2f{(float)movement_vector.x, (float)movement_vector.y});
}