#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <entt/entt.hpp>

#include "ECS/World.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/TransformSystem.hpp"
#include "Systems/PowerSystem.hpp"
#include "Systems/WaterSystem.hpp"
#include "Systems/GarbageSystem.hpp"
#include "Systems/PollutionSystem.hpp"
#include "Systems/AlertSystem.hpp"
#include "Systems/OverlaySystem.hpp"
#include "Graphics/Tilemap.hpp"

namespace CitySim {

namespace Graphics {
class Renderer;
class Window;
}

namespace Input {
class InputManager;
}

class Game {
public:
    enum class State {
        Uninitialized,
        Running,
        Paused,
        Stopped
    };

    Game(Graphics::Window& window, Graphics::Renderer& renderer, Input::InputManager& inputManager);
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

    Graphics::Window& window() { return *m_window; }
    const Graphics::Window& window() const { return *m_window; }

    entt::registry& getRegistry() { return m_registry; }
    const entt::registry& getRegistry() const { return m_registry; }

private:
#if SFML_VERSION_MAJOR >= 3
    void onWindowResized(const sf::Event::Resized& resizedEvent);
#else
    void onWindowResized(const sf::Event::SizeEvent& resizedEvent);
#endif
    void updateDebugVisual(float deltaTime);
    
    // Funções de inicialização
    bool initializeECS();
    bool initializeTilemap();
    void setupDebugVisual();
    void togglePause();

    // Funções de renderização específicas
    void renderECS();
    void renderNonECS();

private:
    Graphics::Window* m_window = nullptr;
    Graphics::Renderer* m_renderer = nullptr;
    Input::InputManager* m_inputManager = nullptr;
    State m_state = State::Uninitialized;
    sf::Clock m_simulationClock;
    entt::registry m_registry;
    World m_world;

    // Sistemas ECS
    RenderSystem* m_renderSystem = nullptr;
    TransformSystem* m_transformSystem = nullptr;
    PowerSystem* m_powerSystem = nullptr;
    WaterSystem* m_waterSystem = nullptr;
    GarbageSystem* m_garbageSystem = nullptr;
    PollutionSystem* m_pollutionSystem = nullptr;
    AlertSystem* m_alertSystem = nullptr;
    OverlaySystem* m_overlaySystem = nullptr;

    // Tilemap (não-ECS por enquanto)
    std::unique_ptr<Tilemap> m_tilemap;

    // Debug visual
    sf::RectangleShape m_debugShape;
    float m_debugShapeRotation = 0.0f;
    bool m_debugShapeInitialized = false;
};

} // namespace CitySim