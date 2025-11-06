#include "Input/Mouse.hpp"

namespace CitySim::Input {

void Mouse::beginFrame() {
    m_justPressed.clear();
    m_justReleased.clear();
    m_wheelDelta = 0.0f;
}

void Mouse::handleEvent(const sf::Event::MouseButtonPressed& event) {
    const auto button = event.button;
    const bool inserted = m_pressedButtons.insert(button).second;
    if (inserted) {
        m_justPressed.insert(button);
    }
    m_position = event.position;
}

void Mouse::handleEvent(const sf::Event::MouseButtonReleased& event) {
    const auto button = event.button;
    if (m_pressedButtons.erase(button) > 0) {
        m_justReleased.insert(button);
    }
    m_position = event.position;
}

void Mouse::handleEvent(const sf::Event::MouseMoved& event) {
    m_position = event.position;
}

void Mouse::handleEvent(const sf::Event::MouseWheelScrolled& event) {
    m_wheelDelta += event.delta;
}

bool Mouse::isButtonPressed(sf::Mouse::Button button) const {
    return m_pressedButtons.find(button) != m_pressedButtons.end();
}

bool Mouse::wasButtonPressed(sf::Mouse::Button button) const {
    return m_justPressed.find(button) != m_justPressed.end();
}

bool Mouse::wasButtonReleased(sf::Mouse::Button button) const {
    return m_justReleased.find(button) != m_justReleased.end();
}

sf::Vector2i Mouse::position() const {
    return m_position;
}

float Mouse::wheelDelta() const {
    return m_wheelDelta;
}

} // namespace CitySim::Input
