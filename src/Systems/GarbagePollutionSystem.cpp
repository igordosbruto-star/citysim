#include "Core/Systems/GarbagePollutionSystem.hpp"
#include "Core/Components/PollutionComponent.hpp"
#include <cmath>

namespace CitySim {

GarbageSystem::GarbageSystem(entt::registry& registry)
    : m_registry(registry) {
}

void GarbageSystem::update(float dt) {
    (void)dt; // Silencia warning de parâmetro não utilizado
    
    float totalGarbage = calculateTotalGarbage();
    float totalCapacity = calculateTotalCapacity();

    // Atualiza a taxa de poluição das instalações baseado na carga
    auto view = m_registry.view<PollutionComponent>();
    for (auto entity : view) {
        auto& pollution = view.get<PollutionComponent>(entity);
        if (!pollution.isGarbageFacility) continue;
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
    auto view = m_registry.view<PollutionComponent>();
    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        if (!pollution.isGarbageFacility) continue;
        totalCapacity += pollution.pollutionRadius * 10.0f; // Capacidade é proporcional ao raio
    }
    return totalCapacity;
}

float GarbageSystem::calculateTotalGarbage() const {
    // CORREÇÃO: Método alternativo para contar entidades
    // Usando uma view com um componente que todas as entidades relevantes têm
    // Por exemplo, se você tem um componente Transform ou similar
    uint32_t entityCount = 0;
    
    // Se você não tem um componente comum, pode usar este workaround:
    // Crie uma view com um componente que muitas entidades têm,
    // ou mantenha um contador manual
    
    // Workaround simples: assumir um número fixo por enquanto
    // Você pode ajustar isso posteriormente quando tiver componentes específicos
    entityCount = 100; // Número arbitrário por enquanto
    
    return static_cast<float>(entityCount) * GARBAGE_PER_CAPITA;
}

// ===== PollutionSystem Implementation =====

PollutionSystem::PollutionSystem(entt::registry& registry)
    : m_registry(registry) {
}

void PollutionSystem::update(float dt) {
    (void)dt; // Silencia warning de parâmetro não utilizado
    
    // Atualiza a poluição de todas as fontes
    auto pollutionView = m_registry.view<PollutionComponent>();
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
    float totalPollution = 0.0f;
    auto pollutionView = m_registry.view<PollutionComponent>();
    for (auto entity : pollutionView) {
        const auto& pollution = pollutionView.get<PollutionComponent>(entity);
        // TODO: Calcular distância quando tivermos o componente de posição
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

} // namespace CitySim