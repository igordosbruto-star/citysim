#include <Core/Systems/PowerSystem.hpp>
#include <queue>
#include <unordered_set>

namespace CitySimulator {

PowerSystem::PowerSystem(entt::registry& registry)
    : m_registry(registry) {
}

void PowerSystem::update(float dt) {
    // Reset the power state of all nodes
    auto view = m_registry.view<PowerGridComponent>();
    for (auto entity : view) {
        auto& power = view.get<PowerGridComponent>(entity);
        power.hasPower = power.isPowerPlant;
    }

    // Propaga energia a partir de cada usina
    auto powerPlants = m_registry.view<PowerGridComponent>(entt::where([](const auto& power) {
        return power.isPowerPlant;
    }));

    for (auto entity : powerPlants) {
        auto& power = powerPlants.get<PowerGridComponent>(entity);
        if (m_registry.all_of<NetworkNodeComponent>(entity)) {
            propagatePower(entity, power.gridId);
        }
    }
}

void PowerSystem::addPowerPlant(entt::entity entity, float capacity) {
    if (!m_registry.all_of<PowerGridComponent>(entity)) {
        m_registry.emplace<PowerGridComponent>(entity);
    }
    
    auto& power = m_registry.get<PowerGridComponent>(entity);
    power.powerCapacity = capacity;
    power.powerOutput = capacity;
    power.isPowerPlant = true;
    power.hasPower = true;
    power.gridId = static_cast<uint32_t>(entity);

    if (!m_registry.all_of<NetworkNodeComponent>(entity)) {
        auto& node = m_registry.emplace<NetworkNodeComponent>(entity);
        node.nodeId = static_cast<uint32_t>(entity);
        node.isActive = true;
        node.isPowered = true;
    }
}

bool PowerSystem::connectNodes(entt::entity node1, entt::entity node2) {
    if (!m_registry.valid(node1) || !m_registry.valid(node2)) {
        return false;
    }

    auto* node1Comp = m_registry.try_get<NetworkNodeComponent>(node1);
    auto* node2Comp = m_registry.try_get<NetworkNodeComponent>(node2);

    if (!node1Comp || !node2Comp || !canConnect(*node1Comp, *node2Comp)) {
        return false;
    }

    node1Comp->connections.push_back(node2Comp->nodeId);
    node2Comp->connections.push_back(node1Comp->nodeId);

    // Se um dos nós tem energia, atualiza o estado do outro
    if (hasAvailablePower(node1)) {
        updateNodePowerState(node2);
    } else if (hasAvailablePower(node2)) {
        updateNodePowerState(node1);
    }

    return true;
}

void PowerSystem::updateNodePowerState(entt::entity node) {
    auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(node);
    auto* powerComp = m_registry.try_get<PowerGridComponent>(node);
    
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
    for (auto connectedId : nodeComp->connections) {
        auto connectedEntity = static_cast<entt::entity>(connectedId);
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
    float totalDemand = 0.0f;
    auto view = m_registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (!power.isPowerPlant) {
            totalDemand += power.powerDemand;
        }
    }
    return totalDemand;
}

float PowerSystem::calculateTotalOutput() const {
    float totalOutput = 0.0f;
    auto view = m_registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (power.isPowerPlant) {
            totalOutput += power.powerOutput;
        }
    }
    return totalOutput;
}

void PowerSystem::propagatePower(entt::entity startNode, uint32_t gridId) {
    std::queue<entt::entity> toVisit;
    std::unordered_set<entt::entity> visited;
    toVisit.push(startNode);
    visited.insert(startNode);

    while (!toVisit.empty()) {
        auto current = toVisit.front();
        toVisit.pop();

        auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(current);
        auto* powerComp = m_registry.try_get<PowerGridComponent>(current);

        if (!nodeComp || !powerComp) {
            continue;
        }

        // Marca o nó como energizado
        nodeComp->isPowered = true;
        powerComp->hasPower = true;
        powerComp->gridId = gridId;

        // Propaga para as conexões
        for (auto connectedId : nodeComp->connections) {
            auto connectedEntity = static_cast<entt::entity>(connectedId);
            if (visited.find(connectedEntity) == visited.end()) {
                visited.insert(connectedEntity);
                toVisit.push(connectedEntity);
            }
        }
    }
}

bool PowerSystem::canConnect(const NetworkNodeComponent& node1, const NetworkNodeComponent& node2) const {
    // Por enquanto, apenas verifica se os nós já não estão conectados
    for (auto connectedId : node1.connections) {
        if (connectedId == node2.nodeId) {
            return false;
        }
    }
    return true;
}

bool PowerSystem::hasAvailablePower(entt::entity node) const {
    auto* nodeComp = m_registry.try_get<NetworkNodeComponent>(node);
    auto* powerComp = m_registry.try_get<PowerGridComponent>(node);
    
    if (!nodeComp || !powerComp) {
        return false;
    }

    return powerComp->hasPower || nodeComp->isPowered;
}

} // namespace CitySimulator