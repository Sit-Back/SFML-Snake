#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "utility.hpp"

std::vector<sf::Vector2f> calcWidthVertex(sf::Vector2f position, sf::Angle angle);
SquareLocation travelEntry(Direction search_dir);

class Player final : public sf::Drawable {
    public:
        struct BodyPos
        {
            sf::Vector2i position;
            Direction direction;
        };

        static const sf::Color PLAYER_COLOR;
        static constexpr int MOVE_QUEUE_SIZE = 2;
        static constexpr int TURN_RESOLUTION = 10;
        static constexpr int INITIAL_PLAYER_LENGTH = 4;
        static constexpr float PLAYER_WIDTH = 40;

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