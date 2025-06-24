#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

const std::filesystem::path ASSET_PATH("assets");

class AssetHandler
{
    public:
        explicit AssetHandler(const std::vector<std::string>& initial_textures);
        AssetHandler();
        void load_texture(const std::string& texture_path);
        sf::Texture* get_texture(const std::string& texture_path);
        void load_font(const std::string& font_path);
        sf::Texture* get_font(const std::string& font_path);

    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> _fonts;
};