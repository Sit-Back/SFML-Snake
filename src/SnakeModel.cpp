#include "SnakeModel.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.hpp"
#include "utility.hpp"
#include "SnakeConfig.hpp"


SnakeModel::SnakeModel(AssetHandler* texture_handler) : m_player()
{}

////Fruit Methods
//
void SnakeModel::createFruit() {
    sf::Vector2i position{rand() % SnakeConfig::GRID_DIMENSIONS.x, rand() % SnakeConfig::GRID_DIMENSIONS.y };

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
        position = {rand() % SnakeConfig::GRID_DIMENSIONS.x, rand() % SnakeConfig::GRID_DIMENSIONS.y };
    }

    sf::Sprite sprite(*m_textureHandler.getTexture("apple.png"));
    sprite.setPosition(gridCoordinates(position));
    sf::Vector2f scale = {
        SnakeConfig::GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().x),
        SnakeConfig::GRID_SIZE/static_cast<float>(sprite.getTexture().getSize().y)};
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
Player* SnakeModel::getPlayer() {return &m_player;}
std::vector<sf::Vector2i> SnakeModel::getFruitList() const {return m_fruitList;}
