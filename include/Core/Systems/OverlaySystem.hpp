#pragma once

#include "ECS/System.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace CitySim {

enum class OverlayType {
    Power,
    Water,
    Pollution
};

class OverlaySystem : public System {
public:
    OverlaySystem() = default;
    
    bool Init(entt::registry& registry) override {
        System::Init(registry);
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        return true;
    }
    
    void Update(float deltaTime) override;
    
    std::string GetName() const override { return "OverlaySystem"; }

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
    OverlayType m_activeOverlay = OverlayType::Power;
    bool m_isOverlayActive = false;
    
    sf::Vector2u m_gridSize{1, 1};
    sf::VertexArray m_vertices;
    sf::Color m_colorGood{0, 255, 0, 128};
    sf::Color m_colorBad{255, 0, 0, 128};
    
    void updateVertices();
    void updatePowerOverlay();
    void updateWaterOverlay();
    void updatePollutionOverlay();
    sf::Color interpolateColor(float value) const;
};

} // namespace CitySim