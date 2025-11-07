#include "simulation/BuildingSystem.hpp"
#include "simulation/BuildingComponent.hpp"
#include "simulation/GridComponent.hpp"
#include "Core/Logger.hpp"

namespace CitySim {

BuildingSystem::BuildingSystem(Game& game)
    : m_game(game)
    , m_registry(game.getRegistry()) {
    Logger::info("BuildingSystem initialized");
}

bool BuildingSystem::demolish(const sf::Vector2i& position) {
    if (!isValidPosition(position)) {
        Logger::warn("Attempted to demolish at invalid position: ({}, {})", position.x, position.y);
        return false;
    }

    entt::entity entity = findBuildingAt(position);
    if (entity != entt::null) {
        const auto* building = m_registry.try_get<BuildingComponent>(entity);
        
        if (!building) {
            Logger::warn("Entity at ({}, {}) has no BuildingComponent", position.x, position.y);
            return false;
        }
        
        if (!building->demolishable) {
            Logger::warn("Building at ({}, {}) cannot be demolished", position.x, position.y);
            return false;
        }
        
        // Remover a entidade e seus componentes
        m_registry.destroy(entity);
        Logger::info("Building demolished at position ({}, {})", position.x, position.y);
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