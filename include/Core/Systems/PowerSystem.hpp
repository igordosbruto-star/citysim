#pragma once

#include "ECS/System.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/NetworkNodeComponent.hpp"

// Incluir headers da STL PRIMEIRO
#include <queue>
#include <unordered_set>

namespace CitySim {

class PowerSystem : public System {
public:
    PowerSystem() = default;
    
    bool Init(entt::registry& registry) override {
        System::Init(registry);
        return true;
    }
    
    void Update(float deltaTime) override;
    
    std::string GetName() const override { return "PowerSystem"; }

    // Métodos públicos mantidos:
    void addPowerPlant(entt::entity entity, float capacity);
    bool connectNodes(entt::entity node1, entt::entity node2);
    void updateNodePowerState(entt::entity node);
    float calculateTotalDemand() const;
    float calculateTotalOutput() const;
    void propagatePower(entt::entity startNode, entt::entity gridId);
    bool canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const;
    bool hasAvailablePower(entt::entity node) const;

private:
    // Removido: entt::registry& m_registry;
};

} // namespace CitySim