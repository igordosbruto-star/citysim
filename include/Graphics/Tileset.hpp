#pragma once

#include "Graphics/Tile.hpp"
#include <vector>
#include <string>

namespace CitySim {

/**
 * @brief Representa um conjunto de tiles que podem ser usados em um tilemap
 */
class Tileset {
public:
    Tileset() = default;

    /**
     * @brief Construtor com textura e tamanho dos tiles
     * @param texture Textura contendo todos os tiles
     * @param tileWidth Largura de cada tile em pixels
     * @param tileHeight Altura de cada tile em pixels
     */
    Tileset(std::shared_ptr<sf::Texture> texture, int tileWidth, int tileHeight);

    /**
     * @brief Adiciona um novo tipo de tile ao tileset
     * @param textureRect Área da textura para este tile
     * @param flags Flags de comportamento do tile
     * @return ID do tile adicionado
     */
    size_t AddTile(const sf::IntRect& textureRect, Tile::Flags flags = Tile::Flags::None);

    /**
     * @brief Obtém um tile pelo seu ID
     * @param id ID do tile
     * @return Referência para o tile
     * @throws std::out_of_range se o ID for inválido
     */
    const Tile& GetTile(size_t id) const;

    /**
     * @brief Obtém as dimensões dos tiles neste tileset
     * @return Par com largura e altura dos tiles
     */
    std::pair<int, int> GetTileSize() const { return {m_TileWidth, m_TileHeight}; }

    /**
     * @brief Obtém o número de tiles no tileset
     * @return Quantidade de tiles
     */
    size_t GetTileCount() const { return m_Tiles.size(); }

private:
    std::shared_ptr<sf::Texture> m_Texture;      ///< Textura contendo todos os tiles
    std::vector<Tile> m_Tiles;                   ///< Lista de tiles disponíveis
    int m_TileWidth{0};                          ///< Largura de cada tile em pixels
    int m_TileHeight{0};                         ///< Altura de cada tile em pixels
};

} // namespace CitySim