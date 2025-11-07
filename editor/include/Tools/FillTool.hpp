#pragma once

#include "Tool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace CitySim::Editor {

class FillTool : public Tool {
public:
    FillTool();
    
    void onMouseDown(const sf::Vector2i& position) override;
    void onMouseMove(const sf::Vector2i& position) override;
    void onMouseUp(const sf::Vector2i& position) override;
    
    void draw(sf::RenderTarget& target) override;
    std::string getName() const override { return "Fill"; }
    std::string getDescription() const override { return "Fill connected area with selected type"; }
    
    void setColor(const sf::Color& color);
    
private:
    sf::RectangleShape m_preview;
    bool m_filling;
    
    void fill(const sf::Vector2i& startPos);
    void updatePreview(const sf::Vector2i& position);
};

} // namespace CitySim::Editor