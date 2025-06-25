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

struct BodyPos
{
    sf::Vector2i position;
    Direction direction;
};

std::vector<sf::Vector2f> calcWidthVertex(sf::Vector2f position, sf::Angle angle);
SquareLocation travelEntry(Direction search_dir);

class Player final : public sf::Drawable {
    public:
        //Constructors
        explicit Player(const sf::Texture* eyeTexture);
        void update();

        //General Methods
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void incrementLength();
        void setDirection(Direction direction);

        //Getter Methods
        sf::Vector2f getPosition() const;
        std::deque<BodyPos> getBodyPositions() const;
        sf::Vector2i getPositionGrid() const;
        sf::Vector2f getHeadCenter() const;
        Direction  getMoveDirection() const;
        int getLength() const;

    private:
        //General Variables
        sf::CircleShape m_head;
        sf::CircleShape m_end;
        sf::Vector2i m_headPos;
        sf::Sprite m_eyeSprite;
        Direction m_direction;
        int m_length;

        //Tail Variables
        std::deque<BodyPos> m_bodyPositions;
        sf::VertexArray m_tailStrip;
        
        //Methods
        std::vector<sf::Vector2f> generateCircleVertices(sf::Vector2i initialPos, Direction initialDirection, Direction finalPosition) const;
        void addVertices(const std::vector<sf::Vector2f>& points);
        void updateTail();
};