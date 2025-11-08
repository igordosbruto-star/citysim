#pragma once

#include "ECS/System.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace CitySim {

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

class AlertSystem : public System {
public:
    AlertSystem() = default;
    
    bool Init(entt::registry& registry) override {
        System::Init(registry);
        loadTextures();
        return true;
    }
    
    void Update(float deltaTime) override;
    
    std::string GetName() const override { return "AlertSystem"; }

    // Renderiza os alertas
    void render(sf::RenderTarget& target);
    
    // Adiciona um novo alerta
    void addAlert(AlertType type, const sf::Vector2f& position);
    
    // Remove todos os alertas
    void clearAlerts();
    
    // Retorna o número de alertas ativos
    size_t getActiveAlertCount() const;

private:
    std::vector<Alert> m_alerts;
    
    sf::Texture m_noPowerTexture;
    sf::Texture m_noWaterTexture;
    sf::Texture m_pollutionTexture;
    
    static constexpr float ALERT_DURATION = 5.0f;
    static constexpr float ALERT_BLINK_RATE = 0.5f;
    
    // Verifica a necessidade de alertas
    void checkPowerAlerts();
    void checkWaterAlerts();
    void checkPollutionAlerts();
    
    // Atualiza a visualização de um alerta
    void updateAlertVisual(Alert& alert, float dt);
    
    // Carrega as texturas dos ícones
    bool loadTextures();
};

} // namespace CitySim