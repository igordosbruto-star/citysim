#include "Core/Systems/OverlaySystem.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/PollutionComponent.hpp"
#include <cstdint>

namespace CitySim {

void OverlaySystem::Update(float deltaTime) {
    if (!m_isOverlayActive) {
        return;
    }
    updateVertices();
}

void OverlaySystem::render(sf::RenderTarget& target) {
    if (!m_isOverlayActive) {
        return;
    }
    target.draw(m_vertices);
}

void OverlaySystem::setActiveOverlay(OverlayType type) {
    m_activeOverlay = type;
    m_isOverlayActive = true;
    updateVertices();
}

void OverlaySystem::clearOverlays() {
    m_isOverlayActive = false;
}

bool OverlaySystem::hasActiveOverlay() const {
    return m_isOverlayActive;
}

void OverlaySystem::setGridSize(const sf::Vector2u& size) {
    m_gridSize = size;
    m_vertices.resize(size.x * size.y * 6);
}

void OverlaySystem::updateVertices() {
    switch (m_activeOverlay) {
        case OverlayType::Power:
            updatePowerOverlay();
            break;
        case OverlayType::Water:
            updateWaterOverlay();
            break;
        case OverlayType::Pollution:
            updatePollutionOverlay();
            break;
    }
}

void OverlaySystem::updatePowerOverlay() {
    auto& registry = *GetRegistry();
    
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float coverage = 0.0f;
            
            auto view = registry.view<PowerGridComponent>();
            for (auto entity : view) {
                const auto& power = view.get<PowerGridComponent>(entity);
                if (power.hasPower) {
                    coverage = 1.0f;
                    break;
                }
            }
            
            sf::Color color = interpolateColor(coverage);
            size_t index = (y * m_gridSize.x + x) * 6;
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            // Primeiro triângulo
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            // Segundo triângulo
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 4].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 5].position = sf::Vector2f(worldX, worldY + 32);
            
            for (int i = 0; i < 6; ++i) {
                m_vertices[index + i].color = color;
            }
        }
    }
}

void OverlaySystem::updateWaterOverlay() {
    auto& registry = *GetRegistry();
    
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float coverage = 0.0f;
            
            auto view = registry.view<WaterGridComponent>();
            for (auto entity : view) {
                const auto& water = view.get<WaterGridComponent>(entity);
                if (water.hasWater) {
                    coverage = 1.0f;
                    break;
                }
            }
            
            sf::Color color = interpolateColor(coverage);
            size_t index = (y * m_gridSize.x + x) * 6;
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            // Primeiro triângulo
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            // Segundo triângulo
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 4].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 5].position = sf::Vector2f(worldX, worldY + 32);
            
            for (int i = 0; i < 6; ++i) {
                m_vertices[index + i].color = color;
            }
        }
    }
}

void OverlaySystem::updatePollutionOverlay() {
    auto& registry = *GetRegistry();
    
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float pollution = 0.0f;
            
            auto view = registry.view<PollutionComponent>();
            for (auto entity : view) {
                const auto& pollutionComp = view.get<PollutionComponent>(entity);
                pollution = std::max(pollution, pollutionComp.pollutionLevel);
            }
            
            float normalizedPollution = std::min(pollution / 100.0f, 1.0f);
            sf::Color color = interpolateColor(1.0f - normalizedPollution);
            
            size_t index = (y * m_gridSize.x + x) * 6;
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            // Primeiro triângulo
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            // Segundo triângulo
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 4].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 5].position = sf::Vector2f(worldX, worldY + 32);
            
            for (int i = 0; i < 6; ++i) {
                m_vertices[index + i].color = color;
            }
        }
    }
}

sf::Color OverlaySystem::interpolateColor(float value) const {
    sf::Color result;
    result.r = static_cast<uint8_t>((1.0f - value) * m_colorBad.r + value * m_colorGood.r);
    result.g = static_cast<uint8_t>((1.0f - value) * m_colorBad.g + value * m_colorGood.g);
    result.b = static_cast<uint8_t>((1.0f - value) * m_colorBad.b + value * m_colorGood.b);
    result.a = 128;
    return result;
}

} // namespace CitySim