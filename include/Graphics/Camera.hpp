#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace CitySim::Graphics {

class Renderer;
class Window;

class Camera {
public:
    explicit Camera(Window& window);

    void setCenter(const sf::Vector2f& center);
    void move(const sf::Vector2f& offset);
    void setSize(const sf::Vector2f& size);
    void zoom(float factor);

    void resize(const sf::Vector2u& size);

    void apply(Renderer& renderer) const;

    const sf::View& view() const { return m_view; }

private:
    sf::View m_view;
};

} // namespace CitySim::Graphics
