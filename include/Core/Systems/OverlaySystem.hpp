#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <vector>
#include <memory>

namespace CitySimulator {

enum class OverlayType {
    Power,
    Water,
    Pollution
};

class OverlaySystem {
public:
    explicit OverlaySystem(entt::registry& registry);

    // Atualiza o overlay
    void update(float dt);

    // Renderiza o overlay ativo
    void render(sf::RenderTarget& target);

    // Define o tipo de overlay ativo
    void setActiveOverlay(OverlayType type);

    // Desativa todos os overlays
    void clearOverlays();

    // Retorna verdadeiro se algum overlay está ativo
    bool hasActiveOverlay() const;

    // Define o tamanho do grid do overlay
    void setGridSize(const sf::Vector2u& size);

private:
    entt::registry& m_registry;
    OverlayType m_activeOverlay;
    bool m_isOverlayActive;
    
    sf::Vector2u m_gridSize;
    sf::RenderTexture m_overlayTexture;
    sf::VertexArray m_vertices;
    sf::Color m_colorGood;
    sf::Color m_colorBad;
    
    // Atualiza os vértices do overlay
    void updateVertices();
    
    // Atualiza o overlay de energia
    void updatePowerOverlay();
    
    // Atualiza o overlay de água
    void updateWaterOverlay();
    
    // Atualiza o overlay de poluição
    void updatePollutionOverlay();
    
    // Interpola cor baseado no valor (0.0f a 1.0f)
    sf::Color interpolateColor(float value) const;
};

} // namespace CitySimulator