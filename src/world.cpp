#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include "utility.hpp"

Direction get_direction_to(sf::Vector2u initial_grid, sf::Vector2u final_grid) {
    const sf::Vector2i difference(static_cast<int>(final_grid.x) - initial_grid.x, static_cast<int>(final_grid.y) - initial_grid.y);

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

sf::Angle direction_to_angle(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return sf::radians(-M_PI_2);
        case Direction::DOWN:
            return sf::radians(M_PI_2);
        case Direction::LEFT:
            return sf::radians(M_PI);
        case Direction::RIGHT:
            return sf::radians(0.f);
    }

    return {};
}

World::World(sf::Vector2u dimensions, float size) : _dimensions(dimensions), _size(size), _gridVertices(sf::PrimitiveType::Triangles, _dimensions.x*_dimensions.y*6) {
    _fruitTexture = load_texture("apple.png");
    int square_counter = 0;

    for (int row = 0; row < _dimensions.y; row++) {
        std::vector<sf::Vector2f> columnValues;
        auto row_fl = static_cast<float>(row);
        for (int column = 0; column < _dimensions.x; column++) {
            sf::Color square_color;
            if ((column+row)%2 == 0) {
                square_color.r = 163;
                square_color.g = 201;
                square_color.b = 173;
            } else {
                square_color.r = 122;
                square_color.g = 163;
                square_color.b = 133;
            }

            auto col_fl = static_cast<float>(column);
            sf::Vector2f top_left = {col_fl*_size, row_fl*_size};
            sf::Vector2f top_right{col_fl*_size + _size, row_fl*_size};
            sf::Vector2f bottom_left{col_fl*_size, row_fl*_size+_size};
            sf::Vector2f bottom_right{col_fl*_size + _size, row_fl*_size+_size};

            columnValues.push_back(top_left);

            _gridVertices[square_counter*6].position = top_left;
            _gridVertices[square_counter*6].color = square_color;
            _gridVertices[square_counter*6+1].position = top_right;
            _gridVertices[square_counter*6+1].color = square_color;
            _gridVertices[square_counter*6+2].position = bottom_right;
            _gridVertices[square_counter*6+2].color = square_color;

            _gridVertices[square_counter*6+3].position = top_left;
            _gridVertices[square_counter*6+3].color = square_color;
            _gridVertices[square_counter*6+4].position = bottom_right;
            _gridVertices[square_counter*6+4].color = square_color;
            _gridVertices[square_counter*6+5].position = bottom_left;
            _gridVertices[square_counter*6+5].color = square_color;

            square_counter++;
       }

       _gridPositionsMatrix.push_back(columnValues);
    }
}

sf::VertexArray World::get_vertices() const {
    return _gridVertices;
}

sf::Vector2f World::grid_pos_coordinates(const sf::Vector2u position) const {
    return _gridPositionsMatrix.at(position.y).at(position.x);
}

sf::Vector2f World::grid_pos_coordinates(const sf::Vector2u position, const World::SquareLocation location_in_square ) const {
    sf::Vector2f coords = _gridPositionsMatrix.at(position.y).at(position.x);
    switch (location_in_square)
    {
    case World::SquareLocation::TOP_LEFT:
        return coords;
    case World::SquareLocation::TOP_RIGHT:
        coords.x += _size;
        return coords;
    case World::SquareLocation::BOTTOM_LEFT:
        coords.y += _size;
        return coords;
    case World::SquareLocation::BOTTOM_RIGHT:
        coords.x += _size;
        coords.y += _size;
        return coords;
    case World::SquareLocation::TOP:
        coords.x += _size/2;
        return coords;
    case World::SquareLocation::BOTTOM:
        coords.x += _size/2;
        coords.y += _size;
        return coords;
    case World::SquareLocation::LEFT:
        coords.y += _size/2;
        return coords;
    case World::SquareLocation::RIGHT:
        coords.x += _size;
        coords.y += _size/2;
        return coords;
    case World::SquareLocation::CENTER:
        coords.x += _size/2;
        coords.y += _size/2;
        return coords;
    }

    throw std::invalid_argument("Invalid location in square.");
}

void World::move_entity(sf::Vector2u& entity, Direction direction) const {
    switch (direction) {
        case (Direction::UP):
            if (entity.y > 0) {
                entity.y -= 1;
            }
            break;
        case (Direction::DOWN):
            if (entity.y < _dimensions.y-1) {
                entity.y += 1;
            }
            break;
        case (Direction::LEFT):
            if (entity.x > 0) {
                entity.x -= 1;
            }
            break;
        case (Direction::RIGHT):
            if (entity.x < _dimensions.x-1) {
                entity.x += 1;
            }
            break;
    }
}

float World::get_square_size() const {
    return _size;
}
sf::Vector2u World::get_dimensions() const {
    return _dimensions;
}

void World::create_fruit() {
    sf::Vector2u position{rand() % _dimensions.x, rand() % _dimensions.y };

    while (!std::ranges::all_of(_fruitList, [position](const Fruit& fruit) {
        return fruit.get_pos() != position;
    })) {
        position = {rand() % _dimensions.x, rand() % _dimensions.y };
    }

    _fruitList.emplace_back(this, position, _fruitTexture);
}

std::vector<Fruit> World::get_fruit_list() const {
    return _fruitList;
}

void World::destroy_fruit_index(int index) {
    _fruitList.erase(_fruitList.begin() + index);
}

void World::draw_fruit(sf::RenderWindow& window) const {
    for (const Fruit& fruit : _fruitList) {
        window.draw(fruit.get_sprite());
    };
}