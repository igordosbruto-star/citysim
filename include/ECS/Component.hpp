#pragma once

namespace CitySimulator {

/**
 * @brief Base class for all components in the ECS system.
 * 
 * Components are pure data classes without behavior. They should be simple POD-like 
 * structs that contain only the data needed for systems to operate on entities.
 * 
 * This base class serves as a common interface and type for runtime reflection,
 * but most components should simply be structs inheriting from it.
 */
class Component {
public:
    virtual ~Component() = default;
protected:
    Component() = default;
};

} // namespace CitySimulator