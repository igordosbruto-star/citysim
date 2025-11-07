#include "ui/BuildUI.hpp"
#include "Input/InputManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace CitySim {

BuildUI::BuildUI()
    : m_selectedTool(BuildTool::None) {
    initializeButtons();
}

void BuildUI::initializeButtons() {
    const float buttonSize = 50.0f;
    const float buttonGap = 10.0f;
    const float buttonY = 10.0f;
    float currentX = 10.0f;
    
    // Configurar cada botão
    for (int i = 0; i < 5; i++) {
        m_buttons[i].setSize(sf::Vector2f(buttonSize, buttonSize));
        m_buttons[i].setPosition(currentX, buttonY);
        m_buttons[i].setOutlineThickness(2.0f);
        
        // Cores diferentes para cada ferramenta
        switch (static_cast<BuildTool>(i)) {
            case BuildTool::Residential:
                m_buttons[i].setFillColor(sf::Color(100, 200, 100));  // Verde
                break;
            case BuildTool::Commercial:
                m_buttons[i].setFillColor(sf::Color(100, 100, 200));  // Azul
                break;
            case BuildTool::Industrial:
                m_buttons[i].setFillColor(sf::Color(200, 100, 100));  // Vermelho
                break;
            case BuildTool::Demolish:
                m_buttons[i].setFillColor(sf::Color(150, 150, 150));  // Cinza
                break;
            default:
                m_buttons[i].setFillColor(sf::Color(200, 200, 200));  // Cinza claro
                break;
        }
        
        currentX += buttonSize + buttonGap;
    }
}

void BuildUI::update() {
    updateButtonStates();
}

void BuildUI::draw(sf::RenderTarget& target) {
    // Desenhar cada botão
    for (int i = 0; i < 5; i++) {
        const auto tool = static_cast<BuildTool>(i);
        
        // Ajustar visual do botão baseado no estado
        if (m_selectedTool == tool) {
            m_buttons[i].setOutlineColor(sf::Color::Yellow);
        }
        else if (isMouseOverButton(tool)) {
            m_buttons[i].setOutlineColor(sf::Color::White);
        }
        else {
            m_buttons[i].setOutlineColor(sf::Color(100, 100, 100));
        }
        
        target.draw(m_buttons[i]);
    }
}

void BuildUI::setSelectedTool(BuildTool tool) {
    m_selectedTool = tool;
}

bool BuildUI::isButtonPressed(BuildTool tool) const {
    const int index = static_cast<int>(tool);
    if (index >= 0 && index < 5) {
        return InputManager::isMouseButtonPressed(sf::Mouse::Left) &&
               isMouseOverButton(tool);
    }
    return false;
}

bool BuildUI::isMouseOverButton(BuildTool tool) const {
    const int index = static_cast<int>(tool);
    if (index >= 0 && index < 5) {
        const auto mousePos = InputManager::getMousePosition();
        const auto& button = m_buttons[index];
        const auto buttonBounds = sf::FloatRect(
            button.getPosition(),
            button.getSize()
        );
        return buttonBounds.contains(static_cast<float>(mousePos.x),
                                   static_cast<float>(mousePos.y));
    }
    return false;
}

void BuildUI::updateButtonStates() {
    // Verificar cliques nos botões
    for (int i = 0; i < 5; i++) {
        const auto tool = static_cast<BuildTool>(i);
        if (isButtonPressed(tool)) {
            setSelectedTool(tool);
            break;
        }
    }
}

} // namespace CitySim