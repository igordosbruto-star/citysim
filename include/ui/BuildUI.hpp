#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace CitySim {

enum class BuildTool {
    None,
    Residential,
    Commercial,
    Industrial,
    Demolish
};

class BuildUI {
public:
    BuildUI();
    
    void update();
    void draw(sf::RenderTarget& target);
    
    BuildTool getSelectedTool() const { return m_selectedTool; }
    void setSelectedTool(BuildTool tool);
    
    bool isButtonPressed(BuildTool tool) const;
    bool isMouseOverButton(BuildTool tool) const;
    
private:
    BuildTool m_selectedTool;
    sf::RectangleShape m_buttons[5];  // 4 ferramentas + None
    
    void initializeButtons();
    sf::Vector2f getButtonPosition(BuildTool tool) const;
    void updateButtonStates();
};

} // namespace CitySim