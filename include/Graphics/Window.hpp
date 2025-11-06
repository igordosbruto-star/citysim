#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <optional>
#include <string>

namespace CitySim::Graphics {

class Window {
public:
    Window() = default;

    bool create(const sf::VideoMode& videoMode, const std::string& title, const sf::ContextSettings& settings = {});
    void close();

    bool isOpen() const;

    void setFramerateLimit(unsigned int limit);
    void setVerticalSyncEnabled(bool enabled);
    void setKeyRepeatEnabled(bool enabled);

    std::optional<sf::Event> pollEvent();

    sf::Vector2u getSize() const;

    sf::RenderWindow& nativeHandle();
    const sf::RenderWindow& nativeHandle() const;

private:
    sf::RenderWindow m_window;
};

} // namespace CitySim::Graphics
