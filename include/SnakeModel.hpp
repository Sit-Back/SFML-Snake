#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Player.hpp"
#include "AssetHandler.hpp"

class SnakeModel
{
    public:
        //Generators
        SnakeModel(AssetHandler* textureHandler);

        //Fruit Methods
        void createFruit(sf::Vector2i position);
        void destroyFruitIndex(int index);
        

        //Getter Methods
        sf::VertexArray getVertices() const;
        Player* getPlayer();
        std::vector<sf::Vector2i> getFruitList() const;
        int getScore() const;

    private:
        //Member Variables
        Player m_player;
        std::vector<sf::Vector2i> m_fruitList;        
};
