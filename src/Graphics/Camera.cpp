#include "Graphics/Camera.hpp"

#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"

namespace CitySim::Graphics {

namespace {
    sf::Vector2f toVector2f(const sf::Vector2u& value) {
        return sf::Vector2f(static_cast<float>(value.x), static_cast<float>(value.y));
    }
}

Camera::Camera(Window& window) {
    resize(window.getSize());
}

void Camera::setCenter(const sf::Vector2f& center) {
    m_view.setCenter(center);
}

void Camera::move(const sf::Vector2f& offset) {
    m_view.move(offset);
}

void Camera::setSize(const sf::Vector2f& size) {
    m_view.setSize(size);
}

void Camera::zoom(float factor) {
    m_view.zoom(factor);
}

void Camera::resize(const sf::Vector2u& size) {
    const sf::Vector2f sizeF = toVector2f(size);
    m_view.setSize(sizeF);
    m_view.setCenter(sizeF * 0.5f);
}

void Camera::apply(Renderer& renderer) const {
    renderer.setView(m_view);
}

} // namespace CitySim::Graphics
