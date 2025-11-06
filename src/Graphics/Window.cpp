#include "Graphics/Window.hpp"

#include "Utils/Logger.hpp"

#include <SFML/Config.hpp>
// SFML 3 removed the old WindowStyle header; only include the legacy header for SFML 2.
#if SFML_VERSION_MAJOR < 3
#include <SFML/Window/WindowStyle.hpp>
#endif

#include <exception>

namespace CitySim::Graphics {

bool Window::create(const sf::VideoMode& videoMode, const std::string& title, sf::ContextSettings settings) {
    try {
#if SFML_VERSION_MAJOR >= 3
    // SFML 3: create(videoMode, title, State, settings)
    m_window.create(videoMode, title, sf::State::Windowed, settings);
#else
    m_window.create(videoMode, title, sf::Style::Default, settings);
#endif
        if (!m_window.isOpen()) {
            LOG_ERROR("Falha ao criar janela: janela não está aberta");
            return false;
        }
    } catch (const std::exception& e) {
        LOG_ERROR_F("Exceção ao criar janela: %s", e.what());
        return false;
    } catch (...) {
        LOG_ERROR("Exceção desconhecida ao criar janela");
        return false;
    }

    return true;
}

void Window::close() {
    if (m_window.isOpen()) {
        m_window.close();
    }
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

void Window::setFramerateLimit(unsigned int limit) {
    m_window.setFramerateLimit(limit);
}

void Window::setVerticalSyncEnabled(bool enabled) {
    m_window.setVerticalSyncEnabled(enabled);
}

void Window::setKeyRepeatEnabled(bool enabled) {
    m_window.setKeyRepeatEnabled(enabled);
}

std::optional<sf::Event> Window::pollEvent() {
#if SFML_VERSION_MAJOR >= 3
    return m_window.pollEvent();
#else
    sf::Event event;
    if (m_window.pollEvent(event)) {
        return event;
    }
    return std::nullopt;
#endif
}

sf::Vector2u Window::getSize() const {
    return m_window.getSize();
}

sf::RenderWindow& Window::nativeHandle() {
    return m_window;
}

const sf::RenderWindow& Window::nativeHandle() const {
    return m_window;
}

} // namespace CitySim::Graphics
