#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "fruit.hpp"

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


class World {
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

        World(sf::Vector2u dimensions, float size);
    
        sf::VertexArray get_vertices() const;
        sf::Vector2f grid_pos_coordinates(sf::Vector2u position) const;
        sf::Vector2f grid_pos_coordinates(sf::Vector2u position, World::SquareLocation location_in_square ) const;
        void move_entity(sf::Vector2u& entity, Direction direction) const;
        float get_square_size() const;
        sf::Vector2u get_dimensions() const;
        void create_fruit();
        std::vector<Fruit> get_fruit_list() const;
        void destroy_fruit_index(int index);
        void draw_fruit(sf::RenderWindow& window) const;
    private:
        const sf::Vector2u _dimensions;
        const float _size;
        sf::Texture _fruitTexture;
        sf::VertexArray _gridVertices;
        std::vector<Fruit> _fruitList;
        std::vector<std::vector<sf::Vector2f>> _gridPositionsMatrix;
};
