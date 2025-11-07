#include "ECS/Entity.hpp"

namespace CitySimulator {

Entity::Entity(entt::entity handle, entt::registry* registry)
    : m_Handle(handle)
    , m_Registry(registry) {
}

bool Entity::IsValid() const {
    return m_Registry != nullptr && m_Handle != entt::null && m_Registry->valid(m_Handle);
}

} // namespace CitySimulator