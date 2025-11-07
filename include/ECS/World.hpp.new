#pragma once

#include "ECS/Entity.hpp"
#include "ECS/System.hpp"
#include <entt/entt.hpp>
#include <memory>
#include <vector>
#include <string>

namespace CitySimulator {

/**
 * @brief Main container and manager for ECS entities and systems.
 * 
 * The World class manages the lifecycle of all entities and systems. It wraps an
 * entt::registry and provides a higher-level interface for game-specific operations.
 */
class World {
public:
    World();
    ~World();

    /**
     * @brief Create a new entity
     * @param name Optional name/tag for the entity
     * @return New Entity instance
     */
    Entity CreateEntity(const std::string& name = std::string());

    /**
     * @brief Destroy an entity and all its components
     * @param entity Entity to destroy
     */
    void DestroyEntity(Entity entity);

    /**
     * @brief Get the underlying entt registry
     * @return Reference to the registry
     */
    entt::registry& GetRegistry() { return m_Registry; }

    /**
     * @brief Get the underlying entt registry (const version)
     * @return Const reference to the registry
     */
    const entt::registry& GetRegistry() const { return m_Registry; }

    /**
     * @brief Add a system to the world
     * @tparam T System type to add
     * @tparam Args Constructor argument types
     * @param args Arguments to forward to system constructor
     * @return Reference to the newly added system
     */
    template<typename T, typename... Args>
    T& AddSystem(Args&&... args) {
        static_assert(std::is_base_of<System, T>::value, "T must derive from System");
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T& systemRef = *system;
        m_Systems.push_back(std::move(system));
        return systemRef;
    }
    
    /**
     * @brief Get a system of specified type
     * @tparam T System type to get
     * @return Pointer to system if found, nullptr otherwise
     */
    template<typename T>
    T* GetSystem() {
        static_assert(std::is_base_of<System, T>::value, "T must derive from System");
        for (auto& system : m_Systems) {
            if (auto ptr = dynamic_cast<T*>(system.get())) {
                return ptr;
            }
        }
        return nullptr;
    }

    /**
     * @brief Initialize all systems with the registry
     * @return true if all systems initialized successfully
     */
    bool InitSystems();

    /**
     * @brief Update all enabled systems
     * @param deltaTime Time since last update in seconds
     */
    void Update(float deltaTime);

    /**
     * @brief Get entity by name/tag
     * @param name Name to search for
     * @return Entity with matching name, or invalid entity if not found
     */
    Entity FindEntityByName(const std::string& name);

    /**
     * @brief Clear all entities and systems
     */
    void Clear();

private:
    entt::registry m_Registry;                        ///< Main ECS registry
    std::vector<std::unique_ptr<System>> m_Systems;   ///< Registered systems
};

} // namespace CitySimulator