#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <cmath>
#include "grid.hpp"
#include "player.hpp"
#include "utility.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "Snake Game",
         sf::Style::Titlebar | sf::Style::Close
    );
    
    window.setFramerateLimit(2);
    window.setKeyRepeatEnabled(false);

    sf::View gridView(sf::FloatRect({0,0},{200, 200}));
    window.setView(gridView);

    Grid game_grid = Grid(sf::Vector2u{20, 20}, GRID_SIZE);
    Player player(game_grid, GRID_SIZE); 

    while (window.isOpen())
    {
        while (const  std::optional<sf::Event> event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keypressed_data = event->getIf<sf::Event::KeyPressed>()) {
                sf::Keyboard::Key keycode = keypressed_data->code;
                
                switch (keycode)
                {
                case sf::Keyboard::Key::Left:
                    player.add_move_to_buffer(MovementDirection::LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                    player.add_move_to_buffer(MovementDirection::RIGHT);
                    break;
                case sf::Keyboard::Key::Up:
                    player.add_move_to_buffer(MovementDirection::UP);
                    break;
                case sf::Keyboard::Key::Down:
                    player.add_move_to_buffer(MovementDirection::DOWN);
                    break;
                }
            }
        }

        player.update();
        window.clear(sf::Color::Black);
        window.draw(game_grid.get_verticies());
        player.draw(window);
        window.display();
    }
}