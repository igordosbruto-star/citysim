// Incluir headers da STL PRIMEIRO, antes de qualquer coisa
#include <queue>
#include <unordered_set>

#include "Core/Systems/PowerSystem.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/NetworkNodeComponent.hpp"

namespace CitySim {

void PowerSystem::Update(float deltaTime) {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry() do System base
    
    // Reset the power state of all nodes
    for (auto entity : registry.view<PowerGridComponent>()) {
        auto& power = registry.get<PowerGridComponent>(entity);
        power.hasPower = power.isPowerPlant;
    }

    // Propaga energia a partir de cada usina
    for (auto entity : registry.view<PowerGridComponent>()) {
        const auto& power = registry.get<PowerGridComponent>(entity);
        if (!power.isPowerPlant) continue;
        if (registry.all_of<NetworkNodeComponent>(entity)) {
            propagatePower(entity, entity);
        }
    }
}

void PowerSystem::addPowerPlant(entt::entity entity, float capacity) {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    
    if (!registry.all_of<PowerGridComponent>(entity)) {
        registry.emplace<PowerGridComponent>(entity);
    }
    
    auto& power = registry.get<PowerGridComponent>(entity);
    power.powerCapacity = capacity;
    power.powerOutput = capacity;
    power.isPowerPlant = true;
    power.hasPower = true;
    power.gridRoot = entity;

    if (!registry.all_of<NetworkNodeComponent>(entity)) {
        auto& node = registry.emplace<NetworkNodeComponent>(entity);
        node.nodeEntity = entity;
        node.isActive = true;
        node.isPowered = true;
    }
}

bool PowerSystem::connectNodes(entt::entity node1, entt::entity node2) {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    
    if (!registry.valid(node1) || !registry.valid(node2)) {
        return false;
    }

    auto* node1Comp = registry.try_get<NetworkNodeComponent>(node1);
    auto* node2Comp = registry.try_get<NetworkNodeComponent>(node2);

    if (!node1Comp || !node2Comp || !canConnect(*node1Comp, *node2Comp)) {
        return false;
    }

    node1Comp->connections.push_back(node2);
    node2Comp->connections.push_back(node1);

    // Se um dos nós tem energia, atualiza o estado do outro
    if (hasAvailablePower(node1)) {
        updateNodePowerState(node2);
    } else if (hasAvailablePower(node2)) {
        updateNodePowerState(node1);
    }

    return true;
}

void PowerSystem::updateNodePowerState(entt::entity node) {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    auto* nodeComp = registry.try_get<NetworkNodeComponent>(node);
    auto* powerComp = registry.try_get<PowerGridComponent>(node);
    
    if (!nodeComp || !powerComp) {
        return;
    }

    // Se é uma usina, sempre tem energia
    if (powerComp->isPowerPlant) {
        nodeComp->isPowered = true;
        powerComp->hasPower = true;
        return;
    }

    // Verifica se alguma conexão tem energia
    for (auto connectedEntity : nodeComp->connections) {
        if (hasAvailablePower(connectedEntity)) {
            nodeComp->isPowered = true;
            powerComp->hasPower = true;
            return;
        }
    }

    nodeComp->isPowered = false;
    powerComp->hasPower = false;
}

float PowerSystem::calculateTotalDemand() const {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    float totalDemand = 0.0f;
    auto view = registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (!power.isPowerPlant) {
            totalDemand += power.powerDemand;
        }
    }
    return totalDemand;
}

float PowerSystem::calculateTotalOutput() const {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    float totalOutput = 0.0f;
    auto view = registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (power.isPowerPlant) {
            totalOutput += power.powerOutput;
        }
    }
    return totalOutput;
}

void PowerSystem::propagatePower(entt::entity startNode, entt::entity gridId) {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    std::queue<entt::entity> toVisit;
    std::unordered_set<entt::entity> visited;
    toVisit.push(startNode);
    visited.insert(startNode);

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        auto* nodeComp = registry.try_get<NetworkNodeComponent>(current);
        auto* powerComp = registry.try_get<PowerGridComponent>(current);

        if (!nodeComp || !powerComp) {
            continue;
        }

        // Marca o nó como energizado
        nodeComp->isPowered = true;
        powerComp->hasPower = true;
        powerComp->gridRoot = gridId;

        // Propaga para as conexões
        for (auto connectedEntity : nodeComp->connections) {
            if (visited.find(connectedEntity) == visited.end()) {
                visited.insert(connectedEntity);
                toVisit.push(connectedEntity);
            }
        }
    }
}

bool PowerSystem::canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const {
    // Por enquanto, apenas verifica se os nós já não estão conectados
    for (auto connectedEntity : node1.connections) {
        if (connectedEntity == node2.nodeEntity) {
            return false;
        }
    }
    return true;
}

bool PowerSystem::hasAvailablePower(entt::entity node) const {
    auto& registry = *GetRegistry(); // ← USAR GetRegistry()
    auto* nodeComp = registry.try_get<NetworkNodeComponent>(node);
    auto* powerComp = registry.try_get<PowerGridComponent>(node);
    
    if (!nodeComp || !powerComp) {
        return false;
    }

    return powerComp->hasPower || nodeComp->isPowered;
}

} // namespace CitySim