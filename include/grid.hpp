#pragma once

#include <SFML/Graphics.hpp>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction get_direction_to(sf::Vector2u initial_grid, sf::Vector2u final_grid);
Direction get_opposite(Direction direction);
sf::Angle direction_to_angle(Direction direction);
sf::Vector2f direction_to_vector(Direction direction, float magnitude);


class Grid {
    public:
        enum class SquareLocation {
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT,
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            CENTER
        };

        const sf::Vector2u _dimensions;
        const float _size;

        Grid(sf::Vector2u dimensions, float size);
    
        sf::VertexArray get_verticies() const;
        sf::Vector2f grid_pos_coords(sf::Vector2u position) const;
        sf::Vector2f grid_pos_coords(sf::Vector2u position, Grid::SquareLocation location_in_square ) const;
        void move_entity(sf::Vector2u& entity, Direction direction) const;
    private:
        sf::VertexArray _gridVerticies;
        std::vector<std::vector<sf::Vector2f>> _gridPositionsMatrix;
};
