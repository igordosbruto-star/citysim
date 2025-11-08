#include "Core/Systems/AlertSystem.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/PollutionComponent.hpp"

namespace CitySim {

void AlertSystem::Update(float deltaTime) {
    auto& registry = *GetRegistry();
    
    // Verifica os diferentes tipos de alerta
    checkPowerAlerts();
    checkWaterAlerts();
    checkPollutionAlerts();

    // Atualiza alertas existentes
    for (auto it = m_alerts.begin(); it != m_alerts.end();) {
        updateAlertVisual(*it, deltaTime);
        
        it->duration += deltaTime;
        if (it->duration >= ALERT_DURATION) {
            it = m_alerts.erase(it);
        } else {
            ++it;
        }
    }
}

void AlertSystem::render(sf::RenderTarget& target) {
    for (const auto& alert : m_alerts) {
        if (alert.isActive) {
            target.draw(alert.sprite);
        }
    }
}

void AlertSystem::addAlert(AlertType type, const sf::Vector2f& position) {
    Alert alert(type, position);
    
    switch (type) {
        case AlertType::NoPower:
            alert.sprite.setTexture(m_noPowerTexture);
            break;
        case AlertType::NoWater:
            alert.sprite.setTexture(m_noWaterTexture);
            break;
        case AlertType::HighPollution:
            alert.sprite.setTexture(m_pollutionTexture);
            break;
    }
    
    sf::FloatRect bounds = alert.sprite.getLocalBounds();
    alert.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    alert.sprite.setPosition(position);
    
    m_alerts.push_back(alert);
}

void AlertSystem::clearAlerts() {
    m_alerts.clear();
}

size_t AlertSystem::getActiveAlertCount() const {
    return m_alerts.size();
}

bool AlertSystem::loadTextures() {
    // Carrega as texturas dos ícones de alerta
    m_noPowerTexture.create(32, 32);
    m_noWaterTexture.create(32, 32);
    m_pollutionTexture.create(32, 32);
    
    // ... (código de criação de texturas temporárias permanece o mesmo)
    
    return true;
}

void AlertSystem::checkPowerAlerts() {
    auto& registry = *GetRegistry();
    auto view = registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (!power.hasPower && !power.isPowerPlant) {
            // TODO: Obter posição real da entidade
            sf::Vector2f position(0.0f, 0.0f);
            addAlert(AlertType::NoPower, position);
        }
    }
}

void AlertSystem::checkWaterAlerts() {
    auto& registry = *GetRegistry();
    auto view = registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (!water.hasWater && !water.isWaterPlant) {
            sf::Vector2f position(0.0f, 0.0f);
            addAlert(AlertType::NoWater, position);
        }
    }
}

void AlertSystem::checkPollutionAlerts() {
    auto& registry = *GetRegistry();
    auto view = registry.view<PollutionComponent>();
    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        if (pollution.pollutionLevel > 75.0f) {
            sf::Vector2f position(0.0f, 0.0f);
            addAlert(AlertType::HighPollution, position);
        }
    }
}

void AlertSystem::updateAlertVisual(Alert& alert, float dt) {
    float blinkPhase = std::fmod(alert.duration, ALERT_BLINK_RATE) / ALERT_BLINK_RATE;
    alert.isActive = blinkPhase < 0.5f;
    
    if (alert.duration > ALERT_DURATION - 1.0f) {
        float alpha = 255.0f * (1.0f - (alert.duration - (ALERT_DURATION - 1.0f)));
        sf::Color color = alert.sprite.getColor();
        color.a = static_cast<sf::Uint8>(alpha);
        alert.sprite.setColor(color);
    }
}

} // namespace CitySim