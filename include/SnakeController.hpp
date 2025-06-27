#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <queue>
#include <vector>
#include "SnakeModel.hpp"
#include "Button.hpp"

struct Menu
{
    sf::Sprite logo;
    sf::Text subtext;
    std::vector<Button> buttons;
};

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
    void processMenuEvents(std::vector<Button> buttons);
    void startSnake();
    void drawGame(); 
};
