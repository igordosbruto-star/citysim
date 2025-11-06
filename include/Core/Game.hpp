#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace CitySim {

// Gerenciador central da simulação. Responsável por coordenar
// sistemas de gameplay, simulação e renderização dentro do loop da
// Application. Mantém um ciclo de vida explícito para facilitar a
// integração de futuros subsistemas (ECS, UI, etc.).
class Game {
public:
    enum class State {
        Uninitialized,
        Running,
        Paused,
        Stopped
    };

    explicit Game(sf::RenderWindow& window);
    ~Game();

    bool initialize();
    void shutdown();

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render();

    void pause();
    void resume();

    bool isInitialized() const { return m_state != State::Uninitialized; }
    bool isPaused() const { return m_state == State::Paused; }
    State state() const { return m_state; }

    sf::RenderWindow& window() { return *m_window; }
    const sf::RenderWindow& window() const { return *m_window; }

private:
    void onWindowResized(const sf::Event::Resized& resizedEvent);
    void updateDebugVisual(float deltaTime);

private:
    sf::RenderWindow* m_window = nullptr; // Não possui, apenas observa
    State m_state = State::Uninitialized;
    sf::Clock m_simulationClock;

    // Placeholder visual até os sistemas de renderização ficarem prontos
    sf::RectangleShape m_debugShape;
    float m_debugShapeRotation = 0.0f;
    bool m_debugShapeInitialized = false;
};

} // namespace CitySim
