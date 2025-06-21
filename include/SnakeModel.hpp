#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
#include "TextureHandler.hpp"
#include "utility.hpp"

constexpr sf::Vector2i GRID_DIMENSIONS = {15, 15};

class SnakeModel
{
    public:
        SnakeModel();
    
        sf::VertexArray get_vertices() const;
        Player get_player() const;
        void create_fruit();
        std::vector<sf::Vector2i> get_fruit_list() const;
        void destroy_fruit_index(int index);
        void draw_fruit(sf::RenderWindow& window) const;
    private:
        TextureHandler _textureHandler;
        Player _player;
        sf::VertexArray _gridVertices;
        std::vector<sf::Sprite> _fruitSpriteList{};
        std::vector<sf::Vector2i> _fruitList;
};
