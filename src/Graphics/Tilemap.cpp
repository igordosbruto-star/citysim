#include "Graphics/Tilemap.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace CitySimulator {

bool Tilemap::Create(unsigned int width, unsigned int height, const Tileset& tileset) {
    m_Width = width;
    m_Height = height;
    m_Tileset = &tileset;

    // Cada tile será representado por 2 triângulos (6 vértices)
    m_Vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_Vertices.resize(width * height * 6);

    // Inicializa o array de IDs com -1 (tile vazio)
    m_TileIds.resize(width * height, static_cast<size_t>(-1));

    // Cria os vértices para cada tile
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            UpdateTileVertices(x, y);
        }
    }

    return true;
}

void Tilemap::SetTile(unsigned int x, unsigned int y, size_t tileId) {
    if (!IsValidPosition(x, y)) {
        return;
    }

    m_TileIds[y * m_Width + x] = tileId;
    UpdateTileVertices(x, y);
}

int Tilemap::GetTile(unsigned int x, unsigned int y) const {
    if (!IsValidPosition(x, y)) {
        return -1;
    }

    return static_cast<int>(m_TileIds[y * m_Width + x]);
}

bool Tilemap::IsValidPosition(unsigned int x, unsigned int y) const {
    return x < m_Width && y < m_Height;
}

void Tilemap::UpdateTileVertices(unsigned int x, unsigned int y) {
    // Obtém o ID do tile nesta posição
    size_t tileId = m_TileIds[y * m_Width + x];

    // Obtém um ponteiro para os 6 vértices do tile (2 triângulos)
    size_t vertexOffset = (y * m_Width + x) * 6;
    sf::Vertex* quad = &m_Vertices[vertexOffset];

    if (tileId == static_cast<size_t>(-1)) {
        // Tile vazio - torna os vértices transparentes
        quad[0].color = sf::Color::Transparent;
        quad[1].color = sf::Color::Transparent;
        quad[2].color = sf::Color::Transparent;
        quad[3].color = sf::Color::Transparent;
        return;
    }

    // Obtém o tile e suas dimensões
    const Tile& tile = m_Tileset->GetTile(tileId);
    auto [tileWidth, tileHeight] = m_Tileset->GetTileSize();
    const sf::IntRect& textureRect = tile.GetTextureRect();

    // Define as posições dos vértices (dois triângulos)
    // Triângulo A: top-left, top-right, bottom-right
    quad[0].position = sf::Vector2f(x * tileWidth, y * tileHeight);
    quad[1].position = sf::Vector2f((x + 1) * tileWidth, y * tileHeight);
    quad[2].position = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
    // Triângulo B: bottom-right, bottom-left, top-left
    quad[3].position = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
    quad[4].position = sf::Vector2f(x * tileWidth, (y + 1) * tileHeight);
    quad[5].position = sf::Vector2f(x * tileWidth, y * tileHeight);

    // Coordenadas de textura correspondentes aos vértices (dois triângulos)
    quad[0].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x), static_cast<float>(textureRect.position.y));
    quad[1].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x + textureRect.size.x), static_cast<float>(textureRect.position.y));
    quad[2].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x + textureRect.size.x), static_cast<float>(textureRect.position.y + textureRect.size.y));
    quad[3].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x + textureRect.size.x), static_cast<float>(textureRect.position.y + textureRect.size.y));
    quad[4].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x), static_cast<float>(textureRect.position.y + textureRect.size.y));
    quad[5].texCoords = sf::Vector2f(static_cast<float>(textureRect.position.x), static_cast<float>(textureRect.position.y));

    // Restaura a cor para branco (totalmente visível)
    for (int i = 0; i < 6; ++i) {
        quad[i].color = sf::Color::White;
    }
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!m_Tileset) {
        return;
    }

    // Aplica a transformação
    states.transform *= getTransform();

    // Define a textura
    states.texture = m_Tileset->GetTile(0).GetTexture().get();

    // Desenha o vertex array
    target.draw(m_Vertices, states);
}

} // namespace CitySimulator