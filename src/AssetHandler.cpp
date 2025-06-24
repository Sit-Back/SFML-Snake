#include <map>
#include <SFML/Graphics.hpp>
#include "AssetHandler.hpp"

#include <iostream>

AssetHandler::AssetHandler(const std::vector<std::string>& initial_textures )
{
    for (const auto& texture : initial_textures)
{
        load_texture(texture);
    }
}

AssetHandler::AssetHandler() = default;

void AssetHandler::load_texture(const std::string& texture_path)
{
    if (sf::Texture texture; texture.loadFromFile(ASSET_PATH / texture_path)) {
        _textures[texture_path] = texture;
    } else
    {
        throw std::runtime_error("Asset not found: " + texture_path);
    }
}

sf::Texture* AssetHandler::get_texture(const std::string& texture_path)
{
    if (!_textures.contains(texture_path)) load_texture(texture_path);

    return &_textures.at(texture_path);
}

void AssetHandler::load_font(const std::string& font_path)
{
    if (sf::Font font; font.openFromFile(ASSET_PATH / font_path)) {
        _fonts[font_path] = font;
    } else
    {
        throw std::runtime_error("Asset not found: " + font_path);
    }
}

sf::Texture* AssetHandler::get_font(const std::string& font_path)
{
    if (!_textures.contains(font_path)) load_texture(font_path);

    return &_textures.at(font_path);
}

