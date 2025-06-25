#include "SnakeController.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

SnakeController::SnakeController() :
    m_model(&m_textureHandler),
    m_window(
        sf::VideoMode(WINDOW_DIMENSIONS),
        GAME_TITLE,
        sf::Style::Titlebar | sf::Style::Close),
    m_testButton
(
        {0,0}, 
        "Play",
        m_textureHandler.getFont("ui-font.ttf"),
        [this]() {startSnake();}
)
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    sf::View gridView(sf::FloatRect({0, 0}, {800, 800}));
    m_window.setView(gridView);
}

void SnakeController::startSnake() {
    m_gameState = GameState::GAME;
}


void SnakeController::drawGame()
{
    m_window.clear(sf::Color::Black);
    m_window.draw(m_model.getVertices());
    m_window.draw(*m_model.getPlayer());
    m_model.drawFruit(m_window);
}

bool SnakeController::hasLost()
{
    const auto player = *m_model.getPlayer();
    auto headpos = player.getPositionGrid();
    auto bodypositions = player.getBodyPositions();

    const bool colliding = std::any_of(
        bodypositions.begin()+1,
        bodypositions.end(),
        [headpos](BodyPos segment)
        {return segment.position == headpos;}
    );

    if (colliding) return true;

    sf::Vector2i corner = {GRID_DIMENSIONS.x-1, GRID_DIMENSIONS.y-1};
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

void SnakeController::processMenuEvents()
{
    while (const  std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                m_testButton.handleMouseClick(m_window.mapPixelToCoords(mouseEvent->position));
            }
        }
    }
}

void SnakeController::playSnake()
{
    processGameEvents();

    if (m_timer.getElapsedTime().asSeconds() > UPDATE_RATE) {
        if (!m_inputBuffer.empty()) {
            m_model.getPlayer()->setDirection(*getNextDirection());
        }
        m_model.getPlayer()->update();
        for (int i = 0; i < m_model.getFruitList().size(); i++) {
            if (m_model.getPlayer()->getPositionGrid() == m_model.getFruitList().at(i)) {
                m_model.getPlayer()->incrementLength();
                m_model.destroyFruitIndex(i);
            }
        }
        m_model.createFruit();
        m_timer.restart();
    }

    if (hasLost())
    {
        m_model = SnakeModel(&m_textureHandler);
        m_gameState = GameState::OVER;
    } else
    {
        drawGame();
    }
}

void SnakeController::gameOver()
{
    processMenuEvents();

    m_window.clear();
    m_window.draw(m_testButton);
}

void SnakeController::playGame()
{
    while (m_window.isOpen())
    {
        switch (m_gameState)
        {
        case GameState::GAME:
            playSnake();
            break;
        case GameState::OVER:
            gameOver();
            break;
        }
        m_window.display();
    }
}

void SnakeController::addMoveToBuffer(const Direction move) {
    if (m_inputBuffer.size() < MOVE_QUEUE_SIZE) {
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