#include "Input/InputManager.hpp"

#include "Graphics/Window.hpp"

namespace CitySim::Input {

void InputManager::beginFrame() {
    m_keyboard.beginFrame();
    m_mouse.beginFrame();
}

void InputManager::processEvents(Graphics::Window& window, const std::function<void(const sf::Event&)>& callback) {
    while (auto event = window.pollEvent()) {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            m_keyboard.handleEvent(*keyPressed);
        } else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            m_keyboard.handleEvent(*keyReleased);
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            m_mouse.handleEvent(*mousePressed);
        } else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            m_mouse.handleEvent(*mouseReleased);
        } else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            m_mouse.handleEvent(*mouseMoved);
        } else if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
            m_mouse.handleEvent(*wheelScrolled);
        }

        if (callback) {
            callback(*event);
        }
    }
}

} // namespace CitySim::Input
