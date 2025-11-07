#include <Core/Systems/GarbagePollutionSystem.hpp>
#include <cmath>

namespace CitySimulator {

// ===== GarbageSystem Implementation =====

GarbageSystem::GarbageSystem(entt::registry& registry)
    : m_registry(registry) {
}

void GarbageSystem::update(float dt) {
    auto facilities = m_registry.view<PollutionComponent>(entt::where([](const auto& pollution) {
        return pollution.isGarbageFacility;
    }));

    float totalGarbage = calculateTotalGarbage();
    float totalCapacity = calculateTotalCapacity();

    // Atualiza a taxa de poluição das instalações baseado na carga
    for (auto entity : facilities) {
        auto& pollution = facilities.get<PollutionComponent>(entity);
        if (totalCapacity > 0) {
            pollution.pollutionRate = (totalGarbage / totalCapacity) * pollution.pollutionLevel;
        } else {
            pollution.pollutionRate = pollution.pollutionLevel;
        }
    }
}

void GarbageSystem::addGarbageFacility(entt::entity entity, float capacity) {
    if (!m_registry.all_of<PollutionComponent>(entity)) {
        m_registry.emplace<PollutionComponent>(entity);
    }
    
    auto& pollution = m_registry.get<PollutionComponent>(entity);
    pollution.isGarbageFacility = true;
    pollution.pollutionRadius = std::sqrt(capacity); // Raio aumenta com a raiz da capacidade
    pollution.pollutionLevel = capacity * 0.1f;     // Nível base de poluição
}

float GarbageSystem::calculateTotalCapacity() const {
    float totalCapacity = 0.0f;
    auto view = m_registry.view<PollutionComponent>(entt::where([](const auto& pollution) {
        return pollution.isGarbageFacility;
    }));

    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        totalCapacity += pollution.pollutionRadius * 10.0f; // Capacidade é proporcional ao raio
    }

    return totalCapacity;
}

float GarbageSystem::calculateTotalGarbage() const {
    // Por enquanto, apenas uma simulação simples baseada no número de entidades
    // Posteriormente, será baseado na população real da cidade
    return static_cast<float>(m_registry.size()) * GARBAGE_PER_CAPITA;
}

// ===== PollutionSystem Implementation =====

PollutionSystem::PollutionSystem(entt::registry& registry)
    : m_registry(registry) {
}

void PollutionSystem::update(float dt) {
    // Atualiza a poluição de todas as fontes
    auto polluters = m_registry.view<PollutionComponent>();
    for (auto entity : polluters) {
        propagatePollution(entity);
    }

    // Decaimento natural da poluição
    for (auto entity : polluters) {
        auto& pollution = polluters.get<PollutionComponent>(entity);
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
    float totalPollution = 0.0f;
    auto view = m_registry.view<PollutionComponent>();

    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        // TODO: Calcular distância quando tivermos componente de posição
        // Por enquanto, retorna o nível máximo de poluição
        totalPollution = std::max(totalPollution, pollution.pollutionLevel);
    }

    return totalPollution;
}

void PollutionSystem::propagatePollution(entt::entity source) {
    auto* pollution = m_registry.try_get<PollutionComponent>(source);
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

} // namespace CitySimulator