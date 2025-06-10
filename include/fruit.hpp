#pragma once 
#include <SFML/Graphics.hpp>

class SnakeModel;

class Fruit {
public:
    Fruit(const SnakeModel* gameGrid, sf::Vector2u gridPosition, const sf::Texture& texture);
    sf::Sprite get_sprite() const;
    sf::Vector2u get_pos() const;
        
private:
    sf::Sprite _sprite;
    sf::Vector2u _pos;
};