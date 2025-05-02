#pragma once

#include <SFML/Graphics.hpp>

const float GRID_SIZE = 10.f;

class Grid {
    public:
        Grid(sf::Vector2u dimensions, float size);

        sf::VertexArray get_verticies();
        sf::Vector2f grid_pos_coords(unsigned int row, unsigned int column);
    private:
        sf::VertexArray _gridVerticies;
        std::vector<std::vector<sf::Vector2f>> _gridPositionsMatrix;
        float _size;
};
