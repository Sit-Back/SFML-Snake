#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

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
        

        MovementDirection direction;

        Player(float bodyWidth) : _bodyWidth(bodyWidth) {
            _headRadius = _bodyWidth/2;
            _head.setRadius(_headRadius);
            _head.setFillColor(PLAYER_COLOR);

            _removingTail = true;
            _delayCounter = 0;

            direction = MovementDirection::RIGHT;

            std::array<sf::Vector2f,2> initialVerticies = calc_width_vertex(get_head_center(), direction_to_radian(direction), _bodyWidth/2-2);

            _stripPositions.push_front(sf::Vertex({initialVerticies[0], PLAYER_COLOR}));
            _stripPositions.push_front(sf::Vertex({initialVerticies[1], PLAYER_COLOR}));

            _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        }

        std::array<sf::Vector2f, 2> calc_width_vertex(sf::Vector2f position, float radiansDirection, float width);

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();
        sf::Vector2f get_head_center();

        void update_tail();

        MovementDirection get_move_direction();

        void update();

        void add_move_to_buffer(const MovementDirection move);
    private:
        float _headRadius;
        int _delayCounter;
        float _bodyWidth;
        bool _removingTail;
        sf::CircleShape _head;
        std::deque<sf::Vertex> _stripPositions;
        std::queue<MovementDirection> _inputBuffer;
        sf::VertexArray _tailStrip;
        std::optional<MovementDirection> get_next_direction();
};