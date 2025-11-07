#pragma once

#include <entt/entt.hpp>
#include <Core/Components/PowerGridComponent.hpp>
#include <Core/Components/NetworkNodeComponent.hpp>

namespace CitySimulator {

class PowerSystem {
public:
    explicit PowerSystem(entt::registry& registry);

    void update(float dt);
    
    // Adiciona uma usina de energia
    void addPowerPlant(entt::entity entity, float capacity);
    
    // Conecta dois nós da rede elétrica
    bool connectNodes(entt::entity node1, entt::entity node2);
    
    // Atualiza o estado de energia de um nó
    void updateNodePowerState(entt::entity node);
    
    // Calcula demanda total de energia
    float calculateTotalDemand() const;
    
    // Calcula produção total de energia
    float calculateTotalOutput() const;

private:
    entt::registry& m_registry;
    
    // Propaga energia a partir de uma usina
    void propagatePower(entt::entity startNode, uint32_t gridId);
    
    // Verifica se dois nós estão próximos o suficiente para conectar
    bool canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const;
    
    // Verifica se um nó tem energia disponível
    bool hasAvailablePower(entt::entity node) const;
};

} // namespace CitySimulator