#include <SFML/Graphics.hpp>
#include "SnakeModel.hpp"
#include "player.hpp"
#include "utility.hpp"

constexpr float UPDATE_RATE = 0.15f;
constexpr float GRID_SIZE = 800.0/15.0;

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

    SnakeModel game_grid = SnakeModel(sf::Vector2u{15, 15}, GRID_SIZE);

    sf::Texture eyeTexture = load_texture("eyes.png");
    eyeTexture.setSmooth(true);
    Player player(game_grid, eyeTexture);

    sf::Clock timer;
    while (window.isOpen())
    {
        while (const  std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (key_pressed->code)
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
                default: ;
                }
            }
        }

        if (timer.getElapsedTime().asSeconds() > UPDATE_RATE) {
            game_grid.create_fruit();
            player.update();
            timer.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(game_grid.get_vertices());
        player.draw(window);
        game_grid.draw_fruit(window);
        window.display();
    }
}