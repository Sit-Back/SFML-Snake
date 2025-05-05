#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "grid.hpp"

const float MOVEMENT_SPEED = 1.f;
const int MOVE_QUEUE_SIZE = 2;
const sf::Color PLAYER_COLOR(245, 66, 129);
const int TAIL_UPDATE_DELAY = 5;

enum class MovementDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

sf::Vector2f direction_to_vector(MovementDirection direction, float magnitude);
float direction_to_radian(MovementDirection direction);

class Player {
    public: 
        //General Variables
        MovementDirection _direction;

        //Constructors
        Player(const Grid& gameGrid, float bodyWidth) : _bodyWidth(bodyWidth), _gameGrid(gameGrid){
            _head.setRadius(_bodyWidth/2);
            _head.setFillColor(PLAYER_COLOR);

            _headpos = {0, 0};

            _direction = MovementDirection::RIGHT;

            std::array<sf::Vector2f,2> initialVerticies = calc_width_vertex(get_head_center(), direction_to_radian(_direction), _bodyWidth/2-1);

            _stripPositions.push_front(sf::Vertex({initialVerticies[0], PLAYER_COLOR}));
            _stripPositions.push_front(sf::Vertex({initialVerticies[1], PLAYER_COLOR}));

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        }

        //General Methods
        void draw(sf::RenderWindow& window);
        void update();
        void add_move_to_buffer(const MovementDirection move);
        void move_player(MovementDirection direction);

        //Getter Methods
        sf::Vector2f get_position() const;
        sf::Vector2u get_position_grid() const;
        sf::Vector2f get_head_center() const;
        MovementDirection  get_move_direction() const;

    private:
        //General Variables
        const float _bodyWidth;
        const Grid& _gameGrid;
        sf::CircleShape _head;
        sf::Vector2u _headpos;
        std::queue<MovementDirection> _inputBuffer;

        //Tail Variables
        std::vector<sf::Vector2u> _tailPosList;
        std::deque<sf::Vertex> _stripPositions;
        sf::VertexArray _tailStrip;
        MovementDirection get_opposite(MovementDirection direction);
        
        //Methods
        std::optional<MovementDirection> get_next_direction();
        std::array<sf::Vector2f, 2> calc_width_vertex(sf::Vector2f position, float radiansDirection, float width);
        void update_tail();
};