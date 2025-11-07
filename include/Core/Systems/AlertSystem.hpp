#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <string>
#include <vector>
#include <memory>

namespace CitySimulator {

enum class AlertType {
    NoPower,
    NoWater,
    HighPollution
};

struct Alert {
    AlertType type;
    sf::Vector2f position;
    float duration;
    bool isActive;
    sf::Sprite sprite;

    Alert(AlertType t, const sf::Vector2f& pos)
        : type(t), position(pos), duration(0.0f), isActive(true) {}
};

class AlertSystem {
public:
    explicit AlertSystem(entt::registry& registry);

    void update(float dt);
    void render(sf::RenderTarget& target);
    
    // Adiciona um novo alerta
    void addAlert(AlertType type, const sf::Vector2f& position);
    
    // Remove todos os alertas
    void clearAlerts();
    
    // Retorna o número de alertas ativos
    size_t getActiveAlertCount() const;
    
    // Carrega as texturas dos ícones
    bool loadTextures();

private:
    entt::registry& m_registry;
    std::vector<Alert> m_alerts;
    
    sf::Texture m_noPowerTexture;
    sf::Texture m_noWaterTexture;
    sf::Texture m_pollutionTexture;
    
    static constexpr float ALERT_DURATION = 5.0f;  // Duração de cada alerta em segundos
    static constexpr float ALERT_BLINK_RATE = 0.5f; // Taxa de piscada em segundos
    
    // Verifica a necessidade de alertas
    void checkPowerAlerts();
    void checkWaterAlerts();
    void checkPollutionAlerts();
    
    // Atualiza a visualização de um alerta
    void updateAlertVisual(Alert& alert, float dt);
};

} // namespace CitySimulator