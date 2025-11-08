#include "Core/Systems/GarbageSystem.hpp"
#include <cmath>

namespace CitySim {

void GarbageSystem::Update(float dt) {
    auto& registry = *GetRegistry();
    
    float totalGarbage = calculateTotalGarbage();
    float totalCapacity = calculateTotalCapacity();

    // Atualiza a taxa de poluição das instalações baseado na carga
    auto view = registry.view<PollutionComponent>();
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
    auto& registry = *GetRegistry();
    
    if (!registry.all_of<PollutionComponent>(entity)) {
        registry.emplace<PollutionComponent>(entity);
    }
    
    auto& pollution = registry.get<PollutionComponent>(entity);
    pollution.isGarbageFacility = true;
    pollution.pollutionRadius = std::sqrt(capacity); // Raio aumenta com a raiz da capacidade
    pollution.pollutionLevel = capacity * 0.1f;     // Nível base de poluição
}

float GarbageSystem::calculateTotalCapacity() const {
    auto& registry = *GetRegistry();
    float totalCapacity = 0.0f;
    auto view = registry.view<PollutionComponent>();
    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        if (!pollution.isGarbageFacility) continue;
        totalCapacity += pollution.pollutionRadius * 10.0f; // Capacidade é proporcional ao raio
    }
    return totalCapacity;
}

float GarbageSystem::calculateTotalGarbage() const {
    auto& registry = *GetRegistry();
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

} // namespace CitySim