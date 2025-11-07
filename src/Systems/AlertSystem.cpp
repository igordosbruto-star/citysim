#include <Core/Systems/AlertSystem.hpp>
#include <Core/Components/PowerGridComponent.hpp>
#include <Core/Components/WaterGridComponent.hpp>
#include <Core/Components/PollutionComponent.hpp>

namespace CitySim {

AlertSystem::AlertSystem(entt::registry& registry)
    : m_registry(registry) {
    loadTextures();
}

void AlertSystem::update(float dt) {
    // Verifica os diferentes tipos de alerta
    checkPowerAlerts();
    checkWaterAlerts();
    checkPollutionAlerts();

    // Atualiza alertas existentes
    for (auto it = m_alerts.begin(); it != m_alerts.end();) {
        updateAlertVisual(*it, dt);
        
        it->duration += dt;
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
    
    // Configura o sprite baseado no tipo
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
    
    // Centraliza o sprite na posição
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
    // TODO: Carregar as texturas reais quando tivermos os arquivos
    
    // Por enquanto, cria texturas temporárias de cores diferentes
    m_noPowerTexture.create(32, 32);
    m_noWaterTexture.create(32, 32);
    m_pollutionTexture.create(32, 32);
    
    std::vector<sf::Uint8> redPixels(32 * 32 * 4, 255);
    std::vector<sf::Uint8> bluePixels(32 * 32 * 4, 255);
    std::vector<sf::Uint8> greenPixels(32 * 32 * 4, 255);
    
    // Vermelho para falta de energia
    for (size_t i = 3; i < redPixels.size(); i += 4) {
        redPixels[i - 2] = 0;  // G
        redPixels[i - 1] = 0;  // B
    }
    
    // Azul para falta de água
    for (size_t i = 3; i < bluePixels.size(); i += 4) {
        bluePixels[i - 3] = 0;  // R
        bluePixels[i - 2] = 0;  // G
    }
    
    // Verde para poluição
    for (size_t i = 3; i < greenPixels.size(); i += 4) {
        greenPixels[i - 3] = 0;  // R
        greenPixels[i - 1] = 0;  // B
    }
    
    m_noPowerTexture.update(redPixels.data());
    m_noWaterTexture.update(bluePixels.data());
    m_pollutionTexture.update(greenPixels.data());
    
    return true;
}

void AlertSystem::checkPowerAlerts() {
    auto view = m_registry.view<PowerGridComponent>();
    for (auto entity : view) {
        const auto& power = view.get<PowerGridComponent>(entity);
        if (!power.hasPower && !power.isPowerPlant) {
            // TODO: Obter posição real da entidade quando tivermos o sistema de posicionamento
            sf::Vector2f position(0.0f, 0.0f);  // Posição temporária
            addAlert(AlertType::NoPower, position);
        }
    }
}

void AlertSystem::checkWaterAlerts() {
    auto view = m_registry.view<WaterGridComponent>();
    for (auto entity : view) {
        const auto& water = view.get<WaterGridComponent>(entity);
        if (!water.hasWater && !water.isWaterPlant) {
            // TODO: Obter posição real da entidade
            sf::Vector2f position(0.0f, 0.0f);  // Posição temporária
            addAlert(AlertType::NoWater, position);
        }
    }
}

void AlertSystem::checkPollutionAlerts() {
    auto view = m_registry.view<PollutionComponent>();
    for (auto entity : view) {
        const auto& pollution = view.get<PollutionComponent>(entity);
        if (pollution.pollutionLevel > 75.0f) {  // Limite arbitrário de poluição alta
            // TODO: Obter posição real da entidade
            sf::Vector2f position(0.0f, 0.0f);  // Posição temporária
            addAlert(AlertType::HighPollution, position);
        }
    }
}

void AlertSystem::updateAlertVisual(Alert& alert, float dt) {
    // Faz o ícone piscar
    float blinkPhase = std::fmod(alert.duration, ALERT_BLINK_RATE) / ALERT_BLINK_RATE;
    alert.isActive = blinkPhase < 0.5f;
    
    // Fade out no final da duração
    if (alert.duration > ALERT_DURATION - 1.0f) {
        float alpha = 255.0f * (1.0f - (alert.duration - (ALERT_DURATION - 1.0f)));
        sf::Color color = alert.sprite.getColor();
        color.a = static_cast<sf::Uint8>(alpha);
        alert.sprite.setColor(color);
    }
}

} // namespace CitySimulator