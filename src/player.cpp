#include <queue>
#include <cmath>
#include <iostream>
#include "player.hpp"
#include "grid.hpp"
#include "utility.hpp"

//Main Updates
void Player::update() {
    if (!_inputBuffer.empty()) {
        _direction = *get_next_direction();
        move_player(_direction);
        update_tail();
        _tailPosList.push_back(_headPos);
    } else {
        move_player(_direction);
        update_tail();
    }
} 

void Player::update_tail() {
    _tailStrip.clear();
    std::deque<sf::Vertex> stripPositions;
    std::array<sf::Vector2f, 2> points = calc_width_vertex(_gameGrid.grid_pos_coords(_headPos), direction_to_radian(_direction), _bodyWidth/2-1);
    _tailStrip.append(sf::Vertex({points[0], PLAYER_COLOR}));
    _tailStrip.append(sf::Vertex({points[1], PLAYER_COLOR}));
}

//Support Functions
std::optional<Direction> Player::get_next_direction() {
    if (_inputBuffer.size() > 0) {
        Direction direction = _inputBuffer.front();
        _inputBuffer.pop();
        
        return direction;
    }

    return std::nullopt;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(_head);
    window.draw(_tailStrip);
}

sf::Vector2f Player::get_position() const {
    return _head.getPosition();
}

sf::Vector2u Player::get_position_grid() const {
    return _headPos;
}

sf::Vector2f Player::get_head_center() const {
    sf::Vector2f headCenter;
    headCenter.x = get_position().x + _bodyWidth/2;
    headCenter.y = get_position().y + _bodyWidth/2;

    return headCenter;
}

Direction Player::get_move_direction() const {
    return _direction;
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

void Player::add_move_to_buffer(const Direction move) {
    if (
        (
            (_inputBuffer.empty() && _direction != move && _direction != get_opposite(move)) 
            || (_inputBuffer.back() != move && _inputBuffer.back() != get_opposite(move))
        ) 
        && _inputBuffer.size() < MOVE_QUEUE_SIZE
    ) 
    {
        _inputBuffer.push(move);
    }
}

void Player::move_player(Direction direction) {
    switch (direction) {
        case (Direction::UP):
            if (_headPos.y > 0) {
                _headPos.y -= 1;
            }
            break;
        case (Direction::DOWN):
            if (_headPos.y < _gameGrid._dimensions.y-1) {
                _headPos.y += 1;
            }
            break;
        case (Direction::LEFT):
            if (_headPos.x > 0) {
                _headPos.x -= 1;
            }
            break;
        case (Direction::RIGHT):
            if (_headPos.x < _gameGrid._dimensions.x-1) {
                _headPos.x += 1;
            }
            break;
    }

    _head.setPosition(_gameGrid.grid_pos_coords(_headPos));
}