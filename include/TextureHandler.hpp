#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class TextureHandler
{
    public:
        std::map<std::string, sf::Texture> _textures;
        void load_texture(const std::string& texture_path);
        sf::Texture* get_texture(const std::string& texture_path);
};