#pragma once

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <SFML/Graphics.hpp>

const std::filesystem::path ASSET_PATH("assets");

class AssetHandler
{
    public:
        explicit AssetHandler(const std::vector<std::string>& initialTextures);
        AssetHandler();
        void loadTexture(const std::string& texturePath);
        sf::Texture* getTexture(const std::string& texturePath);
        void loadFont(const std::string& fontPath);
        sf::Font* getFont(const std::string& fontPath);

    private:
        std::unordered_map<std::string, sf::Texture> m_loadedTextures;
        std::unordered_map<std::string, sf::Font> m_loadedFonts;
};