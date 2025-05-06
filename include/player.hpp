#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "grid.hpp"

const int MOVE_QUEUE_SIZE = 2;
const sf::Color PLAYER_COLOR(245, 66, 129);
const int TURN_RESOLUTION = 10;
const int INITIAL_PLAYER_LENGTH = 4;
const float PLAYER_WIDTH = 40;

class Player {
    public: 
        //General Variables
        Direction _direction;
        int _length;

        //Constructors
        Player(const Grid& gameGrid) : _gameGrid(gameGrid) {
            _headPos = {11, 5};
            _turnPosList.push_front(_headPos);
            _length = INITIAL_PLAYER_LENGTH;

            _head.setPosition(_gameGrid.grid_pos_coords(_headPos, Grid::SquareLocation::CENTER));
            _head.setRadius(PLAYER_WIDTH/2);
            _head.setFillColor(PLAYER_COLOR);
            _head.setOrigin({PLAYER_WIDTH/2, PLAYER_WIDTH/2});
            _end.setRadius(PLAYER_WIDTH/2);
            _end.setFillColor(PLAYER_COLOR);
            _end.setOrigin({PLAYER_WIDTH/2, PLAYER_WIDTH/2});

            _direction = Direction::RIGHT;

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
            update_tail();
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
        const Grid& _gameGrid;
        sf::CircleShape _head;
        sf::CircleShape _end;
        sf::Vector2u _headPos;
        std::queue<Direction> _inputBuffer;

        //Tail Variables
        std::deque<sf::Vector2u> _turnPosList;
        sf::VertexArray _tailStrip;
        
        //Methods
        std::optional<Direction> get_next_direction();
        std::vector<sf::Vector2f> calc_width_vertex(sf::Vector2f position, sf::Angle angle) const;
        Grid::SquareLocation travel_entry(const Direction search_dir) const;
        std::vector<sf::Vector2f> generate_circle_vertices(sf::Vector2u initialPos, Direction initialDirection, Direction finalPosition) const;
        void add_verticies(std::vector<sf::Vector2f> points);
        void update_tail();
};