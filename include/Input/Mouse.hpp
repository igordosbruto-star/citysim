#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <cstddef>
#include <unordered_set>

namespace CitySim::Input {

struct MouseButtonHash {
    std::size_t operator()(sf::Mouse::Button button) const noexcept {
        return static_cast<std::size_t>(button);
    }
};

class Mouse {
public:
    void beginFrame();

    void handleEvent(const sf::Event::MouseButtonPressed& event);
    void handleEvent(const sf::Event::MouseButtonReleased& event);
    void handleEvent(const sf::Event::MouseMoved& event);
    void handleEvent(const sf::Event::MouseWheelScrolled& event);

    bool isButtonPressed(sf::Mouse::Button button) const;
    bool wasButtonPressed(sf::Mouse::Button button) const;
    bool wasButtonReleased(sf::Mouse::Button button) const;

    sf::Vector2i position() const;
    float wheelDelta() const;

private:
    std::unordered_set<sf::Mouse::Button, MouseButtonHash> m_pressedButtons;
    std::unordered_set<sf::Mouse::Button, MouseButtonHash> m_justPressed;
    std::unordered_set<sf::Mouse::Button, MouseButtonHash> m_justReleased;

    sf::Vector2i m_position{0, 0};
    float m_wheelDelta = 0.0f;
};

} // namespace CitySim::Input
