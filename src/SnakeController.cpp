#include "SnakeController.hpp"

#include <iostream>

SnakeController::SnakeController() :
    _model(&_textureHandler),
    _window(
        sf::VideoMode(WINDOW_DIMENSIONS),
        GAME_TITLE,
        sf::Style::Titlebar | sf::Style::Close)
{
    _window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(false);

    sf::View gridView(sf::FloatRect({0, 0}, {800, 800}));
    _window.setView(gridView);
}

void SnakeController::_draw_game()
{
    _window.clear(sf::Color::Black);
    _window.draw(_model.get_vertices());
    _window.draw(*_model.get_player());
    _model.draw_fruit(_window);
}

bool SnakeController::has_lost()
{
    const auto player = *_model.get_player();
    auto headpos = player.get_position_grid();
    auto bodypositions = player.get_body_positions();

    const bool colliding = std::any_of(
        bodypositions.begin()+1,
        bodypositions.end(),
        [headpos](bodyPos segment)
        {return segment.position == headpos;}
    );

    if (colliding) return true;

    sf::Vector2i corner = {GRID_DIMENSIONS.x-1, GRID_DIMENSIONS.y-1};
    if (!point_in_rect(headpos, {0,0}, corner)) return true;

    return false;
}

void SnakeController::_process_game_events()
{
    while (const  std::optional<sf::Event> event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            _window.close();
        } else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (key_pressed->code)
            {
            case sf::Keyboard::Key::Left:
                _add_move_to_buffer(Direction::LEFT);
                break;
            case sf::Keyboard::Key::Right:
                _add_move_to_buffer(Direction::RIGHT);
                break;
            case sf::Keyboard::Key::Up:
                _add_move_to_buffer(Direction::UP);
                break;
            case sf::Keyboard::Key::Down:
                _add_move_to_buffer(Direction::DOWN);
                break;
            default: ;
            }
        }
    }
}

void SnakeController::_process_menu_events()
{
    while (const  std::optional<sf::Event> event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            _window.close();
        }
    }
}

void SnakeController::play_snake()
{
    _process_game_events();

    if (_timer.getElapsedTime().asSeconds() > UPDATE_RATE) {
        if (!_inputBuffer.empty()) {
            _model.get_player()->set_direction(*_get_next_direction());
        }
        _model.get_player()->update();
        for (int i = 0; i < _model.get_fruit_list().size(); i++) {
            if (_model.get_player()->get_position_grid() == _model.get_fruit_list().at(i)) {
                _model.get_player()->increment_length();
                _model.destroy_fruit_index(i);
            }
        }
        _model.create_fruit();
        _timer.restart();
    }

    if (has_lost())
    {
        _model = SnakeModel(&_textureHandler);
        _gamestate = GameState::OVER;
    } else
    {
        _draw_game();
    }
}

void SnakeController::game_over()
{

}

void SnakeController::play_game()
{
    while (_window.isOpen())
    {
        switch (_gamestate)
        {
        case GameState::GAME:
            play_snake();
        case GameState::OVER:
            game_over();
        }
        _window.display();
    }
}

void SnakeController::_add_move_to_buffer(const Direction move) {
    if (_inputBuffer.size() < MOVE_QUEUE_SIZE) {
        if (_inputBuffer.empty()) {
            if (
                const Direction player_direction = _model.get_player()->get_move_direction();
                player_direction != move
                && player_direction != get_opposite(move))
            {_inputBuffer.push(move);}
        } else if (_inputBuffer.back() != move && _inputBuffer.back() != get_opposite(move)) {
            _inputBuffer.push(move);
        }
    }
}

std::optional<Direction> SnakeController::_get_next_direction() {
    if (!_inputBuffer.empty()) {
        Direction direction = _inputBuffer.front();
        _inputBuffer.pop();

        return direction;
    }

    return std::nullopt;
}