#include <cmath>
#include "utility.hpp"

sf::Vector2f rotate_vector(sf::Vector2f initialVector, sf::Angle rotation) {
    sf::Vector2f finalVector;
    float x = initialVector.x;
    float y = initialVector.y;
    finalVector.x = x*cos(rotation.asRadians()) - y*sin(rotation.asRadians());
    finalVector.y = x*sin(rotation.asRadians()) + y*cos(rotation.asRadians());

    return finalVector;
}

sf::Texture load_texture(std::string filename) {
    sf::Texture texture;
    if (texture.loadFromFile(ASSET_PATH_RELEASE / filename)) {
        return texture;
    } else if (texture.loadFromFile(ASSET_PATH_DEV / filename)) {
        return texture;
    }

    throw std::runtime_error("Asset not found: " + filename);
}