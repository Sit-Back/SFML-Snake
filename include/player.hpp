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
        MovementDirection _direction;

        Player(const Grid& gameGrid, float bodyWidth) : _bodyWidth(bodyWidth), _gameGrid(gameGrid){
            _head.setRadius(_bodyWidth/2);
            _head.setFillColor(PLAYER_COLOR);

            _headpos = {0, 0};

            _removingTail = true;
            _delayCounter = 0;

            _direction = MovementDirection::RIGHT;

            std::array<sf::Vector2f,2> initialVerticies = calc_width_vertex(get_head_center(), direction_to_radian(_direction), _bodyWidth/2-1);

            _stripPositions.push_front(sf::Vertex({initialVerticies[0], PLAYER_COLOR}));
            _stripPositions.push_front(sf::Vertex({initialVerticies[1], PLAYER_COLOR}));

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        }

        std::array<sf::Vector2f, 2> calc_width_vertex(sf::Vector2f position, float radiansDirection, float width);

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position() const;
        sf::Vector2u get_position_grid() const;
        sf::Vector2f get_head_center() const;

        MovementDirection  get_move_direction() const;

        void update();

        void add_move_to_buffer(const MovementDirection move);

        void move_player(MovementDirection direction);
    private:
        sf::Vector2u _headpos;
        MovementDirection get_opposite(MovementDirection direction);
        std::vector<sf::Vector2u> _tailPosList;
        int _delayCounter;
        const float _bodyWidth;
        bool _removingTail;
        sf::CircleShape _head;
        std::deque<sf::Vertex> _stripPositions;
        std::queue<MovementDirection> _inputBuffer;
        sf::VertexArray _tailStrip;
        std::optional<MovementDirection> get_next_direction();
        const Grid& _gameGrid;
        void update_tail();
};