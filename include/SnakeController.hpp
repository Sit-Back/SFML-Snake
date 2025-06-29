#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <queue>
#include <vector>
#include "SnakeModel.hpp"
#include "Button.hpp"
#include "SnakeGameRenderer.hpp"

class SnakeController
{
public:
    SnakeController();
    bool hasLost();
    void playSnake();
    void gameOver();
    void playGame();

private:
    AssetHandler m_textureHandler;
    SnakeModel m_model;
    std::queue<Direction> m_inputBuffer;
    sf::RenderWindow m_window;
    SnakeGameRenderer m_renderer;
    sf::Clock m_timer;
    GameMode m_gameState = GameMode::GAME;
    void addMoveToBuffer(Direction move);
    std::optional<Direction> getNextDirection();
    void processGameEvents();
    void processMenuEvents(std::vector<Button> buttons);
    void startSnake();
    void drawGame(); 
};
