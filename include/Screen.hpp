#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Button.hpp"

class Screen final : sf::Drawable {
    public:
        Screen(sf::Texture* logo, std::string subtext, std::vector<Button> buttons);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        const sf::Sprite m_logo;
        const sf::Text m_subtext;
        const std::vector<Button> m_buttons;
};