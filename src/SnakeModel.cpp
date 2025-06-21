#include "SnakeModel.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include "utility.hpp"

SnakeModel::SnakeModel() :
    _player(_textureHandler.get_texture("eyes.png")),
    _gridVertices(
        sf::PrimitiveType::Triangles,
        GRID_DIMENSIONS.x * GRID_DIMENSIONS.y * 6)
{
    int square_counter = 0;

    for (int row = 0; row < GRID_DIMENSIONS.y; row++)
    {
        std::vector<sf::Vector2f> columnValues;
        auto row_fl = static_cast<float>(row);
        for (int column = 0; column < GRID_DIMENSIONS.x; column++)
        {
            sf::Color square_color;
            if ((column + row) % 2 == 0)
            {
                square_color.r = 163;
                square_color.g = 201;
                square_color.b = 173;
            }
            else
            {
                square_color.r = 122;
                square_color.g = 163;
                square_color.b = 133;
            }

            auto col_fl = static_cast<float>(column);
            sf::Vector2f top_left = {col_fl * GRID_SIZE, row_fl * GRID_SIZE};
            sf::Vector2f top_right{col_fl * GRID_SIZE + GRID_SIZE, row_fl * GRID_SIZE};
            sf::Vector2f bottom_left{col_fl * GRID_SIZE, row_fl * GRID_SIZE + GRID_SIZE};
            sf::Vector2f bottom_right{col_fl * GRID_SIZE + GRID_SIZE, row_fl * GRID_SIZE + GRID_SIZE};

            columnValues.push_back(top_left);

            _gridVertices[square_counter * 6].position = top_left;
            _gridVertices[square_counter * 6].color = square_color;
            _gridVertices[square_counter * 6 + 1].position = top_right;
            _gridVertices[square_counter * 6 + 1].color = square_color;
            _gridVertices[square_counter * 6 + 2].position = bottom_right;
            _gridVertices[square_counter * 6 + 2].color = square_color;

            _gridVertices[square_counter * 6 + 3].position = top_left;
            _gridVertices[square_counter * 6 + 3].color = square_color;
            _gridVertices[square_counter * 6 + 4].position = bottom_right;
            _gridVertices[square_counter * 6 + 4].color = square_color;
            _gridVertices[square_counter * 6 + 5].position = bottom_left;
            _gridVertices[square_counter * 6 + 5].color = square_color;

            square_counter++;
        }
    }
}

void SnakeModel::create_fruit() {
    sf::Vector2i position{rand() % GRID_DIMENSIONS.x, rand() % GRID_DIMENSIONS.y };

    while (!std::ranges::all_of(_fruitList, [position](const sf::Vector2i& fruit_pos) {
        return fruit_pos != position;
    })) {
        position = {rand() % GRID_DIMENSIONS.x, rand() % GRID_DIMENSIONS.y };
    }

    sf::Sprite sprite(*_textureHandler.get_texture("apple.png"));
    sprite.setPosition(grid_pos_coordinates(position));
    sf::Vector2f scale = {
        GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().x),
        GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().y)};
    sprite.scale(scale);
    _fruitSpriteList.push_back(sprite);
    _fruitList.push_back(position);
}

std::vector<sf::Vector2i> SnakeModel::get_fruit_list() const {
    return _fruitList;
}

void SnakeModel::destroy_fruit_index(int index) {
    _fruitList.erase(_fruitList.begin() + index);
    _fruitSpriteList.erase(_fruitSpriteList.begin() + index);
}

void SnakeModel::draw_fruit(sf::RenderWindow& window) const {
    for (const sf::Sprite& fruit : _fruitSpriteList) {
        window.draw(fruit);
    };
}

//Getter Methods
sf::VertexArray SnakeModel::get_vertices() const {return _gridVertices;}
Player* SnakeModel::get_player() {return &_player;}
