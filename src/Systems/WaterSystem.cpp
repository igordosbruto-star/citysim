#include "Core/Systems/WaterSystem.hpp"
#include <queue>
#include <unordered_set>

namespace CitySim {

void WaterSystem::Update(float deltaTime) {
    auto& registry = *GetRegistry();
    
    // Reset the water state of all nodes
    for (auto entity : registry.view<WaterGridComponent>()) {
        auto& water = registry.get<WaterGridComponent>(entity);
        water.hasWater = water.isWaterPlant;
    }

    // Propaga água a partir de cada estação
    for (auto entity : registry.view<WaterGridComponent>()) {
        const auto& water = registry.get<WaterGridComponent>(entity);
        if (!water.isWaterPlant) continue;
        if (registry.all_of<NetworkNodeComponent>(entity)) {
            propagateWater(entity, entity);
        }
    }
}

void WaterSystem::addWaterPlant(entt::entity entity, float capacity) {
    auto& registry = *GetRegistry();
    
    if (!registry.all_of<WaterGridComponent>(entity)) {
        registry.emplace<WaterGridComponent>(entity);
    }
    
    auto& water = registry.get<WaterGridComponent>(entity);
    water.waterCapacity = capacity;
    water.waterOutput = capacity;
    water.isWaterPlant = true;
    water.hasWater = true;
    water.gridRoot = entity;

    if (!registry.all_of<NetworkNodeComponent>(entity)) {
        auto& node = registry.emplace<NetworkNodeComponent>(entity);
        node.nodeEntity = entity;
        node.isActive = true;
        node.hasWater = true;
    }
}

bool WaterSystem::connectNodes(entt::entity node1, entt::entity node2) {
    auto& registry = *GetRegistry();
    
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

    // Se um dos nós tem água, atualiza o estado do outro
    if (hasAvailableWater(node1)) {
        updateNodeWaterState(node2);
    } else if (hasAvailableWater(node2)) {
        updateNodeWaterState(node1);
    }

    return true;
}

void WaterSystem::updateNodeWaterState(entt::entity node) {
    auto& registry = *GetRegistry();
    auto* nodeComp = registry.try_get<NetworkNodeComponent>(node);
    auto* waterComp = registry.try_get<WaterGridComponent>(node);
    
    if (!nodeComp || !waterComp) {
        return;
    }

    // Se é uma estação, sempre tem água
    if (waterComp->isWaterPlant) {
        nodeComp->hasWater = true;
        waterComp->hasWater = true;
        return;
    }

    // Verifica se alguma conexão tem água
    for (auto connectedEntity : nodeComp->connections) {
        if (hasAvailableWater(connectedEntity)) {
            nodeComp->hasWater = true;
            waterComp->hasWater = true;
            return;
        }
    }

    nodeComp->hasWater = false;
    waterComp->hasWater = false;
}

float WaterSystem::calculateTotalDemand() const {
    auto& registry = *GetRegistry();
    float totalDemand = 0.0f;
    auto view = registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (!water.isWaterPlant) {
            totalDemand += water.waterDemand;
        }
    }
    return totalDemand;
}

float WaterSystem::calculateTotalOutput() const {
    auto& registry = *GetRegistry();
    float totalOutput = 0.0f;
    auto view = registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (water.isWaterPlant) {
            totalOutput += water.waterOutput;
        }
    }
    return totalOutput;
}

void WaterSystem::propagateWater(entt::entity startNode, entt::entity gridId) {
    auto& registry = *GetRegistry();
    std::queue<entt::entity> toVisit;
    std::unordered_set<entt::entity> visited;
    toVisit.push(startNode);
    visited.insert(startNode);

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        auto* nodeComp = registry.try_get<NetworkNodeComponent>(current);
        auto* waterComp = registry.try_get<WaterGridComponent>(current);

        if (!nodeComp || !waterComp) {
            continue;
        }

        // Marca o nó como tendo água
        nodeComp->hasWater = true;
        waterComp->hasWater = true;
        waterComp->gridRoot = gridId;

        // Propaga para as conexões
        for (auto connectedEntity : nodeComp->connections) {
            if (visited.find(connectedEntity) == visited.end()) {
                visited.insert(connectedEntity);
                toVisit.push(connectedEntity);
            }
        }
    }
}

bool WaterSystem::canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const {
    // Por enquanto, apenas verifica se os nós já não estão conectados
    for (auto connectedEntity : node1.connections) {
        if (connectedEntity == node2.nodeEntity) {
            return false;
        }
    }
    return true;
}

bool WaterSystem::hasAvailableWater(entt::entity node) const {
    auto& registry = *GetRegistry();
    auto* nodeComp = registry.try_get<NetworkNodeComponent>(node);
    auto* waterComp = registry.try_get<WaterGridComponent>(node);
    
    if (!nodeComp || !waterComp) {
        return false;
    }

    return waterComp->hasWater || nodeComp->hasWater;
}

} // namespace CitySim