#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>

const std::filesystem::path ASSET_PATH("assets");

sf::Texture load_texture(const std::string& filename);

sf::Vector2f rotate_vector(sf::Vector2f initialVector, sf::Angle angleOfRotation);