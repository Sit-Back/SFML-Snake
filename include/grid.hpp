#pragma once

#include <SFML/Graphics.hpp>

class Grid {
    public:
        const sf::Vector2u _dimensions;
        const float _size;

        Grid(sf::Vector2u dimensions, float size);
    
        sf::VertexArray get_verticies() const;
        sf::Vector2f grid_pos_coords(unsigned int row, unsigned int column) const;
    private:
        sf::VertexArray _gridVerticies;
        std::vector<std::vector<sf::Vector2f>> _gridPositionsMatrix;
};
