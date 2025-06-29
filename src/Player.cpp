#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Player.hpp"
#include "utility.hpp"

Player::Player()
{
    m_headPos = {5, 7};
    m_direction = Direction::RIGHT;
    m_length = INITIAL_PLAYER_LENGTH;

    sf::Vector2i pos = m_headPos;
    for (int i = 0; i < m_length; i++)
    {
        m_bodyPositions.emplace_back(pos, m_direction);
        shiftPosition(pos, getOpposite(m_direction));
    }
}

//Main Updates
void Player::update()
{
    shiftPosition(m_headPos, m_direction);
    m_bodyPositions.emplace_front(m_headPos, m_direction);

    if (m_bodyPositions.size() > m_length)
    {
        m_bodyPositions.pop_back();
    }
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
}

//Support Functions
SquareLocation travelEntry(const Direction search_dir)
{
    switch (search_dir)
    {
    case Direction::LEFT:
        return SquareLocation::RIGHT;
    case Direction::RIGHT:
        return SquareLocation::LEFT;
    case Direction::UP:
        return SquareLocation::BOTTOM;
    case Direction::DOWN:
        return SquareLocation::TOP;
    }

    throw std::invalid_argument("Invalid Direction");
}



void Player::incrementLength()
{
    m_length++;
}

std::deque<BodyPos> Player::getBodyPositions() const
{
    return m_bodyPositions;
}

// Getter Functions
int Player::getLength() const { return m_length; }
Direction Player::getMoveDirection() const { return m_direction; }
sf::Vector2i Player::getPosition() const { return m_headPos; }