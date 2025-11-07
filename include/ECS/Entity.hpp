#pragma once

#include <cstdint>
#include <entt/entt.hpp>

namespace CitySimulator {

/**
 * @brief Represents an entity in the game world.
 * 
 * An entity is just a thin wrapper around an entt::entity handle.
 * It provides a more semantic interface and type safety for game-specific operations.
 */
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, entt::registry* registry);
    
    /**
     * @brief Gets the underlying entt handle
     * @return The raw entt entity handle
     */
    entt::entity GetHandle() const { return m_Handle; }
    
    /**
     * @brief Gets the registry this entity belongs to
     * @return Pointer to the owning registry
     */
    entt::registry* GetRegistry() const { return m_Registry; }
    
    /**
     * @brief Check if the entity is valid
     * @return true if the entity has a valid handle and registry
     */
    bool IsValid() const;
    
    /**
     * @brief Add a component to this entity
     * @tparam T Component type to add
     * @tparam Args Constructor argument types for the component
     * @param args Arguments to forward to the component constructor
     * @return Reference to the added component
     */
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        return m_Registry->emplace<T>(m_Handle, std::forward<Args>(args)...);
    }
    
    /**
     * @brief Remove a component from this entity
     * @tparam T Component type to remove
     */
    template<typename T>
    void RemoveComponent() {
        m_Registry->remove<T>(m_Handle);
    }
    
    /**
     * @brief Check if this entity has a component
     * @tparam T Component type to check for
     * @return true if the entity has the component
     */
    template<typename T>
    bool HasComponent() const {
        return m_Registry->all_of<T>(m_Handle);
    }
    
    /**
     * @brief Get a component from this entity
     * @tparam T Component type to get
     * @return Reference to the component
     */
    template<typename T>
    T& GetComponent() {
        return m_Registry->get<T>(m_Handle);
    }
    
    /**
     * @brief Get a component from this entity (const version)
     * @tparam T Component type to get
     * @return Const reference to the component
     */
    template<typename T>
    const T& GetComponent() const {
        return m_Registry->get<T>(m_Handle);
    }

    /**
     * @brief Try to get a component from this entity
     * @tparam T Component type to get
     * @return Pointer to component if it exists, nullptr otherwise
     */
    template<typename T>
    T* TryGetComponent() {
        return m_Registry->try_get<T>(m_Handle);
    }

    /**
     * @brief Compare two entities for equality
     */
    bool operator==(const Entity& other) const {
        return m_Handle == other.m_Handle && m_Registry == other.m_Registry;
    }
    
    /**
     * @brief Compare two entities for inequality
     */
    bool operator!=(const Entity& other) const {
        return !(*this == other);
    }

private:
    entt::entity m_Handle{entt::null}; ///< The underlying entt entity handle
    entt::registry* m_Registry{nullptr}; ///< Pointer to the registry owning this entity
};

} // namespace CitySimulator