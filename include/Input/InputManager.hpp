#pragma once

#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"

#include <functional>

namespace sf {
class Event;
}

namespace CitySim::Graphics {
class Window;
}

namespace CitySim::Input {

class InputManager {
public:
    void beginFrame();

    void processEvents(Graphics::Window& window, const std::function<void(const sf::Event&)>& callback);

    Keyboard& keyboard() { return m_keyboard; }
    const Keyboard& keyboard() const { return m_keyboard; }

    Mouse& mouse() { return m_mouse; }
    const Mouse& mouse() const { return m_mouse; }

private:
    Keyboard m_keyboard;
    Mouse m_mouse;
};

} // namespace CitySim::Input
