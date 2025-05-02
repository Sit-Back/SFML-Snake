#include <cmath>
#include "utility.hpp"

sf::Vector2f rotate_vector(sf::Vector2f initialVector, float radiansOfRotation) {
    sf::Vector2f finalVector;
    float x = initialVector.x;
    float y = initialVector.y;
    finalVector.x = x*cos(radiansOfRotation) - y*sin(radiansOfRotation);
    finalVector.y = x*sin(radiansOfRotation) + y*cos(radiansOfRotation);

    return finalVector;
}