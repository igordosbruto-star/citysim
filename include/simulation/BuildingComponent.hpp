#pragma once

namespace CitySim {

struct BuildingComponent {
    bool demolishable = true;  // Se o edifício pode ser demolido
    float health = 100.0f;     // Saúde do edifício (0-100)
    
    BuildingComponent() = default;
    explicit BuildingComponent(bool canDemolish) : demolishable(canDemolish) {}
};

} // namespace CitySim