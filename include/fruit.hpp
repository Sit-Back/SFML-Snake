#pragma once 
#include <SFML/Graphics.hpp>

class World;

class Fruit {
public:
    Fruit(const World* gameGrid, sf::Vector2u gridPosition, const sf::Texture& texture);
    sf::Sprite get_sprite() const;
    sf::Vector2u get_pos() const;
        
private:
    sf::Sprite _sprite;
    sf::Vector2u _pos;
};