#pragma once

#include <entt/entt.hpp>
#include <Core/Components/PollutionComponent.hpp>
#include <Core/Components/NetworkNodeComponent.hpp>

namespace CitySimulator {

class GarbageSystem {
public:
    explicit GarbageSystem(entt::registry& registry);

    void update(float dt);
    
    // Adiciona uma instalação de tratamento de lixo
    void addGarbageFacility(entt::entity entity, float capacity);
    
    // Calcula capacidade total de processamento
    float calculateTotalCapacity() const;
    
    // Calcula quantidade total de lixo gerado
    float calculateTotalGarbage() const;

private:
    entt::registry& m_registry;
    
    // Taxa de geração de lixo por habitante
    static constexpr float GARBAGE_PER_CAPITA = 0.1f;
};

class PollutionSystem {
public:
    explicit PollutionSystem(entt::registry& registry);

    void update(float dt);
    
    // Calcula e atualiza a poluição em uma posição
    void updatePollutionAt(const sf::Vector2f& position);
    
    // Obtém o nível de poluição em uma posição
    float getPollutionAt(const sf::Vector2f& position) const;

private:
    entt::registry& m_registry;
    
    // Propaga a poluição de uma fonte
    void propagatePollution(entt::entity source);
    
    // Constantes de simulação de poluição
    static constexpr float POLLUTION_DECAY_RATE = 0.01f;
    static constexpr float MAX_POLLUTION_RADIUS = 10.0f;
};

} // namespace CitySimulator