#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
#include "AssetHandler.hpp"

constexpr sf::Vector2i GRID_DIMENSIONS = {15, 15};

class SnakeModel
{
    public:
        //Generators
        SnakeModel(AssetHandler* texture_handler);

        //Fruit Methods
        void create_fruit();
        void destroy_fruit_index(int index);
        void draw_fruit(sf::RenderWindow& window) const;

        //Getter Methods
        sf::VertexArray get_vertices() const;
        Player* get_player();
        std::vector<sf::Vector2i> get_fruit_list() const;

    private:
        //Member Variables
        AssetHandler _textureHandler;
        Player _player;
        sf::VertexArray _gridVertices;
        std::vector<sf::Sprite> _fruitSpriteList{};
        std::vector<sf::Vector2i> _fruitList;


        //General Methods
        void generate_grid_vertices();
};
