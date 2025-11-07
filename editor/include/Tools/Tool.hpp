#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

namespace CitySim::Editor {

class Tool {
public:
    virtual ~Tool() = default;
    
    // Interface principal da ferramenta
    virtual void onMouseDown(const sf::Vector2i& position) = 0;
    virtual void onMouseMove(const sf::Vector2i& position) = 0;
    virtual void onMouseUp(const sf::Vector2i& position) = 0;
    
    // Funções auxiliares
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    // Estado
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }
    
protected:
    bool m_active = false;
};

} // namespace CitySim::Editor