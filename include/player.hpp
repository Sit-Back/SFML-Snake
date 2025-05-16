#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <queue>
#include "world.hpp"

const int MOVE_QUEUE_SIZE = 2;
const sf::Color PLAYER_COLOR(245, 66, 129);
const int TURN_RESOLUTION = 10;
const int INITIAL_PLAYER_LENGTH = 4;
const float PLAYER_WIDTH = 40;

std::vector<sf::Vector2f> calc_width_vertex(sf::Vector2f position, sf::Angle angle);
World::SquareLocation travel_entry(Direction search_dir);

class Player {
    public: 
        //General Variables
        Direction _direction;
        int _length;

        //Constructors
        Player(World& gameGrid, const sf::Texture& eyeTexture);

        //General Methods
        void draw(sf::RenderWindow& window) const;
        void update();
        void add_move_to_buffer(Direction move);

        //Getter Methods
        sf::Vector2f get_position() const;
        sf::Vector2u get_position_grid() const;
        sf::Vector2f get_head_center() const;
        Direction  get_move_direction() const;

    private:
        //General Variables
        World& _gameGrid;
        sf::CircleShape _head;
        sf::CircleShape _end;
        sf::Vector2u _headPos;
        std::queue<Direction> _inputBuffer;
        sf::Sprite _eyeSprite;

        //Tail Variables
        std::deque<sf::Vector2u> _turnPosList;
        sf::VertexArray _tailStrip;
        
        //Methods
        std::optional<Direction> get_next_direction();
        std::vector<sf::Vector2f> generate_circle_vertices(sf::Vector2u initialPos, Direction initialDirection, Direction finalPosition) const;
        void add_vertices(const std::vector<sf::Vector2f>& points);
        void update_tail();
};