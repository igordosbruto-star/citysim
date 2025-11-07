#pragma once

#include "ZoneType.hpp"

namespace CitySim {

struct ZoneComponent {
    ZoneType type = ZoneType::None;
    int level = 0;  // Nível de desenvolvimento da zona
    float happiness = 1.0f;  // Satisfação (0.0 a 1.0)
    
    ZoneComponent() = default;
    explicit ZoneComponent(ZoneType zoneType) : type(zoneType) {}
};

} // namespace CitySim