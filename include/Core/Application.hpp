#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Config.hpp"

namespace CitySim {

class Application {
public:
    static Application& getInstance();
    
    bool initialize();
    void shutdown();
    void run();
    void quit() { m_isRunning = false; }
    
    sf::RenderWindow& getWindow() { return m_window; }
    bool isRunning() const { return m_isRunning; }

private:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    void handleEvents();
    void update(float deltaTime);
    void render();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_targetFrameTime = 1.0f / 60.0f;
    bool m_isInitialized = false;
    bool m_isRunning = false;
};

} // namespace CitySim