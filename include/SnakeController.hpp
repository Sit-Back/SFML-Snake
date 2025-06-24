#pragma once
#include <queue>
#include "SnakeModel.hpp"

constexpr float UPDATE_RATE = 0.15;
constexpr std::string GAME_TITLE = "Snake Game";
constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};

class SnakeController
{
public:
    SnakeController();
    bool has_lost();
    void play_snake();
    void game_over();
    void play_game();

private:
    enum class GameState
    {
        GAME,
        START,
        OVER
    };

    AssetHandler _textureHandler;
    SnakeModel _model;
    std::queue<Direction> _inputBuffer;
    sf::RenderWindow _window;
    void _add_move_to_buffer(Direction move);
    void _process_game_events();
    void _process_menu_events();
    void _draw_game();
    sf::Clock _timer;
    GameState _gamestate = GameState::GAME;
    std::optional<Direction> _get_next_direction();

};
