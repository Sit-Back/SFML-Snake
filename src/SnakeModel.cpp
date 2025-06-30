#include "SnakeModel.hpp"
#include <SFML/Graphics.hpp>
#include "Player.hpp"



SnakeModel::SnakeModel(AssetHandler* texture_handler) : m_player()
{}

////Fruit Methods
//
void SnakeModel::createFruit(sf::Vector2i position) {
    m_fruitList.push_back(position);
}

void SnakeModel::destroyFruitIndex(int index) {
    m_fruitList.erase(m_fruitList.begin() + index);
}

////Getter Methods
//
Player* SnakeModel::getPlayer() {return &m_player;}
std::vector<sf::Vector2i> SnakeModel::getFruitList() const {return m_fruitList;}
