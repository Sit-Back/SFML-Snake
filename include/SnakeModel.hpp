#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "AssetHandler.hpp"

class SnakeModel
{
    public:
        //Generators
        SnakeModel(AssetHandler* textureHandler);

        //Fruit Methods
        void createFruit();
        void destroyFruitIndex(int index);
        void drawFruit(sf::RenderWindow& window) const;

        //Getter Methods
        sf::VertexArray getVertices() const;
        Player* getPlayer();
        std::vector<sf::Vector2i> getFruitList() const;

    private:
        //Member Variables
        AssetHandler m_textureHandler;
        Player m_player;
        sf::VertexArray m_gridVertices;
        std::vector<sf::Sprite> m_fruitSpriteList{};
        std::vector<sf::Vector2i> m_fruitList;

        //General Methods
        void generateGridVertices();
};
