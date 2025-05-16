#include "fruit.hpp"
#include "world.hpp"
#include <SFML/Graphics.hpp>


Fruit::Fruit(const World* gameGrid, sf::Vector2u gridPosition, const sf::Texture& texture) : _sprite(texture), _pos(gridPosition) {
    sf::Vector2f scale = {gameGrid->get_square_size()/static_cast<float>(texture.getSize().x),gameGrid->get_square_size()/static_cast<float>(texture.getSize().y)};
    _sprite.scale(scale);
    _sprite.setPosition(gameGrid->grid_pos_coordinates(gridPosition));
}

sf::Sprite Fruit::get_sprite() const {
    return _sprite;
}

sf::Vector2u Fruit::get_pos() const {
    return _pos;
}