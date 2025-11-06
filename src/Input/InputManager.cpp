#include "Input/InputManager.hpp"

#include "Graphics/Window.hpp"

#include <SFML/Config.hpp>

namespace CitySim::Input {

void InputManager::beginFrame() {
    m_keyboard.beginFrame();
    m_mouse.beginFrame();
}

void InputManager::processEvents(Graphics::Window& window, const std::function<void(const sf::Event&)>& callback) {
    while (auto eventOpt = window.pollEvent()) {
#if SFML_VERSION_MAJOR >= 3
        if (const auto* keyPressed = eventOpt->getIf<sf::Event::KeyPressed>()) {
            m_keyboard.handlePressed(*keyPressed);
        } else if (const auto* keyReleased = eventOpt->getIf<sf::Event::KeyReleased>()) {
            m_keyboard.handleReleased(*keyReleased);
        } else if (const auto* mousePressed = eventOpt->getIf<sf::Event::MouseButtonPressed>()) {
            m_mouse.handleButtonPressed(*mousePressed);
        } else if (const auto* mouseReleased = eventOpt->getIf<sf::Event::MouseButtonReleased>()) {
            m_mouse.handleButtonReleased(*mouseReleased);
        } else if (const auto* mouseMoved = eventOpt->getIf<sf::Event::MouseMoved>()) {
            m_mouse.handleMoved(*mouseMoved);
        } else if (const auto* wheelScrolled = eventOpt->getIf<sf::Event::MouseWheelScrolled>()) {
            m_mouse.handleWheelScrolled(*wheelScrolled);
        }

        if (callback) {
            callback(*eventOpt);
        }
#else
        const sf::Event& event = *eventOpt;

        switch (event.type) {
        case sf::Event::KeyPressed:
            m_keyboard.handlePressed(event.key);
            break;
        case sf::Event::KeyReleased:
            m_keyboard.handleReleased(event.key);
            break;
        case sf::Event::MouseButtonPressed:
            m_mouse.handleButtonPressed(event.mouseButton);
            break;
        case sf::Event::MouseButtonReleased:
            m_mouse.handleButtonReleased(event.mouseButton);
            break;
        case sf::Event::MouseMoved:
            m_mouse.handleMoved(event.mouseMove);
            break;
        case sf::Event::MouseWheelScrolled:
            m_mouse.handleWheelScrolled(event.mouseWheelScroll);
            break;
        default:
            break;
        }

        if (callback) {
            callback(event);
        }
#endif
    }
}

} // namespace CitySim::Input
