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
    void play_game();

private:
    SnakeModel _model;
    std::queue<Direction> _inputBuffer;
    sf::RenderWindow _window;
    void _add_move_to_buffer(Direction move);
    void _process_events();
    void _draw_game();
    std::optional<Direction> _get_next_direction();
};
