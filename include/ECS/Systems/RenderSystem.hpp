#pragma once

#include "ECS/System.hpp"
#include "ECS/Entity.hpp"
#include "Graphics/Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace CitySimulator {

/**
 * @brief System responsible for rendering entities with RenderableComponent.
 * 
 * This system processes all entities with both Transform and Renderable components
 * and draws them using the SFML renderer in the correct order based on their layer.
 */
class RenderSystem : public System {
public:
    explicit RenderSystem(sf::RenderTarget* target);
    ~RenderSystem() override = default;

    bool Init(entt::registry& registry) override;
    void Update(float deltaTime) override;
    std::string GetName() const override { return "RenderSystem"; }

    /**
     * @brief Set whether debug information should be rendered
     * @param enabled True to enable debug rendering
     */
    void SetDebugRenderEnabled(bool enabled) { m_DebugRenderEnabled = enabled; }

    /**
     * @brief Check if debug rendering is enabled
     * @return Current debug render state
     */
    bool IsDebugRenderEnabled() const { return m_DebugRenderEnabled; }

private:
    sf::RenderTarget* m_Target;
    bool m_DebugRenderEnabled = false;
};

} // namespace CitySimulator