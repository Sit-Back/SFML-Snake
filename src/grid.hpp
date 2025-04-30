#pragma once

#include <SFML/Graphics.hpp>

const float GRID_SIZE = 10.f;

sf::VertexArray generate_grid(sf::Vector2u dimensions, float size);