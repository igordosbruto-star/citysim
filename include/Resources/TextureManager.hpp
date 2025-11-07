#pragma once

#include "Resources/ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace CitySim {

/**
 * @brief Gerenciador especializado para texturas SFML
 */
class TextureManager : public ResourceManager<sf::Texture> {
protected:
    bool LoadFromFile(sf::Texture& texture, const std::string& path) override {
        return texture.loadFromFile(path);
    }
};

} // namespace CitySim