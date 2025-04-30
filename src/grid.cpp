#include "grid.hpp"

sf::VertexArray generate_grid(sf::Vector2u dimensions, float size) {
    int grid_square_count = dimensions.x * dimensions.y;
    sf::VertexArray verticies(sf::PrimitiveType::Triangles, grid_square_count*6);
    int square_counter = 0;
    sf::Color square_color;

    for (int column = 0; column < dimensions.x; column++) {
       for (int row = 0; row < dimensions.y; row++) {
            if ((column+row)%2 == 0) {
                square_color.r = 163;
                square_color.g = 201;
                square_color.b = 173;
            } else {
                square_color.r = 122;
                square_color.g = 163;
                square_color.b = 133;
            }

            sf::Vector2f top_left = {column*size, row*size};
            sf::Vector2f top_right{column*size + size, row*size};
            sf::Vector2f bottom_left{column*size, row*size+size};
            sf::Vector2f bottom_right{column*size + size, row*size+size};

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
    }

    return verticies;
}