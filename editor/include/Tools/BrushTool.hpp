#pragma once

#include "Tool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace CitySim::Editor {

class BrushTool : public Tool {
public:
    BrushTool();
    
    void onMouseDown(const sf::Vector2i& position) override;
    void onMouseMove(const sf::Vector2i& position) override;
    void onMouseUp(const sf::Vector2i& position) override;
    
    void draw(sf::RenderTarget& target) override;
    std::string getName() const override { return "Brush"; }
    std::string getDescription() const override { return "Paint tiles with selected type"; }
    
    void setSize(float size);
    void setColor(const sf::Color& color);
    
private:
    sf::RectangleShape m_preview;
    float m_size;
    bool m_drawing;
    sf::Vector2i m_lastPos;
    
    void applyBrush(const sf::Vector2i& position);
    void updatePreview(const sf::Vector2i& position);
};

} // namespace CitySim::Editor