#include "Graphics/Window.hpp"

#include "Utils/Logger.hpp"

#include <SFML/Window/ContextSettings.hpp>

#include <exception>

namespace CitySim::Graphics {

bool Window::create(const sf::VideoMode& videoMode, const std::string& title, const sf::ContextSettings& settings) {
    try {
        m_window.create(videoMode, title, settings);
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
    return m_window.pollEvent();
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
