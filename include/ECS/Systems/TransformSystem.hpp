#pragma once

#include "ECS/System.hpp"
#include <string>

namespace CitySimulator {

/**
 * @brief System for updating transform hierarchies and handling transform-related logic.
 * 
 * This system processes TransformComponent updates, handles parenting relationships
 * if implemented, and can provide utility functions for transform operations.
 */
class TransformSystem : public System {
public:
    TransformSystem() = default;
    ~TransformSystem() override = default;

    bool Init(entt::registry& registry) override;
    void Update(float deltaTime) override;
    std::string GetName() const override { return "TransformSystem"; }

private:
    // TODO: Add transform hierarchy support if needed
};

} // namespace CitySimulator