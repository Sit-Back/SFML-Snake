#include <queue>
#include <cmath>
#include <iostream>
#include "player.hpp"
#include "grid.hpp"
#include "utility.hpp"

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

sf::Vector2f Player::get_head_center() {
    sf::Vector2f headCenter;
    headCenter.x = get_position().x + _headRadius;
    headCenter.y = get_position().y + _headRadius;

    return headCenter;
}

MovementDirection Player::get_move_direction() {
    return direction;
}

void Player::update_tail() {
    sf::Vector2f currentPos = get_head_center();
    std::array<sf::Vector2f, 2> points = calc_width_vertex(currentPos, direction_to_radian(direction), _bodyWidth/2-2);
    _stripPositions.push_front(sf::Vertex({points[0], PLAYER_COLOR}));
    _stripPositions.push_front(sf::Vertex({points[1], PLAYER_COLOR}));

    _tailStrip.clear();
    for (int i = 0; i < _stripPositions.size(); i++) {
        _tailStrip.append(_stripPositions[i]);
    }
}

std::array<sf::Vector2f, 2> Player::calc_width_vertex(sf::Vector2f position, float radiansDirection, float width) {
    //Get a direction vector of the angle and stretch to the length of width
    sf::Vector2f initialVector;
    initialVector.x = width*cos(radiansDirection);
    initialVector.y = width*sin(radiansDirection);

    //Rotate the initial vector to both sides
    sf::Vector2f rotation1 = rotate_vector(initialVector, M_PI_2);
    sf::Vector2f rotation2 = rotate_vector(initialVector, -M_PI_2);
    
    //Apply transformation to the initial position supplied
    sf::Vector2f pos1{position.x + rotation1.x, position.y + rotation1.y};
    sf::Vector2f pos2{position.x + rotation2.x, position.y + rotation2.y};

    return std::array<sf::Vector2f, 2>{pos1, pos2};
}

void Player::update() {
    sf::Vector2f position = get_position();
        if (std::fmod(position.x, GRID_SIZE) < 0.01f && std::fmod(position.y, GRID_SIZE) < 0.01f) {
            if (!_inputBuffer.empty()) {
                direction = *get_next_direction();
            } else {
                update_tail();
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

float direction_to_radian(MovementDirection direction) {
    switch (direction) {
        case MovementDirection::UP:
            return -M_PI_2;
            break;
        case MovementDirection::DOWN:
            return M_PI_2;
            break;
        case MovementDirection::LEFT:
            return M_PI;
            break;
        case MovementDirection::RIGHT:
            return 0.f;
            break;
    }

    return 0;
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