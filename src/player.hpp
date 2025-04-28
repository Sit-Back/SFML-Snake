#pragma once

#include <SFML/Graphics.hpp>
#include <utility.hpp>

class Player {
    public: 
        Player(float move_speed) : sprite(5.f), move_speed(move_speed) {
            set_move_direction(RIGHT);
        }

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();

        Direction get_move_direction();

        void set_move_direction(Direction new_direction);

        void update();
    private:
        sf::CircleShape sprite;
        Direction direction;
        float move_speed;
        
};