#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

const std::filesystem::path ASSET_PATH("assets");

class TextureHandler
{
    public:
        explicit TextureHandler(const std::vector<std::string>& initial_textures);
        TextureHandler();
        void load_texture(const std::string& texture_path);
        sf::Texture* get_texture(const std::string& texture_path);
    private:
        std::unordered_map<std::string, sf::Texture> _textures;
};