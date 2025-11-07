#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace CitySim {

/**
 * @brief Representa um tile individual com suas propriedades
 */
class Tile {
public:
    /**
     * @brief Flags de colisão e comportamento do tile
     */
    enum class Flags {
        None = 0,
        Solid = 1 << 0,        // Tile sólido (colide)
        Water = 1 << 1,        // Água (pode ter barcos)
        Road = 1 << 2,         // Estrada (pode ter carros)
        Building = 1 << 3,     // Construção (pode ter estruturas)
        Terrain = 1 << 4       // Terreno natural
    };

    Tile() = default;
    
    /**
     * @brief Construtor com textura
     * @param texture Textura do tile
     * @param textureRect Área da textura a ser usada
     * @param flags Flags de comportamento
     */
    Tile(std::shared_ptr<sf::Texture> texture, const sf::IntRect& textureRect, Flags flags = Flags::None)
        : m_Texture(texture)
        , m_TextureRect(textureRect)
        , m_Flags(flags) {
    }

    // Getters
    std::shared_ptr<sf::Texture> GetTexture() const { return m_Texture; }
    const sf::IntRect& GetTextureRect() const { return m_TextureRect; }
    Flags GetFlags() const { return m_Flags; }

    // Setters
    void SetTexture(std::shared_ptr<sf::Texture> texture) { m_Texture = texture; }
    void SetTextureRect(const sf::IntRect& rect) { m_TextureRect = rect; }
    void SetFlags(Flags flags) { m_Flags = flags; }

    // Verificadores de flags
    bool IsSolid() const { return static_cast<bool>(static_cast<int>(m_Flags) & static_cast<int>(Flags::Solid)); }
    bool IsWater() const { return static_cast<bool>(static_cast<int>(m_Flags) & static_cast<int>(Flags::Water)); }
    bool IsRoad() const { return static_cast<bool>(static_cast<int>(m_Flags) & static_cast<int>(Flags::Road)); }
    bool IsBuilding() const { return static_cast<bool>(static_cast<int>(m_Flags) & static_cast<int>(Flags::Building)); }
    bool IsTerrain() const { return static_cast<bool>(static_cast<int>(m_Flags) & static_cast<int>(Flags::Terrain)); }

private:
    std::shared_ptr<sf::Texture> m_Texture;  ///< Textura do tile
    sf::IntRect m_TextureRect;               ///< Área da textura a ser usada
    Flags m_Flags{Flags::None};              ///< Flags de comportamento
};

// Operadores de bitwise para flags
inline Tile::Flags operator|(Tile::Flags a, Tile::Flags b) {
    return static_cast<Tile::Flags>(static_cast<int>(a) | static_cast<int>(b));
}

inline Tile::Flags operator&(Tile::Flags a, Tile::Flags b) {
    return static_cast<Tile::Flags>(static_cast<int>(a) & static_cast<int>(b));
}

// Operadores de comparação
inline bool operator==(Tile::Flags a, Tile::Flags b) {
    return static_cast<int>(a) == static_cast<int>(b);
}

inline bool operator!=(Tile::Flags a, Tile::Flags b) {
    return static_cast<int>(a) != static_cast<int>(b);
}

inline bool operator!(Tile::Flags a) {
    return static_cast<int>(a) == 0;
}

inline Tile::Flags operator~(Tile::Flags a) {
    return static_cast<Tile::Flags>(~static_cast<int>(a));
}

} // namespace CitySim