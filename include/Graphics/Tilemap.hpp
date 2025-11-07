#pragma once

#include "Graphics/Tileset.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

namespace CitySimulator {

/**
 * @brief Representa um mapa de tiles 2D que pode ser renderizado
 */
class Tilemap : public sf::Drawable, public sf::Transformable {
public:
    /**
     * @brief Construtor padrão
     */
    Tilemap() = default;

    /**
     * @brief Inicializa o tilemap com dimensões específicas
     * @param width Largura em tiles
     * @param height Altura em tiles
     * @param tileset Tileset a ser usado
     * @return true se a inicialização foi bem sucedida
     */
    bool Create(unsigned int width, unsigned int height, const Tileset& tileset);

    /**
     * @brief Define um tile em uma posição específica
     * @param x Coordenada X em tiles
     * @param y Coordenada Y em tiles
     * @param tileId ID do tile no tileset
     */
    void SetTile(unsigned int x, unsigned int y, size_t tileId);

    /**
     * @brief Obtém o ID do tile em uma posição específica
     * @param x Coordenada X em tiles
     * @param y Coordenada Y em tiles
     * @return ID do tile ou -1 se a posição for inválida
     */
    int GetTile(unsigned int x, unsigned int y) const;

    /**
     * @brief Verifica se uma posição está dentro dos limites do mapa
     * @param x Coordenada X em tiles
     * @param y Coordenada Y em tiles
     * @return true se a posição for válida
     */
    bool IsValidPosition(unsigned int x, unsigned int y) const;

    /**
     * @brief Obtém as dimensões do mapa
     * @return Par com largura e altura em tiles
     */
    std::pair<unsigned int, unsigned int> GetSize() const { return {m_Width, m_Height}; }

private:
    /**
     * @brief Atualiza os vértices de um tile específico
     * @param x Coordenada X em tiles
     * @param y Coordenada Y em tiles
     */
    void UpdateTileVertices(unsigned int x, unsigned int y);

    /**
     * @brief Implementação da interface Drawable
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_Vertices;         ///< Array de vértices para renderização
    std::vector<size_t> m_TileIds;      ///< IDs dos tiles em cada posição
    const Tileset* m_Tileset{nullptr};  ///< Tileset usado pelo mapa
    unsigned int m_Width{0};            ///< Largura do mapa em tiles
    unsigned int m_Height{0};           ///< Altura do mapa em tiles
};

} // namespace CitySimulator