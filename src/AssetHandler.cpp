#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "AssetHandler.hpp"

AssetHandler::AssetHandler(const std::vector<std::string>& initialTextures )
{
    for (const auto& texture : initialTextures)
{
        loadTexture(texture);
    }
}

AssetHandler::AssetHandler() = default;

void AssetHandler::loadTexture(const std::string& texturePath)
{
    if (sf::Texture texture; texture.loadFromFile(ASSET_PATH / texturePath)) {
        m_loadedTextures[texturePath] = texture;
    } else
    {
        throw std::runtime_error("Asset not found: " + texturePath);
    }
}

sf::Texture* AssetHandler::getTexture(const std::string& texturePath)
{
    if (!m_loadedTextures.contains(texturePath)) loadTexture(texturePath);

    return &m_loadedTextures.at(texturePath);
}

void AssetHandler::loadFont(const std::string& fontPath)
{
    if (sf::Font font; font.openFromFile(ASSET_PATH / fontPath)) {
        m_loadedFonts[fontPath] = font;
    } else
    {
        throw std::runtime_error("Asset not found: " + fontPath);
    }
}

sf::Font* AssetHandler::getFont(const std::string& fontPath)
{
    if (!m_loadedTextures.contains(fontPath)) loadFont(fontPath);

    return &m_loadedFonts.at(fontPath);
}

