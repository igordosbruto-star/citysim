#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace CitySim::Graphics {

class Window;

class Renderer {
public:
    explicit Renderer(Window& window);

    void beginFrame(const sf::Color& clearColor);
    void endFrame();

    void draw(const sf::Drawable& drawable);

    void setView(const sf::View& view);
    const sf::View& getView() const;

    sf::RenderWindow& target();
    const sf::RenderWindow& target() const;

private:
    Window* m_window = nullptr;
};

} // namespace CitySim::Graphics
