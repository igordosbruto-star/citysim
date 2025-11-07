#pragma once

#include "ECS/Component.hpp"
#include <string>

namespace CitySim {

/**
 * @brief Basic transform component storing position, rotation and scale.
 */
struct TransformComponent : public Component {
    float x = 0.0f;            ///< X position in world space
    float y = 0.0f;            ///< Y position in world space
    float rotation = 0.0f;     ///< Rotation in degrees
    float scaleX = 1.0f;       ///< Scale on X axis
    float scaleY = 1.0f;       ///< Scale on Y axis

    TransformComponent() = default;
    TransformComponent(float x, float y, float rotation = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f)
        : x(x), y(y), rotation(rotation), scaleX(scaleX), scaleY(scaleY) {}
};

/**
 * @brief Component for tagging and identifying entities.
 */
struct TagComponent : public Component {
    std::string tag;           ///< String identifier for the entity

    TagComponent() = default;
    explicit TagComponent(const std::string& tag) : tag(tag) {}
};

/**
 * @brief Component indicating an entity should be rendered.
 */
struct RenderableComponent : public Component {
    bool visible = true;       ///< Whether the entity should be rendered
    int layer = 0;            ///< Render layer/order (higher numbers render on top)
    // Additional rendering properties can be added here as needed

    RenderableComponent() = default;
    RenderableComponent(bool visible, int layer = 0) : visible(visible), layer(layer) {}
};

} // namespace CitySimu