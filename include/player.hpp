#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "utility.hpp"

constexpr int MOVE_QUEUE_SIZE = 2;
constexpr sf::Color PLAYER_COLOR(245, 66, 129);
constexpr int TURN_RESOLUTION = 10;
constexpr int INITIAL_PLAYER_LENGTH = 4;
constexpr float PLAYER_WIDTH = 40;

std::vector<sf::Vector2f> calc_width_vertex(sf::Vector2f position, sf::Angle angle);
SquareLocation travel_entry(Direction search_dir);

class Player final : public sf::Drawable {
    public:
        //Constructors
        explicit Player(const sf::Texture* eyeTexture);
        void update();

        //General Methods
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void increment_length();
        void set_direction(Direction direction);
        bool is_colliding(sf::Vector2i point) const;

        //Getter Methods
        sf::Vector2f get_position() const;
        sf::Vector2i get_position_grid() const;
        sf::Vector2f get_head_center() const;
        Direction  get_move_direction() const;
        int get_length() const;

    private:
        //General Variables
        sf::CircleShape _head;
        sf::CircleShape _end;
        sf::Vector2i _headPos;
        sf::Sprite _eyeSprite;
        Direction _direction;
        int _length;

        //Tail Variables
        std::deque<sf::Vector2i> _turnPosList;
        sf::VertexArray _tailStrip;
        
        //Methods
        std::vector<sf::Vector2f> generate_circle_vertices(sf::Vector2i initialPos, Direction initialDirection, Direction finalPosition) const;
        void add_vertices(const std::vector<sf::Vector2f>& points);
        void update_tail();
};