#pragma once 
#include <SFML/Graphics.hpp>
#include "utility.hpp"
#include "grid.hpp"

class Fruit {
public:
    Fruit(Grid& gameGrid, sf::Vector2u gridPosition) : _sprite(_texture) {
        sf::Vector2f scale = {gameGrid.get_square_size()/_texture.getSize().x,gameGrid.get_square_size()/_texture.getSize().y};
        _sprite.scale(scale);
        _sprite.setPosition(gameGrid.grid_pos_coords(gridPosition));
    }

    sf::Sprite get_sprite() const;
        
private:
    sf::Texture _texture = load_texture("apple.png");
    sf::Sprite _sprite;
};