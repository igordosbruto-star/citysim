#pragma once

#include "ECS/Entity.hpp"
#include <string>
#include <vector>
#include <memory>
#include <entt/entt.hpp>

namespace CitySimulator {

/**
 * @brief Base class for all ECS systems.
 * 
 * Systems operate on entities with specific components. Each system should focus
 * on a single responsibility and operate on components in a data-oriented way.
 */
class System {
public:
    virtual ~System() = default;

    /**
     * @brief Initialize the system with the registry
     * @param registry The EnTT registry to use
     * @return true if initialization was successful
     */
    virtual bool Init(entt::registry& registry) {
        m_Registry = &registry;
        return true;
    }

    /**
     * @brief Update the system
     * @param deltaTime Time since last update in seconds
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief Get the name of this system
     * @return String identifier for the system
     */
    virtual std::string GetName() const = 0;

    /**
     * @brief Enable or disable the system
     * @param enabled New enabled state
     */
    void SetEnabled(bool enabled) { m_Enabled = enabled; }

    /**
     * @brief Check if the system is enabled
     * @return Current enabled state
     */
    bool IsEnabled() const { return m_Enabled; }

protected:
    System() = default;
    entt::registry* GetRegistry() const { return m_Registry; }

    template<typename... Args>
    auto GetView() {
        return m_Registry->view<Args...>();
    }

private:
    bool m_Enabled = true;
    entt::registry* m_Registry = nullptr;
};

} // namespace CitySimulator