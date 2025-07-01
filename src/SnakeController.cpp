#include "SnakeController.hpp"
#include "AssetHandler.hpp"
#include "Button.hpp"
#include "SnakeConfig.hpp"
#include "SnakeModel.hpp"
#include <SFML/System/Vector2.hpp>
#include "Screen.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include "SnakeGameRenderer.hpp"
#include "utility.hpp"

SnakeController::SnakeController() :
    m_model(&m_textureHandler),
    m_window(
        sf::VideoMode(SnakeConfig::WINDOW_DIMENSIONS),
        SnakeConfig::GAME_TITLE,
        sf::Style::Titlebar | sf::Style::Close),
    m_renderer(&m_window, &m_textureHandler),
    m_endScreen(
        &m_textureHandler,
        m_textureHandler.getTexture("gameover.png"),
        ""
    ),
    m_startScreen(
        &m_textureHandler,
        m_textureHandler.getTexture("logo.png"),
        ""
    )
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    sf::View gridView(sf::FloatRect({0, 0}, {800, 800}));
    m_window.setView(gridView);

    Button playButton(
        SnakeConfig::BUTTON_1_POS,
        "PLAY AGAIN",
        m_textureHandler.getFont("ui-font.ttf"),
        [this](){
            m_model = SnakeModel(&m_textureHandler);
            m_renderer = SnakeGameRenderer(&m_window, &m_textureHandler);
            m_gameState = GameMode::GAME;
        }
    );
    m_endScreen.addButton(playButton);
    
    Button startButton(
        SnakeConfig::BUTTON_1_POS,
        "START",
        m_textureHandler.getFont("ui-font.ttf"),
        [this](){
            m_gameState = GameMode::GAME;
        }
    );
    m_startScreen.addButton(startButton);

    Button quitButton(
        SnakeConfig::BUTTON_2_POS,
        "QUIT",
        m_textureHandler.getFont("ui-font.ttf"),
        [this](){
            m_window.close();
        }
    );
    m_endScreen.addButton(quitButton);
    m_startScreen.addButton(quitButton);
}

bool SnakeController::hasLost()
{
    const auto player = *m_model.getPlayer();
    auto headpos = player.getPosition();
    auto bodypositions = player.getBodyPositions();

    const bool colliding = std::any_of(
        bodypositions.begin()+1,
        bodypositions.end(),
        [headpos](BodyPos segment)
        {return segment.position == headpos;}
    );

    if (colliding) return true;

    sf::Vector2i corner = {SnakeConfig::GRID_DIMENSIONS.x-1, SnakeConfig::GRID_DIMENSIONS.y-1};
    if (!pointInRect(headpos, {0,0}, corner)) return true;

    return false;
}

void SnakeController::processGameEvents()
{
    while (const  std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Left:
                addMoveToBuffer(Direction::LEFT);
                break;
            case sf::Keyboard::Key::Right:
                addMoveToBuffer(Direction::RIGHT);
                break;
            case sf::Keyboard::Key::Up:
                addMoveToBuffer(Direction::UP);
                break;
            case sf::Keyboard::Key::Down:
                addMoveToBuffer(Direction::DOWN);
                break;
            default: ;
            }
        }
    }
}

void SnakeController::processMenuEvents(std::vector<Button>* buttons)
{
    while (const  std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f clickCoords = m_window.mapPixelToCoords(mouseEvent->position);
                for (Button button : *buttons) {
                    button.handleMouseClick(clickCoords);
                }
            }
        }
    }
}

void SnakeController::destroyFruit(int index) {
    m_model.destroyFruitIndex(index);
    m_renderer.destroyFruitSprite(index);
}

void SnakeController::playSnake()
{
    processGameEvents();

    if (m_timer.getElapsedTime().asSeconds() > SnakeConfig::UPDATE_RATE) {
        if (!m_inputBuffer.empty()) {
            m_model.getPlayer()->setDirection(*getNextDirection());
        }
        m_model.getPlayer()->update();
        for (int i = 0; i < m_model.getFruitList().size(); i++) {
            if (m_model.getPlayer()->getPosition() == m_model.getFruitList().at(i)) {
                m_model.getPlayer()->incrementLength();
                destroyFruit(i);
                for (int i = 0 ; i < rand() % 3; i++) {
                    createFruit();
                }
            }
        }

        if (m_model.getFruitList().size() == 0) {
            createFruit();
        }

        m_timer.restart();
    }

    SnakeGameRenderer::GameState newGameState = {
        m_model.getPlayer()->getBodyPositions(),
        m_model.getPlayer()->getPosition(),
        m_model.getPlayer()->getMoveDirection(),
        m_model.getScore()
    };

    if (hasLost())
    {
        m_gameState = GameMode::OVER;
        m_endScreen.setSubtext("Score: " + std::to_string(m_model.getScore()));
    } else if (m_model.getPlayer()->getLength() == SnakeConfig::AVAILIABLE_SQUARES)
    {
        m_gameState = GameMode::OVER;
        m_endScreen.setSubtext("You Won!");
    }
    else
    {
        m_renderer.update(newGameState);
    }
}

void SnakeController::createFruit() {
    int filledSquares = m_model.getPlayer()->getLength() + m_model.getFruitList().size() - 1;
    if (filledSquares < SnakeConfig::AVAILIABLE_SQUARES) {
        sf::Vector2i position{rand() % SnakeConfig::GRID_DIMENSIONS.x, rand() % SnakeConfig::GRID_DIMENSIONS.y };

        auto bodypositions = m_model.getPlayer()->getBodyPositions();
        auto fruitList = m_model.getFruitList();
        while (
            std::any_of(
                fruitList.begin(),
                fruitList.end(),
                [position](const sf::Vector2i& fruit_pos)
                {
                    return fruit_pos == position;}
            )
            ||  std::any_of(
                bodypositions.begin(),
                bodypositions.end(),
                [position](BodyPos segment)
                {return segment.position == position;})
        )
        {
            position = {rand() % SnakeConfig::GRID_DIMENSIONS.x, rand() % SnakeConfig::GRID_DIMENSIONS.y };
        }

        m_model.createFruit(position);
        m_renderer.createFruitSprite(position);
    }
}

void SnakeController::playGame()
{
    while (m_window.isOpen())
    {
        switch (m_gameState)
        {
        case GameMode::GAME:
            playSnake();
            m_window.clear(sf::Color::Black);
            m_window.draw(m_renderer);
            break;
        case GameMode::OVER:
            processMenuEvents(m_endScreen.getButtons());
            m_window.clear();
            m_window.draw(m_endScreen);
            break;
        case GameMode::START:
            processMenuEvents(m_startScreen.getButtons());
            m_window.clear();
            m_window.draw(m_startScreen);
            break;
        }
        m_window.display();
    }
}

void SnakeController::addMoveToBuffer(const Direction move) {
    if (m_inputBuffer.size() < SnakeConfig::MOVE_QUEUE_SIZE) {
        if (m_inputBuffer.empty()) {
            if (
                const Direction player_direction = m_model.getPlayer()->getMoveDirection();
                player_direction != move
                && player_direction != getOpposite(move))
            {m_inputBuffer.push(move);}
        } else if (m_inputBuffer.back() != move && m_inputBuffer.back() != getOpposite(move)) {
            m_inputBuffer.push(move);
        }
    }
}

std::optional<Direction> SnakeController::getNextDirection() {
    if (!m_inputBuffer.empty()) {
        Direction direction = m_inputBuffer.front();
        m_inputBuffer.pop();

        return direction;
    }

    return std::nullopt;
}