#include "fruit.hpp"
#include "world.hpp"
#include <SFML/Graphics.hpp>


Fruit::Fruit(const World* gameGrid, sf::Vector2u gridPosition, sf::Texture& texture) : _sprite(texture), _pos(gridPosition) {
    sf::Vector2f scale = {gameGrid->get_square_size()/texture.getSize().x,gameGrid->get_square_size()/texture.getSize().y};
    _sprite.scale(scale);
    _sprite.setPosition(gameGrid->grid_pos_coords(gridPosition));
}

sf::Sprite Fruit::get_sprite() const {
    return _sprite;
}

sf::Vector2u Fruit::get_pos() const {
    return _pos;
}