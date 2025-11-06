#include "Graphics/Renderer.hpp"

#include "Graphics/Window.hpp"

namespace CitySim::Graphics {

Renderer::Renderer(Window& window)
    : m_window(&window) {
}

void Renderer::beginFrame(const sf::Color& clearColor) {
    target().clear(clearColor);
}

void Renderer::endFrame() {
    target().display();
}

void Renderer::draw(const sf::Drawable& drawable) {
    target().draw(drawable);
}

void Renderer::setView(const sf::View& view) {
    target().setView(view);
}

const sf::View& Renderer::getView() const {
    return target().getView();
}

sf::RenderTarget& Renderer::target() {
    return m_window->nativeHandle();
}

const sf::RenderTarget& Renderer::target() const {
    return m_window->nativeHandle();
}

} // namespace CitySim::Graphics
