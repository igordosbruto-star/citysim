#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/BasicComponents.hpp"
#include "ECS/World.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/Graphics.hpp>

namespace CitySim {

RenderSystem::RenderSystem(sf::RenderTarget* target)
    : m_Target(target) {
}

bool RenderSystem::Init(entt::registry& registry) {
    return System::Init(registry);
}

void RenderSystem::Update(float dt) {
    auto view = GetRegistry()->view<TransformComponent, RenderableComponent>();

    // Sort entities by render layer
    std::vector<entt::entity> entities;
    for (auto entity : view) {
        entities.push_back(entity);
    }
    
    std::sort(entities.begin(), entities.end(), 
        [this](const entt::entity& a, const entt::entity& b) {
            return GetRegistry()->get<RenderableComponent>(a).layer < 
                   GetRegistry()->get<RenderableComponent>(b).layer;
        });

    // Render each entity in order
    for (auto entity : entities) {
        const auto& transform = GetRegistry()->get<TransformComponent>(entity);
        const auto& renderable = GetRegistry()->get<RenderableComponent>(entity);

        if (!renderable.visible) {
            continue;
        }
        
        // Debug visualization
        // Debug visualization
        if (m_DebugRenderEnabled) {
            sf::RectangleShape debugRect({10.f, 10.f});
            debugRect.setPosition(sf::Vector2f(transform.x - 5.f, transform.y - 5.f));
            debugRect.setRotation(sf::Angle(sf::degrees(transform.rotation)));
            debugRect.setScale(sf::Vector2f(transform.scaleX, transform.scaleY));
            debugRect.setFillColor(sf::Color::Transparent);
            debugRect.setOutlineColor(sf::Color::Green);
            debugRect.setOutlineThickness(1.f);
            if (m_Target) {
                m_Target->draw(debugRect);
            }
        }

        // TODO: Add actual rendering logic here once we have sprites or other
        // visual components defined
    }
}

} // namespace CitySim