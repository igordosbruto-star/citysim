#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cstddef>
#include <type_traits>
#include <unordered_set>

namespace CitySim::Input {

struct ScancodeHash {
    std::size_t operator()(sf::Keyboard::Scancode scancode) const noexcept {
        return static_cast<std::size_t>(scancode);
    }
};

class Keyboard {
public:
    void beginFrame();

    void handleEvent(const sf::Event::KeyPressed& event);
    void handleEvent(const sf::Event::KeyReleased& event);

    bool isPressed(sf::Keyboard::Scancode scancode) const;
    bool wasPressed(sf::Keyboard::Scancode scancode) const;
    bool wasReleased(sf::Keyboard::Scancode scancode) const;

private:
    std::unordered_set<sf::Keyboard::Scancode, ScancodeHash> m_pressedKeys;
    std::unordered_set<sf::Keyboard::Scancode, ScancodeHash> m_justPressed;
    std::unordered_set<sf::Keyboard::Scancode, ScancodeHash> m_justReleased;
};

} // namespace CitySim::Input
