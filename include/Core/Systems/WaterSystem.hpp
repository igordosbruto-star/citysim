#pragma once

#include <entt/entt.hpp>
#include <Core/Components/WaterGridComponent.hpp>
#include <Core/Components/NetworkNodeComponent.hpp>

namespace CitySim {

class WaterSystem {
public:
    explicit WaterSystem(entt::registry& registry);

    void update(float dt);
    
    // Adiciona uma estação de tratamento de água
    void addWaterPlant(entt::entity entity, float capacity);
    
    // Conecta dois nós da rede de água
    bool connectNodes(entt::entity node1, entt::entity node2);
    
    // Atualiza o estado de água de um nó
    void updateNodeWaterState(entt::entity node);
    
    // Calcula demanda total de água
    float calculateTotalDemand() const;
    
    // Calcula produção total de água
    float calculateTotalOutput() const;

private:
    entt::registry& m_registry;
    
    // Propaga água a partir de uma estação
    void propagateWater(entt::entity startNode, entt::entity gridId);
    
    // Verifica se dois nós estão próximos o suficiente para conectar
    bool canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const;
    
    // Verifica se um nó tem água disponível
    bool hasAvailableWater(entt::entity node) const;
};

} // namespace CitySim