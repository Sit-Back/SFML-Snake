#include "SnakeModel.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "utility.hpp"


SnakeModel::SnakeModel(AssetHandler* texture_handler) :
    m_textureHandler(*texture_handler),
    m_player(m_textureHandler.getTexture("eyes.png")),
    m_gridVertices(
        sf::PrimitiveType::Triangles,
        GRID_DIMENSIONS.x * GRID_DIMENSIONS.y * 6)
{
    generateGridVertices();
}

void SnakeModel::generateGridVertices()
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

            m_gridVertices[square_counter * 6].position = top_left;
            m_gridVertices[square_counter * 6].color = square_color;
            m_gridVertices[square_counter * 6 + 1].position = top_right;
            m_gridVertices[square_counter * 6 + 1].color = square_color;
            m_gridVertices[square_counter * 6 + 2].position = bottom_right;
            m_gridVertices[square_counter * 6 + 2].color = square_color;

            m_gridVertices[square_counter * 6 + 3].position = top_left;
            m_gridVertices[square_counter * 6 + 3].color = square_color;
            m_gridVertices[square_counter * 6 + 4].position = bottom_right;
            m_gridVertices[square_counter * 6 + 4].color = square_color;
            m_gridVertices[square_counter * 6 + 5].position = bottom_left;
            m_gridVertices[square_counter * 6 + 5].color = square_color;

            square_counter++;
        }
    }
}

////Fruit Methods
//
void SnakeModel::createFruit() {
    sf::Vector2i position{rand() % GRID_DIMENSIONS.x, rand() % GRID_DIMENSIONS.y };

    auto bodypositions = m_player.getBodyPositions();
    while (
        std::ranges::any_of(
            m_fruitList,
            [position](const sf::Vector2i& fruit_pos)
            {return fruit_pos == position;}
        )
        ||  std::any_of(
            bodypositions.begin(),
            bodypositions.end(),
            [position](BodyPos segment)
            {return segment.position == position;}
        )
    )
    {
        position = {rand() % GRID_DIMENSIONS.x, rand() % GRID_DIMENSIONS.y };
    }

    sf::Sprite sprite(*m_textureHandler.getTexture("apple.png"));
    sprite.setPosition(gridCoordinates(position));
    sf::Vector2f scale = {
        GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().x),
        GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().y)};
    sprite.scale(scale);
    m_fruitSpriteList.push_back(sprite);
    m_fruitList.push_back(position);
}

void SnakeModel::destroyFruitIndex(int index) {
    m_fruitList.erase(m_fruitList.begin() + index);
    m_fruitSpriteList.erase(m_fruitSpriteList.begin() + index);
}

void SnakeModel::drawFruit(sf::RenderWindow& window) const {
    for (const sf::Sprite& fruit : m_fruitSpriteList) {
        window.draw(fruit);
    };
}

////Getter Methods
//
sf::VertexArray SnakeModel::getVertices() const {return m_gridVertices;}
Player* SnakeModel::getPlayer() {return &m_player;}
std::vector<sf::Vector2i> SnakeModel::getFruitList() const {return m_fruitList;}
