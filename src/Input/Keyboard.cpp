#include "Input/Keyboard.hpp"

namespace CitySim::Input {

void Keyboard::beginFrame() {
    m_justPressed.clear();
    m_justReleased.clear();
}

void Keyboard::handleEvent(const sf::Event::KeyPressed& event) {
    const auto scancode = event.scancode;
    const bool inserted = m_pressedKeys.insert(scancode).second;
    if (inserted) {
        m_justPressed.insert(scancode);
    }
}

void Keyboard::handleEvent(const sf::Event::KeyReleased& event) {
    const auto scancode = event.scancode;
    if (m_pressedKeys.erase(scancode) > 0) {
        m_justReleased.insert(scancode);
    }
}

bool Keyboard::isPressed(sf::Keyboard::Scancode scancode) const {
    return m_pressedKeys.find(scancode) != m_pressedKeys.end();
}

bool Keyboard::wasPressed(sf::Keyboard::Scancode scancode) const {
    return m_justPressed.find(scancode) != m_justPressed.end();
}

bool Keyboard::wasReleased(sf::Keyboard::Scancode scancode) const {
    return m_justReleased.find(scancode) != m_justReleased.end();
}

} // namespace CitySim::Input
