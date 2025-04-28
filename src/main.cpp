#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <cmath>
#include "utility.hpp"
#include "player.hpp"

const float MOVEMENT_SPEED = 1.f;
const float GRID_SIZE = 10.f;


int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "Snake Game",
         sf::Style::Titlebar | sf::Style::Close
    );
    
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::View view(sf::FloatRect({0,0},{200, 200}));
    window.setView(view);

    Player player(MOVEMENT_SPEED); 
    InputBuffer input_buffer(2);
    sf::VertexArray grid = generate_grid(sf::Vector2u{20, 20}, GRID_SIZE);

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
                    input_buffer.add_move(LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                input_buffer.add_move(RIGHT);
                    break;
                case sf::Keyboard::Key::Up:
                    input_buffer.add_move(UP);
                    break;
                case sf::Keyboard::Key::Down:
                    input_buffer.add_move(DOWN);
                    break;
                }
            }
        }
        if (!input_buffer.empty() ) {
            Direction move_direction = player.get_move_direction();
            sf::Vector2f position = player.get_position();
            if (std::fmod(position.x, GRID_SIZE) < 0.01f && std::fmod(position.y, GRID_SIZE) < 0.01f) {
                player.set_move_direction(*input_buffer.get_next_direction());
            }
        }
        player.update();
        sf::Vector2f pos = player.get_position();
        window.clear(sf::Color::Black);
        window.draw(grid);
        player.draw(window);
        window.display();
    }
}