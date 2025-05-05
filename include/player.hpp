#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "grid.hpp"

const float MOVEMENT_SPEED = 1.f;
const int MOVE_QUEUE_SIZE = 2;
const sf::Color PLAYER_COLOR(245, 66, 129);
const int TAIL_UPDATE_DELAY = 5;

class Player {
    public: 
        //General Variables
        Direction _direction;

        //Constructors
        Player(const Grid& gameGrid, float bodyWidth) : _bodyWidth(bodyWidth), _gameGrid(gameGrid){
            _headPos = {1, 1};

            _head.setPosition(_gameGrid.grid_pos_coords(_headPos));
            _head.setRadius(_bodyWidth/2);
            _head.setFillColor(PLAYER_COLOR);

            _direction = Direction::RIGHT;

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        }

        //General Methods
        void draw(sf::RenderWindow& window);
        void update();
        void add_move_to_buffer(const Direction move);

        //Getter Methods
        sf::Vector2f get_position() const;
        sf::Vector2u get_position_grid() const;
        sf::Vector2f get_head_center() const;
        Direction  get_move_direction() const;

    private:
        //General Variables
        const float _bodyWidth;
        const Grid& _gameGrid;
        sf::CircleShape _head;
        sf::Vector2u _headPos;
        std::queue<Direction> _inputBuffer;

        //Tail Variables
        std::deque<sf::Vector2u> _turnPosList;
        sf::VertexArray _tailStrip;
        
        //Methods
        std::optional<Direction> get_next_direction();
        std::vector<sf::Vector2f> calc_width_vertex(sf::Vector2f position, float radiansDirection, float width);
        Grid::SquareLocation get_square_location_for_search_dir(Direction search_dir);
        void add_verticies(std::vector<sf::Vector2f> points);
        void update_tail();
};