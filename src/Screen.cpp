#include "Screen.hpp"
#include "AssetHandler.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

Screen::Screen(AssetHandler* assetHandler, sf::Texture* logo, std::string subtext) :
    m_logo(*logo),
    m_subtext(*assetHandler->getFont("ui-font.ttf"), subtext)
{

}
void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_logo);
    target.draw(m_subtext);

    for (auto button : m_buttons) {
        target.draw(button);
    }
}

void Screen::addButton(Button button) {
    m_buttons.push_back(button);
}