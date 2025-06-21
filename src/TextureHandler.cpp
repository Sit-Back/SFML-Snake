#include <map>
#include <SFML/Graphics.hpp>
#include "TextureHandler.hpp"

#include <iostream>

TextureHandler::TextureHandler(const std::vector<std::string>& initial_textures )
{
    for (const auto& texture : initial_textures)
{
        load_texture(texture);
    }
}

TextureHandler::TextureHandler() = default;

void TextureHandler::load_texture(std::string texture_path)
{
    if (sf::Texture texture; texture.loadFromFile(ASSET_PATH / texture_path)) {
        _textures[texture_path] = texture;
    } else
    {
        throw std::runtime_error("Asset not found: " + texture_path);
    }
}

sf::Texture* TextureHandler::get_texture(std::string texture_path)
{
    if (!_textures.contains(texture_path)) load_texture(texture_path);

    return &_textures.at(texture_path);
}
