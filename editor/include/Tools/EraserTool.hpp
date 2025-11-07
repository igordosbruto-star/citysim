#pragma once

#include "Tool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace CitySim::Editor {

class EraserTool : public Tool {
public:
    EraserTool();
    
    void onMouseDown(const sf::Vector2i& position) override;
    void onMouseMove(const sf::Vector2i& position) override;
    void onMouseUp(const sf::Vector2i& position) override;
    
    void draw(sf::RenderTarget& target) override;
    std::string getName() const override { return "Eraser"; }
    std::string getDescription() const override { return "Erase tiles"; }
    
    void setSize(float size);
    
private:
    sf::RectangleShape m_preview;
    float m_size;
    bool m_erasing;
    sf::Vector2i m_lastPos;
    
    void applyEraser(const sf::Vector2i& position);
    void updatePreview(const sf::Vector2i& position);
};

} // namespace CitySim::Editor