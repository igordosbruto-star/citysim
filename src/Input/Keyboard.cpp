#include "Input/Keyboard.hpp"

namespace CitySim::Input {

void Keyboard::beginFrame() {
    m_justPressed.clear();
    m_justReleased.clear();
}

#if SFML_VERSION_MAJOR >= 3
void Keyboard::handlePressed(const sf::Event::KeyPressed& event) {
    const auto key = event.key;
#else
void Keyboard::handlePressed(const sf::Event::KeyEvent& event) {
    const auto key = event.code;
#endif
    const bool inserted = m_pressedKeys.insert(key).second;
    if (inserted) {
        m_justPressed.insert(key);
    }
}

#if SFML_VERSION_MAJOR >= 3
void Keyboard::handleReleased(const sf::Event::KeyReleased& event) {
    const auto key = event.key;
#else
void Keyboard::handleReleased(const sf::Event::KeyEvent& event) {
    const auto key = event.code;
#endif
    if (m_pressedKeys.erase(key) > 0) {
        m_justReleased.insert(key);
    }
}

bool Keyboard::isPressed(sf::Keyboard::Key key) const {
    return m_pressedKeys.find(key) != m_pressedKeys.end();
}

bool Keyboard::wasPressed(sf::Keyboard::Key key) const {
    return m_justPressed.find(key) != m_justPressed.end();
}

bool Keyboard::wasReleased(sf::Keyboard::Key key) const {
    return m_justReleased.find(key) != m_justReleased.end();
}

} // namespace CitySim::Input
