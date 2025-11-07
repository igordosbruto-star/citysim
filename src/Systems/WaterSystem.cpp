#include <Core/Systems/WaterSystem.hpp>
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/NetworkNodeComponent.hpp"
#include <queue>
#include <unordered_set>

namespace CitySim {

WaterSystem::WaterSystem(entt::registry& registry)
    : m_registry(registry) {
}

void WaterSystem::update(float dt) {
    // Reset the water state of all nodes
    for (auto entity : m_registry.view<WaterGridComponent>()) {
        auto& water = m_registry.get<WaterGridComponent>(entity);
        water.hasWater = water.isWaterPlant;
    }

    // Propaga água a partir de cada estação
    for (auto entity : m_registry.view<WaterGridComponent>()) {
        const auto& water = m_registry.get<WaterGridComponent>(entity);
        if (!water.isWaterPlant) continue;
        if (m_registry.all_of<NetworkNodeComponent>(entity)) {
            propagateWater(entity, entity);
        }
    }
}

void WaterSystem::addWaterPlant(entt::entity entity, float capacity) {
    if (!m_registry.all_of<WaterGridComponent>(entity)) {
        m_registry.emplace<WaterGridComponent>(entity);
    }
    
    auto& water = m_registry.get<WaterGridComponent>(entity);
    water.waterCapacity = capacity;
    water.waterOutput = capacity;
    water.isWaterPlant = true;
    water.hasWater = true;
    water.gridRoot = entity;

    if (!m_registry.all_of<NetworkNodeComponent>(entity)) {
        auto& node = m_registry.emplace<NetworkNodeComponent>(entity);
        node.nodeEntity = entity;
        node.isActive = true;
        node.hasWater = true;
    }
}

bool WaterSystem::connectNodes(entt::entity node1, entt::entity node2) {
    if (!m_registry.valid(node1) || !m_registry.valid(node2)) {
        return false;
    }

    auto* node1Comp = m_registry.try_get<NetworkNodeComponent>(node1);
    auto* node2Comp = m_registry.try_get<NetworkNodeComponent>(node2);

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
    auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(node);
    auto* waterComp = m_registry.try_get<WaterGridComponent>(node);
    
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
    float totalDemand = 0.0f;
    auto view = m_registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (!water.isWaterPlant) {
            totalDemand += water.waterDemand;
        }
    }
    return totalDemand;
}

float WaterSystem::calculateTotalOutput() const {
    float totalOutput = 0.0f;
    auto view = m_registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (water.isWaterPlant) {
            totalOutput += water.waterOutput;
        }
    }
    return totalOutput;
}

void WaterSystem::propagateWater(entt::entity startNode, entt::entity gridId) {
    std::queue<entt::entity> toVisit;
    std::unordered_set<entt::entity> visited;
    toVisit.push(startNode);
    visited.insert(startNode);

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(current);
        auto* waterComp = m_registry.try_get<WaterGridComponent>(current);

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
    auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(node);
    auto* waterComp = m_registry.try_get<WaterGridComponent>(node);
    
    if (!nodeComp || !waterComp) {
        return false;
    }

    return waterComp->hasWater || nodeComp->hasWater;
}

} // namespace CitySim