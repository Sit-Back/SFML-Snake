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