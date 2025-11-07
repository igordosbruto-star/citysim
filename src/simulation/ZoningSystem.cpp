#include "simulation/ZoningSystem.hpp"
#include "Utils/Logger.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace CitySim {

ZoningSystem::ZoningSystem(Game& game)
    : m_game(game)
    , m_registry(game.getRegistry()) {
    LOG_INFO("ZoningSystem initialized");
}

bool ZoningSystem::setZone(const sf::Vector2i& position, ZoneType type) {
    if (!isValidPosition(position)) {
        LOG_WARNING_F("Attempted to set zone at invalid position: (%d, %d)", position.x, position.y);
        return false;
    }

    // Se já existe uma zona na posição, remova-a primeiro
    entt::entity existingZone = findZoneEntityAt(position);
    if (existingZone != entt::null) {
        destroyZoneEntity(existingZone);
    }

    // Criar nova entidade de zona se o tipo não for None
    if (type != ZoneType::None) {
        createZoneEntity(position, type);
        const char* zoneTypeStr = type == ZoneType::Residential ? "residential" : 
                                  type == ZoneType::Commercial ? "commercial" : "industrial";
        LOG_INFO_F("Created %s zone at position (%d, %d)", zoneTypeStr, position.x, position.y);
    }

    return true;
}

bool ZoningSystem::removeZone(const sf::Vector2i& position) {
    entt::entity entity = findZoneEntityAt(position);
    if (entity != entt::null) {
        destroyZoneEntity(entity);
        LOG_INFO_F("Removed zone at position (%d, %d)", position.x, position.y);
        return true;
    }
    return false;
}

ZoneType ZoningSystem::getZoneAt(const sf::Vector2i& position) const {
    entt::entity entity = findZoneEntityAt(position);
    if (entity != entt::null) {
        const auto& zone = m_registry.get<ZoneComponent>(entity);
        return zone.type;
    }
    return ZoneType::None;
}

void ZoningSystem::update(float deltaTime) {
    // Atualizar satisfação e desenvolvimento das zonas
    auto view = m_registry.view<ZoneComponent>();
    for (auto entity : view) {
        auto& zone = view.get<ZoneComponent>(entity);
        // TODO: Implementar lógica de atualização baseada em recursos e condições
    }
}

bool ZoningSystem::isValidPosition(const sf::Vector2i& position) const {
    // TODO: Implementar verificação de limites do mapa e outras restrições
    return true;
}

entt::entity ZoningSystem::createZoneEntity(const sf::Vector2i& position, ZoneType type) {
    entt::entity entity = m_registry.create();
    m_registry.emplace<ZoneComponent>(entity, type);
    // TODO: Adicionar outros componentes necessários (Transform, Renderable, etc.)
    return entity;
}

void ZoningSystem::destroyZoneEntity(entt::entity entity) {
    m_registry.destroy(entity);
}

entt::entity ZoningSystem::findZoneEntityAt(const sf::Vector2i& position) const {
    // TODO: Implementar busca por zona na posição usando um sistema de grid ou spatial hashing
    return entt::null;
}

} // namespace CitySim