#pragma once

#include <SFML/System/Vector2.hpp>
#include "ZoneComponent.hpp"

namespace CitySim {

struct GridComponent {
    sf::Vector2i position;
    ZoneType zoneType = ZoneType::None;
    
    GridComponent() = default;
    GridComponent(const sf::Vector2i& pos, ZoneType type = ZoneType::None)
        : position(pos), zoneType(type) {}
};

} // namespace CitySim