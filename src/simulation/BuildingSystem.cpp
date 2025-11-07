#include "simulation/BuildingSystem.hpp"
#include "simulation/BuildingComponent.hpp"
#include "simulation/GridComponent.hpp"
#include "Utils/Logger.hpp"

namespace CitySim {

BuildingSystem::BuildingSystem(Game& game)
    : m_game(game)
    , m_registry(game.getRegistry()) {
    LOG_INFO("BuildingSystem initialized");
}

bool BuildingSystem::demolish(const sf::Vector2i& position) {
    if (!isValidPosition(position)) {
        LOG_WARNING_F("Attempted to demolish at invalid position: (%d, %d)", position.x, position.y);
        return false;
    }

    entt::entity entity = findBuildingAt(position);
    if (entity != entt::null) {
        const auto* building = m_registry.try_get<BuildingComponent>(entity);
        
        if (!building) {
            LOG_WARNING_F("Entity at (%d, %d) has no BuildingComponent", position.x, position.y);
            return false;
        }
        
        if (!building->demolishable) {
            LOG_WARNING_F("Building at (%d, %d) cannot be demolished", position.x, position.y);
            return false;
        }
        
        // Remover a entidade e seus componentes
        m_registry.destroy(entity);
        LOG_INFO_F("Building demolished at position (%d, %d)", position.x, position.y);
        return true;
    }
    
    return false;
}

void BuildingSystem::update(float deltaTime) {
    // Atualizar estado dos edifícios
    auto view = m_registry.view<BuildingComponent>();
    for (auto entity : view) {
        auto& building = view.get<BuildingComponent>(entity);
        // TODO: Implementar atualização de estado dos edifícios
    }
}

bool BuildingSystem::isValidPosition(const sf::Vector2i& position) const {
    // TODO: Implementar verificação de limites do mapa e outras restrições
    return true;
}

entt::entity BuildingSystem::findBuildingAt(const sf::Vector2i& position) const {
    // TODO: Implementar busca por edifício na posição usando sistema de grid ou spatial hashing
    return entt::null;
}

} // namespace CitySim