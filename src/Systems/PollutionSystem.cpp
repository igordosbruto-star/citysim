#include "Core/Systems/PollutionSystem.hpp"
#include <cmath>

namespace CitySim {

void PollutionSystem::Update(float dt) {
    auto& registry = *GetRegistry();
    
    // Atualiza a poluição de todas as fontes
    auto pollutionView = registry.view<PollutionComponent>();
    for (auto entity : pollutionView) {
        propagatePollution(entity);
    }

    // Decaimento natural da poluição
    for (auto entity : pollutionView) {
        auto& pollution = pollutionView.get<PollutionComponent>(entity);
        if (!pollution.isGarbageFacility) {  // Instalações mantêm seu nível
            pollution.pollutionLevel = std::max(0.0f,
                pollution.pollutionLevel - (POLLUTION_DECAY_RATE * dt));
        }
    }
}

void PollutionSystem::updatePollutionAt(const sf::Vector2f& position) {
    // TODO: Implementar quando tivermos o sistema de grid espacial
}

float PollutionSystem::getPollutionAt(const sf::Vector2f& position) const {
    auto& registry = *GetRegistry();
    float totalPollution = 0.0f;
    auto pollutionView = registry.view<PollutionComponent>();
    for (auto entity : pollutionView) {
        const auto& pollution = pollutionView.get<PollutionComponent>(entity);
        // TODO: Calcular distância quando tivermos o componente de posição
        // Por enquanto, retorna o nível máximo de poluição
        totalPollution = std::max(totalPollution, pollution.pollutionLevel);
    }
    return totalPollution;
}

void PollutionSystem::propagatePollution(entt::entity source) {
    auto& registry = *GetRegistry();
    auto* pollution = registry.try_get<PollutionComponent>(source);
    if (!pollution) {
        return;
    }

    // Atualiza o nível de poluição
    if (pollution->isGarbageFacility) {
        // Instalações mantêm um nível constante de poluição
        pollution->pollutionLevel = std::min(
            pollution->pollutionLevel + pollution->pollutionRate,
            MAX_POLLUTION_RADIUS * pollution->pollutionRadius
        );
    }

    // TODO: Implementar propagação espacial quando tivermos o sistema de grid
}

} // namespace CitySim