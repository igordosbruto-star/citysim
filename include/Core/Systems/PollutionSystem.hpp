#pragma once

#include "ECS/System.hpp"
#include "Core/Components/PollutionComponent.hpp"
#include <SFML/System/Vector2.hpp>

namespace CitySim {

class PollutionSystem : public System {
public:
    PollutionSystem() = default;

    bool Init(entt::registry& registry) override {
        System::Init(registry);
        return true;
    }

    void Update(float deltaTime) override;

    std::string GetName() const override { return "PollutionSystem"; }

    // Calcula e atualiza a poluição em uma posição
    void updatePollutionAt(const sf::Vector2f& position);
    
    // Obtém o nível de poluição em uma posição
    float getPollutionAt(const sf::Vector2f& position) const;

private:
    // Propaga a poluição de uma fonte
    void propagatePollution(entt::entity source);
    
    // Constantes de simulação de poluição
    static constexpr float POLLUTION_DECAY_RATE = 0.01f;
    static constexpr float MAX_POLLUTION_RADIUS = 10.0f;
};

} // namespace CitySim