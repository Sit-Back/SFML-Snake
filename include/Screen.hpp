#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AssetHandler.hpp"
#include "Button.hpp"

class Screen final : public sf::Drawable {
    public:
        Screen(AssetHandler* assetHandler, sf::Texture* logo, std::string subtext);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void addButton(Button button);
        void setSubtext(std::string newText);

        std::vector<Button>* getButtons();
    private:
        sf::Sprite m_logo;
        sf::Text m_subtext;
        std::vector<Button> m_buttons;
};