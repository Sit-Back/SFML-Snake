#pragma once
#include <queue>
#include "SnakeModel.hpp"

constexpr float UPDATE_RATE = 0.15f;
constexpr std::string GAME_TITLE = "Snake Game";
constexpr sf::Vector2u WINDOW_DIMENSIONS = {800, 800};

class SnakeController
{
public:
    SnakeController();
    void _draw_game();
    void play_game();

private:
    SnakeModel _model;
    std::queue<Direction> _inputBuffer;
    sf::RenderWindow _window;
    void _add_move_to_buffer(Direction move);
    void _process_events();
    std::optional<Direction> _get_next_direction();
};
