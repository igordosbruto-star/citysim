#include "Tools/EraserTool.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace CitySim::Editor {

EraserTool::EraserTool()
    : m_size(32.0f)
    , m_erasing(false) {
    m_preview.setFillColor(sf::Color(255, 0, 0, 50));
    m_preview.setOutlineColor(sf::Color(255, 0, 0, 200));
    m_preview.setOutlineThickness(2.0f);
    m_preview.setSize(sf::Vector2f(m_size, m_size));
}

void EraserTool::onMouseDown(const sf::Vector2i& position) {
    if (!m_active) return;
    
    m_erasing = true;
    m_lastPos = position;
    applyEraser(position);
}

void EraserTool::onMouseMove(const sf::Vector2i& position) {
    if (!m_active) return;
    
    updatePreview(position);
    
    if (m_erasing) {
        if (position != m_lastPos) {
            applyEraser(position);
            m_lastPos = position;
        }
    }
}

void EraserTool::onMouseUp(const sf::Vector2i& position) {
    if (!m_active) return;
    
    if (m_erasing) {
        applyEraser(position);
        m_erasing = false;
    }
}

void EraserTool::draw(sf::RenderTarget& target) {
    if (m_active) {
        target.draw(m_preview);
    }
}

void EraserTool::setSize(float size) {
    m_size = size;
    m_preview.setSize(sf::Vector2f(m_size, m_size));
}

void EraserTool::applyEraser(const sf::Vector2i& position) {
    // TODO: Implementar remoção de tiles
}

void EraserTool::updatePreview(const sf::Vector2i& position) {
    m_preview.setPosition(sf::Vector2f(
        static_cast<float>(position.x - m_size / 2),
        static_cast<float>(position.y - m_size / 2)
    ));
}

} // namespace CitySim::Editor