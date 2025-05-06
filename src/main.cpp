#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <cmath>
#include "grid.hpp"
#include "player.hpp"
#include "utility.hpp"
#include "fruit.hpp"

const float UPDATE_RATE = 0.15f;
const float GRID_SIZE = 800.0/15.0;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "Snake Game",
         sf::Style::Titlebar | sf::Style::Close
    );
    
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    sf::View gridView(sf::FloatRect({0,0},{800, 800}));
    window.setView(gridView);

    Grid game_grid = Grid(sf::Vector2u{15, 15}, GRID_SIZE);
    Player player(game_grid); 
    sf::Clock timer;

    while (window.isOpen())
    {
        while (const  std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keypressed_data = event->getIf<sf::Event::KeyPressed>()) {
                sf::Keyboard::Key keycode = keypressed_data->code;
                
                switch (keycode)
                {
                case sf::Keyboard::Key::Left:
                    player.add_move_to_buffer(Direction::LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                    player.add_move_to_buffer(Direction::RIGHT);
                    break;
                case sf::Keyboard::Key::Up:
                    player.add_move_to_buffer(Direction::UP);
                    break;
                case sf::Keyboard::Key::Down:
                    player.add_move_to_buffer(Direction::DOWN);
                    break;
                }
            }
        }

        if (timer.getElapsedTime().asSeconds() > UPDATE_RATE) {
            player.update();
            timer.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(game_grid.get_verticies());
        player.draw(window);
        window.display();
    }
}