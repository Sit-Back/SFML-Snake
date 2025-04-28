#include "player.hpp"

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

void Player::update() {
    sf::Vector2f movement_vector = direction_to_vector(direction, move_speed);
    sprite.move(sf::Vector2f{(float)movement_vector.x, (float)movement_vector.y});
}