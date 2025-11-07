#include "Graphics/Tileset.hpp"
#include <stdexcept>

namespace CitySim {

Tileset::Tileset(std::shared_ptr<sf::Texture> texture, int tileWidth, int tileHeight)
    : m_Texture(texture)
    , m_TileWidth(tileWidth)
    , m_TileHeight(tileHeight) {
}

size_t Tileset::AddTile(const sf::IntRect& textureRect, Tile::Flags flags) {
    m_Tiles.emplace_back(m_Texture, textureRect, flags);
    return m_Tiles.size() - 1;
}

const Tile& Tileset::GetTile(size_t id) const {
    if (id >= m_Tiles.size()) {
        throw std::out_of_range("Invalid tile ID");
    }
    return m_Tiles[id];
}

} // namespace CitySim