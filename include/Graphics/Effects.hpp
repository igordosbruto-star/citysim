#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

namespace CitySim {

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
    float maxLifetime;
    float scale;
    sf::Color color;
};

enum class EffectType {
    None,
    Select,      // Seleção de tile
    Build,       // Construção
    Demolish,    // Demolição
    Error        // Erro (não pode construir)
};

class Effects {
public:
    Effects();
    
    void update(float deltaTime);
    void draw(sf::RenderTarget& target);
    
    // Efeitos principais
    void addSelection(const sf::Vector2f& position, float size);
    void removeSelection();
    void addBuildEffect(const sf::Vector2f& position);
    void addDemolishEffect(const sf::Vector2f& position);
    void addErrorEffect(const sf::Vector2f& position);
    
private:
    struct EffectInstance {
        sf::RectangleShape shape;
        float duration;
        float maxDuration;
        EffectType type;
    };
    
    std::vector<Particle> m_particles;
    std::vector<EffectInstance> m_effects;
    std::unique_ptr<sf::RectangleShape> m_selection;
    
    // Funções auxiliares
    void updateParticles(float deltaTime);
    void updateEffects(float deltaTime);
    void spawnParticles(const sf::Vector2f& position, int count, 
                       const sf::Color& color, float speed);
};

} // namespace CitySim