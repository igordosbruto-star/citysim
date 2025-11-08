#pragma once

#include "ECS/System.hpp"
#include "Core/Components/PollutionComponent.hpp"

namespace CitySim {

class GarbageSystem : public System {
public:
    GarbageSystem() = default;

    bool Init(entt::registry& registry) override {
        System::Init(registry);
        return true;
    }

    void Update(float deltaTime) override;

    std::string GetName() const override { return "GarbageSystem"; }

    // Adiciona uma instalação de tratamento de lixo
    void addGarbageFacility(entt::entity entity, float capacity);
    
    // Calcula capacidade total de processamento
    float calculateTotalCapacity() const;
    
    // Calcula quantidade total de lixo gerado
    float calculateTotalGarbage() const;

private:
    // Taxa de geração de lixo por habitante
    static constexpr float GARBAGE_PER_CAPITA = 0.1f;
};

} // namespace CitySim