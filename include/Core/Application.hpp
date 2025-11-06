#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Config.hpp"

namespace CitySim {

class Game;

class Application {
public:
    static Application& getInstance();

    bool initialize();
    void shutdown();
    void run(Game& game);
    void quit() { m_isRunning = false; }

    sf::RenderWindow& getWindow() { return m_window; }
    bool isRunning() const { return m_isRunning; }

private:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    void handleEvents(Game& game);
    void update(Game& game, float deltaTime);
    void render(Game& game);

private:
    sf::RenderWindow m_window;
    float m_targetFrameTime = 1.0f / 60.0f;
    bool m_isInitialized = false;
    bool m_isRunning = false;
};

} // namespace CitySim
