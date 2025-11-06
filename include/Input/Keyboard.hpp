#pragma once

#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cstddef>
#include <unordered_set>

namespace CitySim::Input {

struct KeyHash {
    std::size_t operator()(sf::Keyboard::Key key) const noexcept {
        return static_cast<std::size_t>(key);
    }
};

class Keyboard {
public:
    void beginFrame();

#if SFML_VERSION_MAJOR >= 3
    void handlePressed(const sf::Event::KeyPressed& event);
    void handleReleased(const sf::Event::KeyReleased& event);
#else
    void handlePressed(const sf::Event::KeyEvent& event);
    void handleReleased(const sf::Event::KeyEvent& event);
#endif

    bool isPressed(sf::Keyboard::Key key) const;
    bool wasPressed(sf::Keyboard::Key key) const;
    bool wasReleased(sf::Keyboard::Key key) const;

private:
    std::unordered_set<sf::Keyboard::Key, KeyHash> m_pressedKeys;
    std::unordered_set<sf::Keyboard::Key, KeyHash> m_justPressed;
    std::unordered_set<sf::Keyboard::Key, KeyHash> m_justReleased;
};

} // namespace CitySim::Input
