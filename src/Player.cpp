#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "utility.hpp"
#include "SnakeConfig.hpp"

const sf::Color Player::PLAYER_COLOR(245, 66, 129);

Player::Player(const sf::Texture* eyeTexture) : m_eyeSprite(*eyeTexture)
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

    // Head
    m_head.setOrigin({PLAYER_WIDTH / 2, PLAYER_WIDTH / 2});
    m_head.setPosition(getHeadCenter());
    m_head.setRadius(PLAYER_WIDTH / 2);
    m_head.setFillColor(PLAYER_COLOR);
    sf::Vector2f eyeBounds = m_eyeSprite.getLocalBounds().size;
    float eyeScaleX = (PLAYER_WIDTH + PLAYER_WIDTH / 3) / static_cast<float>(eyeTexture->getSize().x);
    float eyeScaleY = (PLAYER_WIDTH + PLAYER_WIDTH / 3) / static_cast<float>(eyeTexture->getSize().y);
    sf::Vector2f eyeScale = {eyeScaleX, eyeScaleY};
    m_eyeSprite.setOrigin({eyeBounds.x / 2, eyeBounds.y / 2});
    m_eyeSprite.scale(eyeScale);
    m_eyeSprite.setPosition(getHeadCenter());
    m_eyeSprite.setRotation(directionToAngle(m_direction));

    // Tail
    m_tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    m_end.setRadius(PLAYER_WIDTH / 2);
    m_end.setFillColor(PLAYER_COLOR);
    m_end.setOrigin({PLAYER_WIDTH / 2, PLAYER_WIDTH / 2});

    updateTail();
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

    m_head.setPosition(getHeadCenter());
    m_eyeSprite.setPosition(getHeadCenter());
    m_eyeSprite.setRotation(directionToAngle(m_direction));

    updateTail();
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
}

void Player::updateTail()
{
    m_tailStrip.clear();

    Direction previousDirection = getOpposite(m_bodyPositions[0].direction);
    for (int i = 0; i < m_bodyPositions.size()-1; i++)
    {
        const sf::Vector2i position = m_bodyPositions[i].position;
        const Direction direction = getOpposite(m_bodyPositions[i].direction);

        if (previousDirection != direction)
        {
            addVertices(generateCircleVertices(position, previousDirection, direction));
        } else
        {
            addVertices(calcWidthVertex
            (
                gridCoordinates(position, SquareLocation::CENTER),
                directionToAngle(direction))
            );
        }
        previousDirection = getOpposite(m_bodyPositions[i].direction);
    }

    sf::Vector2i endpos = m_bodyPositions[m_bodyPositions.size()-1].position;
    addVertices(calcWidthVertex
            (
                gridCoordinates(endpos, SquareLocation::CENTER),
                directionToAngle(previousDirection))
            );
    m_end.setPosition(gridCoordinates(endpos, SquareLocation::CENTER));
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

void Player::addVertices(const std::vector<sf::Vector2f>& points)
{
    for (sf::Vector2f point : points)
    {
        m_tailStrip.append(sf::Vertex({point, PLAYER_COLOR}));
    }
}

void Player::incrementLength()
{
    m_length++;
}

std::vector<sf::Vector2f> Player::generateCircleVertices(sf::Vector2i initialPos, Direction initialDirection,
                                                           Direction finalDirection) const
{
    std::vector<sf::Vector2f> circleVertices;
    sf::Angle differenceAngle = directionToAngle(finalDirection) - directionToAngle(initialDirection);
    differenceAngle = differenceAngle.wrapSigned();


    SquareLocation potentialOrigin[2]; //First entry is for if the user turns left, second is for if they turn right.
    switch (initialDirection)
    {
    case Direction::RIGHT:
        potentialOrigin[0] = SquareLocation::TOP_LEFT;
        potentialOrigin[1] = SquareLocation::BOTTOM_LEFT;
        break;
    case Direction::LEFT:
        potentialOrigin[0] = SquareLocation::BOTTOM_RIGHT;
        potentialOrigin[1] = SquareLocation::TOP_RIGHT;
        break;
    case Direction::UP:
        potentialOrigin[0] = SquareLocation::BOTTOM_LEFT;
        potentialOrigin[1] = SquareLocation::BOTTOM_RIGHT;
        break;
    case Direction::DOWN:
        potentialOrigin[0] = SquareLocation::TOP_RIGHT;
        potentialOrigin[1] = SquareLocation::TOP_LEFT;
        break;
    default:
        throw std::invalid_argument("Invalid direction.");
    }

    sf::Vector2f origin;
    sf::Angle initialAngle;
    if (differenceAngle.asRadians() < 0)
    {
        //Left/Counter-Clockwise

        initialAngle = directionToAngle(initialDirection) + sf::radians(M_PI_2);
        origin = gridCoordinates(initialPos, potentialOrigin[0]);
    }
    else
    {
        //Right/Clockwise

        initialAngle = directionToAngle(initialDirection) - sf::radians(M_PI_2);
        origin = gridCoordinates(initialPos, potentialOrigin[1]);
    }

    for (int i = 1; i < TURN_RESOLUTION + 1; i++)
    {
        sf::Angle currentAngle = initialAngle + static_cast<float>(i) * (differenceAngle / (TURN_RESOLUTION + 1));
        const float rise = (SnakeConfig::GRID_SIZE / 2) * std::sin(currentAngle.asRadians());
        const float run = (SnakeConfig::GRID_SIZE / 2) * std::cos(currentAngle.asRadians());

        const sf::Vector2f pointPosition = {origin.x + run, origin.y + rise};
        float perpanGradient = -run / rise;
        sf::Angle angle = sf::radians(std::atan(perpanGradient));
        angle = initialDirection == Direction::LEFT || finalDirection == Direction::LEFT
                    ? angle - sf::radians(M_PI)
                    : angle;

        std::vector<sf::Vector2f> vertices = calcWidthVertex(pointPosition, angle);
        circleVertices.push_back(vertices[0]);
        circleVertices.push_back(vertices[1]);
    }

    return circleVertices;
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    target.draw(m_head, states);
    target.draw(m_end, states);
    target.draw(m_tailStrip, states);
    target.draw(m_eyeSprite, states);
}

std::vector<sf::Vector2f> calcWidthVertex(sf::Vector2f position, sf::Angle angle)
{
    //Get a direction vector of the angle and stretch to the length of width
    sf::Vector2f initialVector;
    initialVector.x = Player::PLAYER_WIDTH / 2 * std::cos(angle.asRadians());
    initialVector.y = Player::PLAYER_WIDTH / 2 * std::sin(angle.asRadians());

    //Rotate the initial vector to both sides
    sf::Vector2f rotation1 = rotateVector(initialVector, sf::radians(M_PI_2));
    sf::Vector2f rotation2 = rotateVector(initialVector, sf::radians(-M_PI_2));

    //Apply transformation to the initial position supplied
    sf::Vector2f pos1{position.x + rotation1.x, position.y + rotation1.y};
    sf::Vector2f pos2{position.x + rotation2.x, position.y + rotation2.y};

    return std::vector<sf::Vector2f>{pos1, pos2};
}

std::deque<Player::BodyPos> Player::getBodyPositions() const
{
    return m_bodyPositions;
}

// Getter Functions
int Player::getLength() const { return m_length; }
sf::Vector2f Player::getPosition() const { return m_head.getPosition(); }
sf::Vector2i Player::getPositionGrid() const { return m_headPos; }
Direction Player::getMoveDirection() const { return m_direction; }

sf::Vector2f Player::getHeadCenter() const
{
    return gridCoordinates(m_headPos, SquareLocation::CENTER);
}
