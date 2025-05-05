#include "grid.hpp"
#include <cmath>

Direction get_direction_to(sf::Vector2u initial_grid, sf::Vector2u final_grid) {
    sf::Vector2u difference{final_grid.x - initial_grid.x, final_grid.y - initial_grid.y};

    if (difference.x > 0 && difference.y == 0) return Direction::RIGHT;
    else if (difference.x < 0 && difference.y == 0) return Direction::LEFT;
    else if (difference.y > 0 && difference.x == 0) return Direction::DOWN;
    else if (difference.y < 0 && difference.x == 0) return Direction::UP;
    else throw std::invalid_argument("No cardinal direction found. (diagonal or same point)");
}

Direction get_opposite(Direction direction) {
    switch (direction) {
        case (Direction::UP):
            return Direction::DOWN;
        case (Direction::DOWN):
            return Direction::UP;
        case (Direction::LEFT):
            return Direction::RIGHT;
        case (Direction::RIGHT):
            return Direction::LEFT;
    }

    throw std::invalid_argument("Invalid direction supplied");
}

sf::Vector2f direction_to_vector(Direction direction, float magnitude) {
    switch (direction) {
        case (Direction::UP):
            return sf::Vector2f{0, -magnitude};
        case (Direction::DOWN):
            return sf::Vector2f{0, magnitude};
        case (Direction::LEFT):
            return sf::Vector2f{-magnitude, 0};
        case (Direction::RIGHT):
            return sf::Vector2f{magnitude, 0};
    }

    throw std::invalid_argument("Invalid direction supplied");
}

float direction_to_radian(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return -M_PI_2;
            break;
        case Direction::DOWN:
            return M_PI_2;
            break;
        case Direction::LEFT:
            return M_PI;
            break;
        case Direction::RIGHT:
            return 0.f;
            break;
    }

    return 0;
}

Grid::Grid(sf::Vector2u dimensions, float size) : _size(size), _dimensions(dimensions), _gridVerticies(sf::PrimitiveType::Triangles, _dimensions.x*_dimensions.y*6) {
    int square_counter = 0;
    sf::Color square_color;

    for (int row = 0; row < _dimensions.y; row++) {
        std::vector<sf::Vector2f> columnValues;
        for (int column = 0; column < _dimensions.x; column++) {
            if ((column+row)%2 == 0) {
                square_color.r = 163;
                square_color.g = 201;
                square_color.b = 173;
            } else {
                square_color.r = 122;
                square_color.g = 163;
                square_color.b = 133;
            }

            sf::Vector2f top_left = {column*_size, row*_size};
            sf::Vector2f top_right{column*_size + _size, row*_size};
            sf::Vector2f bottom_left{column*_size, row*_size+_size};
            sf::Vector2f bottom_right{column*_size + _size, row*_size+_size};

            columnValues.push_back(top_left);

            _gridVerticies[square_counter*6].position = top_left;
            _gridVerticies[square_counter*6].color = square_color;
            _gridVerticies[square_counter*6+1].position = top_right;
            _gridVerticies[square_counter*6+1].color = square_color;
            _gridVerticies[square_counter*6+2].position = bottom_right;
            _gridVerticies[square_counter*6+2].color = square_color;

            _gridVerticies[square_counter*6+3].position = top_left;
            _gridVerticies[square_counter*6+3].color = square_color;
            _gridVerticies[square_counter*6+4].position = bottom_right;
            _gridVerticies[square_counter*6+4].color = square_color;
            _gridVerticies[square_counter*6+5].position = bottom_left;
            _gridVerticies[square_counter*6+5].color = square_color;

            square_counter++;
       }

       _gridPositionsMatrix.push_back(columnValues);
    }
}

sf::VertexArray Grid::get_verticies() const {
    return _gridVerticies;
}

sf::Vector2f Grid::grid_pos_coords(sf::Vector2u position) const {
    return _gridPositionsMatrix.at(position.y).at(position.x);
}

sf::Vector2f Grid::grid_pos_coords(sf::Vector2u position, Grid::SquareLocation location_in_square ) const {
    sf::Vector2f coords = _gridPositionsMatrix.at(position.y).at(position.x);
    switch (location_in_square)
    {
    case Grid::SquareLocation::TOP_LEFT:
        return coords;
        break;
    case Grid::SquareLocation::TOP_RIGHT:
        coords.x += _size;
        return coords;
        break;
    case Grid::SquareLocation::BOTTOM_LEFT:
        coords.y += _size;
        return coords;
        break;
    case Grid::SquareLocation::BOTTOM_RIGHT:
        coords.x += _size;
        coords.y += _size;
        return coords;
        break;
    case Grid::SquareLocation::TOP:
        coords.x += _size/2;
        return coords;
        break;
    case Grid::SquareLocation::BOTTOM:
        coords.x += _size/2;
        coords.y += _size;
        return coords;
        break;
    case Grid::SquareLocation::LEFT:
        coords.y += _size/2;
        return coords;
        break;
    case Grid::SquareLocation::RIGHT:
        coords.x += _size;
        coords.y += _size/2;
        return coords;
        break;
    }

    throw std::invalid_argument("Invalid location in square.");
}