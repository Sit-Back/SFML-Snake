#pragma once

#include <map>
#include <SFML/Graphics.hpp>

const std::filesystem::path ASSET_PATH("assets");

class TextureHandler
{
    public:
        explicit TextureHandler(const std::vector<std::string>& initial_textures);
        TextureHandler();
        void load_texture(std::string texture_path);
        sf::Texture* get_texture(std::string texture_path);
    private:
        std::map<std::string, sf::Texture> _textures;
};