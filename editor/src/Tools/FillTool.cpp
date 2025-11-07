#include "Tools/FillTool.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <queue>
#include <set>

namespace CitySim::Editor {

FillTool::FillTool()
    : m_filling(false) {
    m_preview.setFillColor(sf::Color(255, 255, 255, 50));
    m_preview.setOutlineColor(sf::Color(255, 255, 255, 200));
    m_preview.setOutlineThickness(2.0f);
    m_preview.setSize(sf::Vector2f(32.0f, 32.0f));
}

void FillTool::onMouseDown(const sf::Vector2i& position) {
    if (!m_active) return;
    
    m_filling = true;
    fill(position);
}

void FillTool::onMouseMove(const sf::Vector2i& position) {
    if (!m_active) return;
    
    updatePreview(position);
}

void FillTool::onMouseUp(const sf::Vector2i& position) {
    if (!m_active) return;
    
    if (m_filling) {
        m_filling = false;
    }
}

void FillTool::draw(sf::RenderTarget& target) {
    if (m_active) {
        target.draw(m_preview);
    }
}

void FillTool::setColor(const sf::Color& color) {
    m_preview.setFillColor(sf::Color(color.r, color.g, color.b, 50));
    m_preview.setOutlineColor(sf::Color(color.r, color.g, color.b, 200));
}

void FillTool::fill(const sf::Vector2i& startPos) {
    // TODO: Implementar flood fill para preencher área conectada
    // Usar std::queue para BFS e std::set para rastrear tiles visitados
}

void FillTool::updatePreview(const sf::Vector2i& position) {
    m_preview.setPosition(sf::Vector2f(
        static_cast<float>(position.x - 16.0f),
        static_cast<float>(position.y - 16.0f)
    ));
}

} // namespace CitySim::Editor