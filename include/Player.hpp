#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "utility.hpp"

std::vector<sf::Vector2f> calcWidthVertex(sf::Vector2f position, sf::Angle angle);
SquareLocation travelEntry(Direction search_dir);

class Player {
    public:
        static constexpr int INITIAL_PLAYER_LENGTH = 4;
        

        //Constructors
        explicit Player();
        void update();

        //General Methods
        void incrementLength();
        void setDirection(Direction direction);

        //Getter Methods
        std::deque<BodyPos> getBodyPositions() const;
        sf::Vector2i getPosition() const;
        Direction  getMoveDirection() const;
        int getLength() const;

    private:
        //General Variables
        sf::Vector2i m_headPos;
        Direction m_direction;
        int m_length;
        std::deque<BodyPos> m_bodyPositions;
};