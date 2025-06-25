#include "Button.hpp"
#include <SFML/Graphics/Font.hpp>

Button::Button
(
    sf::Vector2f position,
    std::string text,
    sf::Font font,
   std::function<void()> function)
: m_function(function), m_text(font)
{
    m_text.setString(text);
    m_text.setPosition(position);
}

void Button::handleMouseClick(sf::Vector2f mousePos) const
{
    if (m_text.getLocalBounds().contains(mousePos)) {
        m_function();
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}
