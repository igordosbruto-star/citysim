#include "Core/Systems/OverlaySystem.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/PollutionComponent.hpp"
#include <cstdint>

namespace CitySim {

OverlaySystem::OverlaySystem(entt::registry& registry)
    : m_registry(registry)
    , m_activeOverlay(OverlayType::Power)
    , m_isOverlayActive(false)
    , m_gridSize(1, 1)
    , m_vertices()  // CORREÇÃO: Inicialize sem parâmetro
    , m_colorGood(0, 255, 0, 128)   // Verde semi-transparente
    , m_colorBad(255, 0, 0, 128)    // Vermelho semi-transparente
{
    // CORREÇÃO: Defina o tipo primitivo depois da construção
    
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
}

void OverlaySystem::update(float dt) {
    if (!m_isOverlayActive) {
        return;
    }

    // Atualiza os vértices do overlay ativo
    updateVertices();
}

void OverlaySystem::render(sf::RenderTarget& target) {
    if (!m_isOverlayActive) {
        return;
    }

    // Renderiza os vértices do overlay
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
    
    // Redimensiona o array de vértices para cobrir o grid
    m_vertices.resize(size.x * size.y * 6);  // 4 vértices por quadrado
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
    // Percorre cada célula do grid
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float coverage = 0.0f;
            
            // Verifica se tem energia nesta posição
            auto view = m_registry.view<PowerGridComponent>();
            for (auto entity : view) {
                const auto& power = view.get<PowerGridComponent>(entity);
                if (power.hasPower) {
                    // TODO: Verificar posição real da entidade quando tivermos o sistema de grid
                    coverage = 1.0f;
                    break;
                }
            }
            
            // Define a cor do quadrado baseado na cobertura
            sf::Color color = interpolateColor(coverage);
            
            // Índice do primeiro vértice do quadrado atual
            size_t index = (y * m_gridSize.x + x) * 4;
            
            // Posição do quadrado no mundo
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            // Define os 4 vértices do quadrado
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY + 32);
            
            // Define a cor de cada vértice
            m_vertices[index + 0].color = color;
            m_vertices[index + 1].color = color;
            m_vertices[index + 2].color = color;
            m_vertices[index + 3].color = color;
        }
    }
}

void OverlaySystem::updateWaterOverlay() {
    // Similar ao overlay de energia, mas para água
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float coverage = 0.0f;
            
            auto view = m_registry.view<WaterGridComponent>();
            for (auto entity : view) {
                const auto& water = view.get<WaterGridComponent>(entity);
                if (water.hasWater) {
                    coverage = 1.0f;
                    break;
                }
            }
            
            sf::Color color = interpolateColor(coverage);
            size_t index = (y * m_gridSize.x + x) * 4;
            
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY + 32);
            
            m_vertices[index + 0].color = color;
            m_vertices[index + 1].color = color;
            m_vertices[index + 2].color = color;
            m_vertices[index + 3].color = color;
        }
    }
}

void OverlaySystem::updatePollutionOverlay() {
    // Overlay para poluição
    for (unsigned int y = 0; y < m_gridSize.y; y++) {
        for (unsigned int x = 0; x < m_gridSize.x; x++) {
            float pollution = 0.0f;
            
            // TODO: Quando tivermos o sistema de grid espacial,
            // usar a posição real para verificar a poluição
            sf::Vector2f position(x * 32.0f, y * 32.0f);
            
            auto view = m_registry.view<PollutionComponent>();
            for (auto entity : view) {
                const auto& pollutionComp = view.get<PollutionComponent>(entity);
                pollution = std::max(pollution, pollutionComp.pollutionLevel);
            }
            
            // Normaliza o nível de poluição para 0-1
            float normalizedPollution = std::min(pollution / 100.0f, 1.0f);
            sf::Color color = interpolateColor(1.0f - normalizedPollution); // Inverte para vermelho = mais poluído
            
            size_t index = (y * m_gridSize.x + x) * 4;
            float worldX = x * 32.0f;
            float worldY = y * 32.0f;
            
            m_vertices[index + 0].position = sf::Vector2f(worldX, worldY);
            m_vertices[index + 1].position = sf::Vector2f(worldX + 32, worldY);
            m_vertices[index + 2].position = sf::Vector2f(worldX + 32, worldY + 32);
            m_vertices[index + 3].position = sf::Vector2f(worldX, worldY + 32);
            
            m_vertices[index + 0].color = color;
            m_vertices[index + 1].color = color;
            m_vertices[index + 2].color = color;
            m_vertices[index + 3].color = color;
        }
    }
}

sf::Color OverlaySystem::interpolateColor(float value) const {
    // Interpola entre vermelho (0.0) e verde (1.0)
    sf::Color result;
    result.r = static_cast<uint8_t>((1.0f - value) * m_colorBad.r + value * m_colorGood.r);
    result.g = static_cast<uint8_t>((1.0f - value) * m_colorBad.g + value * m_colorGood.g);
    result.b = static_cast<uint8_t>((1.0f - value) * m_colorBad.b + value * m_colorGood.b);
    result.a = 128;  // 50% transparência
    return result;
}

} // namespace CitySim