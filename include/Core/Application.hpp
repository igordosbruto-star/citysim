#pragma once

#include "Core/Config.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"
#include "Input/InputManager.hpp"

#include <memory>

namespace CitySim {

class Game;

class Application {
public:
    static Application& getInstance();

    bool initialize();
    void shutdown();
    void run(Game& game);
    void quit() { m_isRunning = false; }

    Graphics::Window& window() { return m_window; }
    Graphics::Renderer& renderer() { return *m_renderer; }
    Graphics::Camera& camera() { return *m_camera; }
    Input::InputManager& input() { return m_inputManager; }
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
    Graphics::Window m_window;
    std::unique_ptr<Graphics::Renderer> m_renderer;
    std::unique_ptr<Graphics::Camera> m_camera;
    Input::InputManager m_inputManager;
    float m_targetFrameTime = 1.0f / 60.0f;
    bool m_isInitialized = false;
    bool m_isRunning = false;
};

} // namespace CitySim
