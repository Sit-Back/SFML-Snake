#include <queue>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "utility.hpp"

Player::Player(const sf::Texture* eyeTexture) : _eyeSprite(*eyeTexture)
{
    _headPos = {5, 7};
    _direction = Direction::RIGHT;
    _length = INITIAL_PLAYER_LENGTH;

    sf::Vector2i pos = _headPos;
    for (int i = 0; i < _length; i++)
    {
        _bodyPositions.emplace_back(pos, _direction);
        move_position(pos, get_opposite(_direction));
    }




    // Head
    _head.setOrigin({PLAYER_WIDTH / 2, PLAYER_WIDTH / 2});
    _head.setPosition(get_head_center());
    _head.setRadius(PLAYER_WIDTH / 2);
    _head.setFillColor(PLAYER_COLOR);
    sf::Vector2f eyeBounds = _eyeSprite.getLocalBounds().size;
    float eyeScaleX = (PLAYER_WIDTH + PLAYER_WIDTH / 3) / static_cast<float>(eyeTexture->getSize().x);
    float eyeScaleY = (PLAYER_WIDTH + PLAYER_WIDTH / 3) / static_cast<float>(eyeTexture->getSize().y);
    sf::Vector2f eyeScale = {eyeScaleX, eyeScaleY};
    _eyeSprite.setOrigin({eyeBounds.x / 2, eyeBounds.y / 2});
    _eyeSprite.scale(eyeScale);
    _eyeSprite.setPosition(get_head_center());
    _eyeSprite.setRotation(direction_to_angle(_direction));

    // Tail
    _tailStrip.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    _end.setRadius(PLAYER_WIDTH / 2);
    _end.setFillColor(PLAYER_COLOR);
    _end.setOrigin({PLAYER_WIDTH / 2, PLAYER_WIDTH / 2});

    update_tail();
}

//Main Updates
void Player::update()
{
    move_position(_headPos, _direction);
    _bodyPositions.emplace_front(_headPos, _direction);

    if (_bodyPositions.size() > _length)
    {
        _bodyPositions.pop_back();
    }

    _head.setPosition(get_head_center());
    _eyeSprite.setPosition(get_head_center());
    _eyeSprite.setRotation(direction_to_angle(_direction));

    update_tail();
}

void Player::set_direction(Direction direction)
{
    _direction = direction;
}

void Player::update_tail()
{
    _tailStrip.clear();

    Direction previousDirection = get_opposite(_bodyPositions[0].direction);
    for (int i = 0; i < _bodyPositions.size()-1; i++)
    {
        const sf::Vector2i position = _bodyPositions[i].position;
        const Direction direction = get_opposite(_bodyPositions[i].direction);

        if (previousDirection != direction)
        {
            add_vertices(generate_circle_vertices(position, previousDirection, direction));
        } else
        {
            add_vertices(calc_width_vertex
            (
                grid_pos_coordinates(position, SquareLocation::CENTER),
                direction_to_angle(direction))
            );
        }
        previousDirection = get_opposite(_bodyPositions[i].direction);
    }

    sf::Vector2i endpos = _bodyPositions[_bodyPositions.size()-1].position;
    add_vertices(calc_width_vertex
            (
                grid_pos_coordinates(endpos, SquareLocation::CENTER),
                direction_to_angle(previousDirection))
            );
    _end.setPosition(grid_pos_coordinates(endpos, SquareLocation::CENTER));
}

//Support Functions
SquareLocation travel_entry(const Direction search_dir)
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

void Player::add_vertices(const std::vector<sf::Vector2f>& points)
{
    for (sf::Vector2f point : points)
    {
        _tailStrip.append(sf::Vertex({point, PLAYER_COLOR}));
    }
}

void Player::increment_length()
{
    _length++;
}

std::vector<sf::Vector2f> Player::generate_circle_vertices(sf::Vector2i initialPos, Direction initialDirection,
                                                           Direction finalDirection) const
{
    std::vector<sf::Vector2f> circleVertices;
    sf::Angle differenceAngle = direction_to_angle(finalDirection) - direction_to_angle(initialDirection);
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

        initialAngle = direction_to_angle(initialDirection) + sf::radians(M_PI_2);
        origin = grid_pos_coordinates(initialPos, potentialOrigin[0]);
    }
    else
    {
        //Right/Clockwise

        initialAngle = direction_to_angle(initialDirection) - sf::radians(M_PI_2);
        origin = grid_pos_coordinates(initialPos, potentialOrigin[1]);
    }

    for (int i = 1; i < TURN_RESOLUTION + 1; i++)
    {
        sf::Angle currentAngle = initialAngle + static_cast<float>(i) * (differenceAngle / (TURN_RESOLUTION + 1));
        const float rise = (GRID_SIZE / 2) * std::sin(currentAngle.asRadians());
        const float run = (GRID_SIZE / 2) * std::cos(currentAngle.asRadians());

        const sf::Vector2f pointPosition = {origin.x + run, origin.y + rise};
        float perpanGradient = -run / rise;
        sf::Angle angle = sf::radians(std::atan(perpanGradient));
        angle = initialDirection == Direction::LEFT || finalDirection == Direction::LEFT
                    ? angle - sf::radians(M_PI)
                    : angle;

        std::vector<sf::Vector2f> vertices = calc_width_vertex(pointPosition, angle);
        circleVertices.push_back(vertices[0]);
        circleVertices.push_back(vertices[1]);
    }

    return circleVertices;
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    target.draw(_head, states);
    target.draw(_end, states);
    target.draw(_tailStrip, states);
    target.draw(_eyeSprite, states);
}

std::vector<sf::Vector2f> calc_width_vertex(sf::Vector2f position, sf::Angle angle)
{
    //Get a direction vector of the angle and stretch to the length of width
    sf::Vector2f initialVector;
    initialVector.x = PLAYER_WIDTH / 2 * std::cos(angle.asRadians());
    initialVector.y = PLAYER_WIDTH / 2 * std::sin(angle.asRadians());

    //Rotate the initial vector to both sides
    sf::Vector2f rotation1 = rotate_vector(initialVector, sf::radians(M_PI_2));
    sf::Vector2f rotation2 = rotate_vector(initialVector, sf::radians(-M_PI_2));

    //Apply transformation to the initial position supplied
    sf::Vector2f pos1{position.x + rotation1.x, position.y + rotation1.y};
    sf::Vector2f pos2{position.x + rotation2.x, position.y + rotation2.y};

    return std::vector<sf::Vector2f>{pos1, pos2};
}

std::deque<bodyPos> Player::get_body_positions() const
{
    return _bodyPositions;
}

// Getter Functions
int Player::get_length() const { return _length; }
sf::Vector2f Player::get_position() const { return _head.getPosition(); }
sf::Vector2i Player::get_position_grid() const { return _headPos; }
Direction Player::get_move_direction() const { return _direction; }

sf::Vector2f Player::get_head_center() const
{
    return grid_pos_coordinates(_headPos, SquareLocation::CENTER);
}
