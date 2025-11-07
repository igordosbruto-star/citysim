#pragma once

#include <entt/entity/registry.hpp>
#include <SFML/System/Vector2.hpp>

#include "Core/Game.hpp"

namespace CitySim {

class BuildingSystem {
public:
    explicit BuildingSystem(Game& game);
    
    // Demolição
    bool demolish(const sf::Vector2i& position);
    
    // Atualizações
    void update(float deltaTime);
    
private:
    Game& m_game;
    entt::registry& m_registry;
    
    // Funções auxiliares
    bool isValidPosition(const sf::Vector2i& position) const;
    entt::entity findBuildingAt(const sf::Vector2i& position) const;
};

} // namespace CitySim