#pragma once

#include <SFML/Graphics.hpp>
#include <utility.hpp>

const float MOVEMENT_SPEED = 1.f;

class Player {
    public: 
        Player() : sprite(5.f) {
            set_move_direction(RIGHT);
        }

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();

        Direction get_move_direction();

        void set_move_direction(Direction new_direction);

        void update(std::queue<Direction>& input_buffer);
    private:
        sf::CircleShape sprite;
        Direction direction;
};