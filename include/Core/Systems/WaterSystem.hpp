#pragma once

#include "ECS/System.hpp"
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/NetworkNodeComponent.hpp"

namespace CitySim {

class WaterSystem : public System {
public:
    WaterSystem() = default;

    bool Init(entt::registry& registry) override {
        System::Init(registry);
        return true;
    }

    void Update(float deltaTime) override;

    std::string GetName() const override { return "WaterSystem"; }

    // Métodos públicos mantidos:
    void addWaterPlant(entt::entity entity, float capacity);
    bool connectNodes(entt::entity node1, entt::entity node2);
    void updateNodeWaterState(entt::entity node);
    float calculateTotalDemand() const;
    float calculateTotalOutput() const;

private:
    // Removido: entt::registry& m_registry;

    // Propaga água a partir de uma estação
    void propagateWater(entt::entity startNode, entt::entity gridId);
    
    // Verifica se dois nós estão próximos o suficiente para conectar
    bool canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const;
    
    // Verifica se um nó tem água disponível
    bool hasAvailableWater(entt::entity node) const;
};

} // namespace CitySim