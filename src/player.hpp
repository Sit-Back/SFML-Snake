#pragma once

#include <SFML/Graphics.hpp>

const float MOVEMENT_SPEED = 1.f;
const int MOVE_QUEUE_SIZE = 2;

class Player {
    public: 
        enum class MovementDirection {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Player() : sprite(5.f) {
            set_move_direction(Player::MovementDirection::RIGHT);
        }

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();

        Player::MovementDirection get_move_direction();

        void set_move_direction(Player::MovementDirection new_direction);

        void update();

        void add_move_to_buffer(const Player::MovementDirection move);
    private:
        sf::CircleShape sprite;
        Player::MovementDirection direction;
        std::queue<Player::MovementDirection> input_buffer;

        std::optional<Player::MovementDirection> get_next_direction();
};

sf::Vector2f direction_to_vector(Player::MovementDirection direction);