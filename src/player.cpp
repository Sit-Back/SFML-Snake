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
        sf::Vector2u prevHeadPos = _headPos;
        _gameGrid.move_entity(_headPos, _direction);
        _head.setPosition(_gameGrid.grid_pos_coords(_headPos));
        update_tail();
        _turnPosList.push_front(prevHeadPos);
    } else {
        _gameGrid.move_entity(_headPos, _direction);
        _head.setPosition(_gameGrid.grid_pos_coords(_headPos));
        update_tail();
    }
} 

void Player::update_tail() {
    sf::Vector2u currentSearchPos = _headPos;
    _tailStrip.clear();
    add_verticies(calc_width_vertex(_gameGrid.grid_pos_coords(_headPos), direction_to_radian(_direction), _bodyWidth/2-1));

    int corner_index = 0;
    while (corner_index < _turnPosList.size()) {
        
        //std::cout << _turnPosList[corner_index].x << " " << _turnPosList[corner_index].y << '\n';
        corner_index++;
    }
    //std::cout << "--------------\n";

}

void Player::add_verticies(std::vector<sf::Vector2f> points) {
    for (int i = 0; i < points.size(); i++) {
        _tailStrip.append(sf::Vertex({points[i], PLAYER_COLOR}));
    }
}

//Support Functions
Grid::SquareLocation Player::get_square_location_for_search_dir(Direction search_dir) {
    switch (search_dir)
    {
    case Direction::LEFT:
        return Grid::SquareLocation::RIGHT;
        break;
    case Direction::RIGHT:
        return Grid::SquareLocation::LEFT;
        break;
    case Direction::UP:
        return Grid::SquareLocation::BOTTOM;
        break;
    case Direction::DOWN:
        return Grid::SquareLocation::TOP;
        break;
    }

    throw std::invalid_argument("Invalid Direction");
}

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

std::vector<sf::Vector2f> Player::calc_width_vertex(sf::Vector2f position, float radiansDirection, float width) {
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

    return std::vector<sf::Vector2f>{pos1, pos2};
}

void Player::add_move_to_buffer(const Direction move) {
    if (_inputBuffer.size() < MOVE_QUEUE_SIZE) {
        if (_inputBuffer.empty()) {
            if (_direction != move && _direction != get_opposite(move)) {
                _inputBuffer.push(move);
            }
        } else if (_inputBuffer.back() != move && _inputBuffer.back() != get_opposite(move)) {
            _inputBuffer.push(move);
        }
    }
}