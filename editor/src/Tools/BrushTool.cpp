#include "Tools/BrushTool.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace CitySim::Editor {

BrushTool::BrushTool()
    : m_size(32.0f)
    , m_drawing(false) {
    m_preview.setFillColor(sf::Color(255, 255, 255, 50));
    m_preview.setOutlineColor(sf::Color(255, 255, 255, 200));
    m_preview.setOutlineThickness(2.0f);
    m_preview.setSize(sf::Vector2f(m_size, m_size));
}

void BrushTool::onMouseDown(const sf::Vector2i& position) {
    if (!m_active) return;
    
    m_drawing = true;
    m_lastPos = position;
    applyBrush(position);
}

void BrushTool::onMouseMove(const sf::Vector2i& position) {
    if (!m_active) return;
    
    updatePreview(position);
    
    if (m_drawing) {
        if (position != m_lastPos) {
            applyBrush(position);
            m_lastPos = position;
        }
    }
}

void BrushTool::onMouseUp(const sf::Vector2i& position) {
    if (!m_active) return;
    
    if (m_drawing) {
        applyBrush(position);
        m_drawing = false;
    }
}

void BrushTool::draw(sf::RenderTarget& target) {
    if (m_active) {
        target.draw(m_preview);
    }
}

void BrushTool::setSize(float size) {
    m_size = size;
    m_preview.setSize(sf::Vector2f(m_size, m_size));
}

void BrushTool::setColor(const sf::Color& color) {
    m_preview.setFillColor(sf::Color(color.r, color.g, color.b, 50));
    m_preview.setOutlineColor(sf::Color(color.r, color.g, color.b, 200));
}

void BrushTool::applyBrush(const sf::Vector2i& position) {
    // TODO: Implementar pintura de tiles com o tipo selecionado
}

void BrushTool::updatePreview(const sf::Vector2i& position) {
    m_preview.setPosition(sf::Vector2f(
        static_cast<float>(position.x - m_size / 2),
        static_cast<float>(position.y - m_size / 2)
    ));
}

} // namespace CitySim::Editor