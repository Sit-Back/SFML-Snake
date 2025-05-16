#include <cmath>
#include "utility.hpp"

sf::Vector2f rotate_vector(sf::Vector2f initialVector, sf::Angle rotation) {
    sf::Vector2f finalVector;
    float x = initialVector.x;
    float y = initialVector.y;
    finalVector.x = x*std::cos(rotation.asRadians()) - y*std::sin(rotation.asRadians());
    finalVector.y = x*std::sin(rotation.asRadians()) + y*std::cos(rotation.asRadians());

    return finalVector;
}

sf::Texture load_texture(const std::string& filename) {
    if (sf::Texture texture; texture.loadFromFile(ASSET_PATH / filename)) {
        return texture;
    }

    throw std::runtime_error("Asset not found: " + filename);
}