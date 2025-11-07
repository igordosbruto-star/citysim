#include "Graphics/Effects.hpp"
#include <cmath>
#include <random>

namespace CitySim {

Effects::Effects() {
    // Reservar espaço para evitar realocações
    m_particles.reserve(1000);
    m_effects.reserve(10);
}

void Effects::update(float deltaTime) {
    updateParticles(deltaTime);
    updateEffects(deltaTime);
}

void Effects::draw(sf::RenderTarget& target) {
    // Desenhar efeitos ativos
    for (const auto& effect : m_effects) {
        auto shape = effect.shape;
        float alpha = (effect.duration / effect.maxDuration) * 255.0f;
        shape.setFillColor(sf::Color(
            shape.getFillColor().r,
            shape.getFillColor().g,
            shape.getFillColor().b,
            static_cast<sf::Uint8>(alpha)
        ));
        target.draw(shape);
    }
    
    // Desenhar seleção
    if (m_selection) {
        target.draw(*m_selection);
    }
    
    // Desenhar partículas
    for (const auto& particle : m_particles) {
        sf::RectangleShape shape;
        shape.setPosition(particle.position);
        shape.setSize(sf::Vector2f(particle.scale, particle.scale));
        shape.setOrigin(particle.scale / 2.0f, particle.scale / 2.0f);
        
        float alpha = (particle.lifetime / particle.maxLifetime) * 255.0f;
        shape.setFillColor(sf::Color(
            particle.color.r,
            particle.color.g,
            particle.color.b,
            static_cast<sf::Uint8>(alpha)
        ));
        
        target.draw(shape);
    }
}

void Effects::addSelection(const sf::Vector2f& position, float size) {
    m_selection = std::make_unique<sf::RectangleShape>();
    m_selection->setPosition(position);
    m_selection->setSize(sf::Vector2f(size, size));
    m_selection->setFillColor(sf::Color(255, 255, 255, 50));
    m_selection->setOutlineColor(sf::Color(255, 255, 255, 200));
    m_selection->setOutlineThickness(2.0f);
}

void Effects::removeSelection() {
    m_selection.reset();
}

void Effects::addBuildEffect(const sf::Vector2f& position) {
    spawnParticles(position, 20, sf::Color(100, 255, 100), 100.0f);
    
    EffectInstance effect;
    effect.shape.setPosition(position);
    effect.shape.setSize(sf::Vector2f(32.0f, 32.0f));
    effect.shape.setFillColor(sf::Color(100, 255, 100, 100));
    effect.duration = 0.5f;
    effect.maxDuration = 0.5f;
    effect.type = EffectType::Build;
    
    m_effects.push_back(effect);
}

void Effects::addDemolishEffect(const sf::Vector2f& position) {
    spawnParticles(position, 30, sf::Color(255, 100, 100), 150.0f);
    
    EffectInstance effect;
    effect.shape.setPosition(position);
    effect.shape.setSize(sf::Vector2f(32.0f, 32.0f));
    effect.shape.setFillColor(sf::Color(255, 100, 100, 100));
    effect.duration = 0.5f;
    effect.maxDuration = 0.5f;
    effect.type = EffectType::Demolish;
    
    m_effects.push_back(effect);
}

void Effects::addErrorEffect(const sf::Vector2f& position) {
    spawnParticles(position, 10, sf::Color(255, 50, 50), 80.0f);
    
    EffectInstance effect;
    effect.shape.setPosition(position);
    effect.shape.setSize(sf::Vector2f(32.0f, 32.0f));
    effect.shape.setFillColor(sf::Color(255, 50, 50, 100));
    effect.duration = 0.3f;
    effect.maxDuration = 0.3f;
    effect.type = EffectType::Error;
    
    m_effects.push_back(effect);
}

void Effects::updateParticles(float deltaTime) {
    // Atualizar e remover partículas mortas
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(),
            [deltaTime](Particle& p) {
                p.position += p.velocity * deltaTime;
                p.lifetime -= deltaTime;
                p.scale -= deltaTime * 10.0f;
                return p.lifetime <= 0.0f || p.scale <= 0.0f;
            }
        ),
        m_particles.end()
    );
}

void Effects::updateEffects(float deltaTime) {
    // Atualizar e remover efeitos expirados
    m_effects.erase(
        std::remove_if(m_effects.begin(), m_effects.end(),
            [deltaTime](EffectInstance& e) {
                e.duration -= deltaTime;
                return e.duration <= 0.0f;
            }
        ),
        m_effects.end()
    );
}

void Effects::spawnParticles(const sf::Vector2f& position, int count,
                           const sf::Color& color, float speed) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> speedDist(0.5f, 1.0f);
    std::uniform_real_distribution<float> lifetimeDist(0.3f, 0.8f);
    std::uniform_real_distribution<float> scaleDist(2.0f, 6.0f);
    
    for (int i = 0; i < count; ++i) {
        Particle p;
        p.position = position;
        
        float angle = angleDist(gen);
        float particleSpeed = speed * speedDist(gen);
        p.velocity = sf::Vector2f(
            std::cos(angle) * particleSpeed,
            std::sin(angle) * particleSpeed
        );
        
        p.lifetime = lifetimeDist(gen);
        p.maxLifetime = p.lifetime;
        p.scale = scaleDist(gen);
        p.color = color;
        
        m_particles.push_back(p);
    }
}

} // namespace CitySim