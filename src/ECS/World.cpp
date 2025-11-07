#include "ECS/World.hpp"
#include "ECS/Components/BasicComponents.hpp"
#include "Utils/Logger.hpp"

namespace CitySim {

World::World() = default;

World::~World() = default;

Entity World::CreateEntity(const std::string& name) {
    Entity entity{m_Registry.create(), &m_Registry};
    
    // Add default components
    entity.AddComponent<TransformComponent>();
    
    // Add tag if name provided
    if (!name.empty()) {
        entity.AddComponent<TagComponent>(name);
    }
    
    return entity;
}

void World::DestroyEntity(Entity entity) {
    if (entity.IsValid()) {
        m_Registry.destroy(entity.GetHandle());
    }
}

Entity World::FindEntityByName(const std::string& name) {
    auto view = m_Registry.view<TagComponent>();
    for (auto [entity, tag] : view.each()) {
        if (tag.tag == name) {
            return Entity{entity, &m_Registry};
        }
    }
    return Entity{}; // Return invalid entity if not found
}

void World::Update(float deltaTime) {
    for (auto& system : m_Systems) {
        if (system->IsEnabled()) {
            system->Update(deltaTime);
        }
    }
}

void World::Clear() {
    m_Registry.clear();
    m_Systems.clear();
}

bool World::InitSystems() {
    bool success = true;
    for (auto& system : m_Systems) {
        if (!system->Init(m_Registry)) {
            success = false;
            LOG_ERROR("Failed to initialize system");
            break; // Stop initializing on first failure
        }
    }
    return success;
}

} // namespace CitySim