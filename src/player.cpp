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
        _tailPosList.push_back(_headpos);
    } else {
        move_player(_direction);
        update_tail();
    }
    
    
} 

void Player::update_tail() {
    sf::Vector2f currentPos = get_head_center();
    std::array<sf::Vector2f, 2> points = calc_width_vertex(currentPos, direction_to_radian(_direction), _bodyWidth/2-1);
    _stripPositions.push_front(sf::Vertex({points[0], PLAYER_COLOR}));
    _stripPositions.push_front(sf::Vertex({points[1], PLAYER_COLOR}));

    _tailStrip.clear();
    for (int i = 0; i < _stripPositions.size(); i++) {
        _tailStrip.append(_stripPositions[i]);
    }
}


//Support Functions
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

sf::Vector2f Player::get_position() const {
    return _head.getPosition();
}

sf::Vector2u Player::get_position_grid() const {
    return _headpos;
}

sf::Vector2f Player::get_head_center() const {
    sf::Vector2f headCenter;
    headCenter.x = get_position().x + _bodyWidth/2;
    headCenter.y = get_position().y + _bodyWidth/2;

    return headCenter;
}

MovementDirection Player::get_move_direction() const {
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

void Player::add_move_to_buffer(const MovementDirection move) {
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

MovementDirection Player::get_opposite(MovementDirection direction) {
    switch (direction) {
        case (MovementDirection::UP):
            return MovementDirection::DOWN;
        case (MovementDirection::DOWN):
            return MovementDirection::UP;
        case (MovementDirection::LEFT):
            return MovementDirection::RIGHT;
        case (MovementDirection::RIGHT):
            return MovementDirection::LEFT;
    }

    throw std::invalid_argument("Invalid direction supplied");
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

void Player::move_player(MovementDirection direction) {
    switch (direction) {
        case (MovementDirection::UP):
            if (_headpos.y > 0) {
                _headpos.y -= 1;
            }
            break;
        case (MovementDirection::DOWN):
            if (_headpos.y < _gameGrid._dimensions.y-1) {
                _headpos.y += 1;
            }
            break;
        case (MovementDirection::LEFT):
            if (_headpos.x > 0) {
                _headpos.x -= 1;
            }
            break;
        case (MovementDirection::RIGHT):
            if (_headpos.x < _gameGrid._dimensions.x-1) {
                _headpos.x += 1;
            }
            break;
    }

    _head.setPosition(_gameGrid.grid_pos_coords(_headpos.y, _headpos.x));
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