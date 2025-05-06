#include <queue>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "grid.hpp"
#include "utility.hpp"

//Main Updates
void Player::update() {
    if (!_inputBuffer.empty()) {
        _direction = *get_next_direction();
        _turnPosList.push_front(_headPos);
    }

    _gameGrid.move_entity(_headPos, _direction);
    _head.setPosition(_gameGrid.grid_pos_coords(_headPos, Grid::SquareLocation::CENTER));
    update_tail();
} 

void Player::update_tail() {
    sf::Vector2u currentSearchPos = _headPos;
    Direction searchDirection = get_opposite(_direction);
    _tailStrip.clear();
    add_verticies(calc_width_vertex(get_head_center(), direction_to_angle(searchDirection)));

    int corner_index = 0;
    int traversed_squares = 0;
    while (traversed_squares < _length-1) {
        if (_turnPosList.size() > corner_index + 1 && currentSearchPos == _turnPosList[corner_index]) {
            Direction initialDirection = searchDirection;
            searchDirection = get_direction_to(currentSearchPos, _turnPosList[corner_index+1]);
            add_verticies(generate_circle_vertices(currentSearchPos, initialDirection, searchDirection));
            corner_index++;
        }

        _gameGrid.move_entity(currentSearchPos, searchDirection);
        sf::Vector2f vertexOrigin = _gameGrid.grid_pos_coords(currentSearchPos, travel_entry(searchDirection));
        add_verticies(calc_width_vertex(vertexOrigin, direction_to_angle(searchDirection)));
        traversed_squares++;
    }
    sf::Vector2f endPos = _gameGrid.grid_pos_coords(currentSearchPos, Grid::SquareLocation::CENTER);
    add_verticies(calc_width_vertex(endPos, direction_to_angle(searchDirection)));
    _end.setPosition(endPos);
}
 
//Support Functions
Grid::SquareLocation Player::travel_entry(const Direction search_dir) const {
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

void Player::add_verticies(std::vector<sf::Vector2f> points) {
    for (int i = 0; i < points.size(); i++) {
        _tailStrip.append(sf::Vertex({points[i], PLAYER_COLOR}));
    }
}

std::vector<sf::Vector2f> Player::generate_circle_vertices(sf::Vector2u initialPos, Direction initialDirection, Direction finalDirection) const {
    std::vector<sf::Vector2f> circleVertices;
    sf::Angle differenceAngle = direction_to_angle(finalDirection)-direction_to_angle(initialDirection);
    differenceAngle = differenceAngle.wrapSigned();

    
    Grid::SquareLocation potentialOrigin[2]; //First entry is for if the user turns left, second is for if they turn right.
    switch (initialDirection)
    {
        case Direction::RIGHT:
            potentialOrigin[0] = Grid::SquareLocation::TOP_LEFT;
            potentialOrigin[1] = Grid::SquareLocation::BOTTOM_LEFT;
            break;
        case Direction::LEFT:
            potentialOrigin[0] = Grid::SquareLocation::BOTTOM_RIGHT;
            potentialOrigin[1] = Grid::SquareLocation::TOP_RIGHT;
            break;
        case Direction::UP:
            potentialOrigin[0] = Grid::SquareLocation::BOTTOM_LEFT;
            potentialOrigin[1] = Grid::SquareLocation::BOTTOM_RIGHT;
            break;
        case Direction::DOWN:
            potentialOrigin[0] = Grid::SquareLocation::TOP_RIGHT;
            potentialOrigin[1] = Grid::SquareLocation::TOP_LEFT; 
            break;
        default:
            throw std::invalid_argument("Invalid direction.");
    }
    
    sf::Vector2f origin;
    sf::Angle initialAngle;
    if (differenceAngle.asRadians() < 0) {
        //Left/Counter-Clockwise

        initialAngle = direction_to_angle(initialDirection) + sf::radians(M_PI_2);
        origin = _gameGrid.grid_pos_coords(initialPos, potentialOrigin[0]);
    } else {
        //Right/Clockwise

        initialAngle = direction_to_angle(initialDirection) - sf::radians(M_PI_2);
        origin = _gameGrid.grid_pos_coords(initialPos, potentialOrigin[1]);
    }

    for (int i = 1; i < TURN_RESOLUTION + 1; i++) {
        sf::Angle currentAngle = initialAngle + i*(differenceAngle/(TURN_RESOLUTION+1));
        float rise = (_gameGrid.get_square_size()/2)*sin(currentAngle.asRadians());
        float run = (_gameGrid.get_square_size()/2)*cos(currentAngle.asRadians());

        sf::Vector2f pointPosition = {origin.x + run, origin.y + rise};
        double perpanGradient = -run/rise;
        sf::Angle angle = sf::radians(atan(perpanGradient));
        angle = initialDirection == Direction::LEFT || finalDirection == Direction::LEFT ? angle - sf::radians(M_PI) : angle;

        std::vector<sf::Vector2f> verticies = calc_width_vertex(pointPosition, angle);
        circleVertices.push_back(verticies[0]);
        circleVertices.push_back(verticies[1]);
      }

    return circleVertices;
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
    window.draw(_end);
    window.draw(_tailStrip);
}

sf::Vector2f Player::get_position() const {
    return _head.getPosition();
}

sf::Vector2u Player::get_position_grid() const {
    return _headPos;
}

sf::Vector2f Player::get_head_center() const {
    return _gameGrid.grid_pos_coords(_headPos, Grid::SquareLocation::CENTER);
}

Direction Player::get_move_direction() const {
    return _direction;
}

std::vector<sf::Vector2f> Player::calc_width_vertex(sf::Vector2f position, sf::Angle angle) const {
    //Get a direction vector of the angle and stretch to the length of width
    sf::Vector2f initialVector;
    initialVector.x = PLAYER_WIDTH/2*cos(angle.asRadians());
    initialVector.y = PLAYER_WIDTH/2*sin(angle.asRadians());

    //Rotate the initial vector to both sides
    sf::Vector2f rotation1 = rotate_vector(initialVector, sf::radians(M_PI_2));
    sf::Vector2f rotation2 = rotate_vector(initialVector, sf::radians(-M_PI_2));
    
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