#pragma once

#include "AssetHandler.hpp"
#include <SFML/Graphics.hpp>
#include <deque>
#include <vector>
#include "utility.hpp"

struct GameState {
    std::deque<BodyPos> segmentPositions;
    sf::Vector2i headPos;
    Direction direction;
    std::vector<sf::Vector2i> fruitPositions;
};

class SnakeGameRenderer final : public sf::Drawable {
    public:
        SnakeGameRenderer(sf::RenderWindow* window, AssetHandler* assetHandler);
        void update(const GameState& newGameState);
        void draw(sf::RenderTarget& target, const sf::RenderStates states) const;
    private:
        static const sf::Color PLAYER_COLOR;
        static constexpr float PLAYER_WIDTH = 40;
        static constexpr int TURN_RESOLUTION = 10;
        sf::VertexArray m_gridVertices;

        void drawPlayer(sf::RenderTarget& target, const sf::RenderStates states) const;
        std::vector<sf::Vector2f> calcWidthVertex(sf::Vector2f position, sf::Angle angle) const;
        void addVertices(const std::vector<sf::Vector2f>& points);
        std::vector<sf::Vector2f> generateCircleVertices(sf::Vector2i initialPos, Direction initialDirection,
                                                           Direction finalDirection) const;
        void generateGridVertices();
        void updateTail(std::deque<BodyPos> bodyPositions);
        sf::Vector2f getHeadCenter(sf::Vector2i headPos) const;
        sf::RenderWindow* m_window;
        AssetHandler* m_assetHandler;
        sf::CircleShape m_headSprite;
        sf::CircleShape m_endSprite;
        sf::Sprite m_eyeSprite;
        sf::VertexArray m_tailStrip;
        
        std::vector<sf::Sprite> fruitSprites;
};