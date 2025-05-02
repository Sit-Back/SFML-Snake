#include "grid.hpp"

Grid::Grid(sf::Vector2u dimensions, float size) {
    _size = size;
    sf::VertexArray verticies(sf::PrimitiveType::Triangles, dimensions.x * dimensions.y*6);
    int square_counter = 0;
    sf::Color square_color;

    for (int row = 0; row < dimensions.y; row++) {
        std::vector<sf::Vector2f> columnValues;
        for (int column = 0; column < dimensions.x; column++) {
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

            verticies[square_counter*6].position = top_left;
            verticies[square_counter*6].color = square_color;
            verticies[square_counter*6+1].position = top_right;
            verticies[square_counter*6+1].color = square_color;
            verticies[square_counter*6+2].position = bottom_right;
            verticies[square_counter*6+2].color = square_color;

            verticies[square_counter*6+3].position = top_left;
            verticies[square_counter*6+3].color = square_color;
            verticies[square_counter*6+4].position = bottom_right;
            verticies[square_counter*6+4].color = square_color;
            verticies[square_counter*6+5].position = bottom_left;
            verticies[square_counter*6+5].color = square_color;

            square_counter++;
       }

       _gridPositionsMatrix.push_back(columnValues);
    }

    _gridVerticies = verticies;
}

sf::VertexArray Grid::get_verticies() {
    return _gridVerticies;
}

sf::Vector2f Grid::grid_pos_coords(unsigned int row, unsigned int column) {
    return _gridPositionsMatrix.at(row).at(column);
}