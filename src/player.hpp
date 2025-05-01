#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

const float MOVEMENT_SPEED = 5.f;
const int MOVE_QUEUE_SIZE = 2;
const sf::Color PLAYER_COLOR(245, 66, 129);
const int TAIL_UPDATE_DELAY = 1;

enum class MovementDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

sf::Vector2f direction_to_vector(MovementDirection direction, float magnitude);

class Player {
    public: 
        

        MovementDirection direction;

        Player(float bodyWidth) : _bodyWidth(bodyWidth) {
            _head.setRadius(_bodyWidth/2);
            _head.setFillColor(PLAYER_COLOR);

            _removingTail = true;
            _delayCounter = 0;

            direction = MovementDirection::RIGHT;

            sf::Vector2f initialPos = _head.getPosition();
            sf::Vector2f initialWidthVertex = calc_width_vertex(_head.getPosition(), direction, _bodyWidth);

            _stripPositions.push_front(sf::Vertex({initialPos, PLAYER_COLOR}));
            _stripPositions.push_front(sf::Vertex({initialWidthVertex, PLAYER_COLOR}));

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        }

        sf::Vector2f calc_width_vertex(sf::Vector2f position, MovementDirection movement_direction, float width);

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();

        void update_tail();

        MovementDirection get_move_direction();

        void update();

        void add_move_to_buffer(const MovementDirection move);
    private:
        int _delayCounter;
        float _bodyWidth;
        bool _removingTail;
        sf::CircleShape _head;
        std::deque<sf::Vertex> _stripPositions;
        std::queue<MovementDirection> _inputBuffer;
        sf::VertexArray _tailStrip;

        std::optional<MovementDirection> get_next_direction();
};