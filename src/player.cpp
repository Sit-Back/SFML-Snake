#include <queue>
#include <cmath>
#include <iostream>
#include "player.hpp"
#include "grid.hpp"

std::optional<MovementDirection> Player::get_next_direction() {
    if (_inputBuffer.size() > 0) {
        MovementDirection direction = _inputBuffer.front();
        _inputBuffer.pop();
        
        return direction;
    }

    return std::nullopt;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(_head);
    window.draw(_tailStrip);
}

sf::Vector2f Player::get_position() {
    return _head.getPosition();
}

MovementDirection Player::get_move_direction() {
    return direction;
}

void Player::update_tail() {
    
    sf::Vector2f currentPos = _head.getPosition();
    _stripPositions.push_front(sf::Vertex({currentPos, PLAYER_COLOR}));
    _stripPositions.push_front(sf::Vertex({calc_width_vertex(currentPos, direction, _bodyWidth), PLAYER_COLOR}));

    _tailStrip.clear();
    for (int i = 0; i < _stripPositions.size(); i++) {
        _tailStrip.append(_stripPositions[i]);
    }
}

sf::Vector2f Player::calc_width_vertex(sf::Vector2f position, MovementDirection movement_direction, float width) {
    if (movement_direction == MovementDirection::LEFT || movement_direction == MovementDirection::RIGHT) {
        position.y += width;
    } else {
        position.x += width;
    }

    return position;
}

void Player::update() {
    sf::Vector2f position = get_position();
        if (std::fmod(position.x, GRID_SIZE) < 0.01f && std::fmod(position.y, GRID_SIZE) < 0.01f) {
            update_tail();
            if (!_inputBuffer.empty()) {
                direction = *get_next_direction();
            }
        }
    

    sf::Vector2f movement_vector = direction_to_vector(direction, MOVEMENT_SPEED);
    _head.move(movement_vector);
} 

void Player::add_move_to_buffer(const MovementDirection move) {
    if ((_inputBuffer.empty() || _inputBuffer.back() != move) 
        && _inputBuffer.size() < MOVE_QUEUE_SIZE) 
    {_inputBuffer.push(move);}
}

sf::Vector2f direction_to_vector(MovementDirection direction, float magnitude) {
    switch (direction) {
        case (MovementDirection::UP):
            return sf::Vector2f{0, -magnitude};
        case (MovementDirection::DOWN):
            return sf::Vector2f{0, magnitude};
        case (MovementDirection::LEFT):
            return sf::Vector2f{-magnitude, 0};
        case (MovementDirection::RIGHT):
            return sf::Vector2f{magnitude, 0};
    }

    throw std::invalid_argument("Invalid direction supplied");
}