#pragma once

#include <entt/entity/registry.hpp>
#include <SFML/System/Vector2.hpp>

#include "ZoneComponent.hpp"
#include "Core/Game.hpp"

namespace CitySim {

class ZoningSystem {
public:
    explicit ZoningSystem(Game& game);
    
    // Operações de zoneamento
    bool setZone(const sf::Vector2i& position, ZoneType type);
    bool removeZone(const sf::Vector2i& position);
    ZoneType getZoneAt(const sf::Vector2i& position) const;
    
    // Atualização do sistema
    void update(float deltaTime);
    
private:
    Game& m_game;
    entt::registry& m_registry;
    
    // Verifica se uma posição é válida para zoneamento
    bool isValidPosition(const sf::Vector2i& position) const;
    
    // Funções auxiliares para gerenciar entidades de zona
    entt::entity createZoneEntity(const sf::Vector2i& position, ZoneType type);
    void destroyZoneEntity(entt::entity entity);
    entt::entity findZoneEntityAt(const sf::Vector2i& position) const;
};

} // namespace CitySim