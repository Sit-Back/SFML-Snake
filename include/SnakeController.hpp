#pragma once
#include <queue>
#include "SnakeModel.hpp"
#include "Button.hpp"

constexpr float UPDATE_RATE = 0.15;
const std::string GAME_TITLE = "Snake Game";
constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};

class SnakeController
{
public:
    SnakeController();
    bool hasLost();
    void playSnake();
    void gameOver();
    void playGame();

private:
    enum class GameState
    {
        GAME,
        START,
        OVER
    };

    AssetHandler m_textureHandler;
    SnakeModel m_model;
    std::queue<Direction> m_inputBuffer;
    sf::RenderWindow m_window;
    sf::Clock m_timer;
    GameState m_gameState = GameState::GAME;
    void addMoveToBuffer(Direction move);
    std::optional<Direction> getNextDirection();
    void processGameEvents();
    void processMenuEvents();
    void startSnake();
    void drawGame(); 

    Button m_testButton;
};
