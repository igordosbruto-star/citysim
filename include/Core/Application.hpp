#pragma once

// Includes essenciais do SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// Nossos includes
#include "Core/Config.hpp"
#include "Input/InputManager.hpp"
#include "Graphics/Renderer.hpp"
#include "ECS/World.hpp"
namespace CitySim {

class Application {
public:
    // Padrão Singleton - acesso global à instância
    static Application& getInstance();
    
    // Delete cópias para evitar múltiplas instâncias
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    // Inicialização e limpeza
    bool initialize();
    void shutdown();
    
    // Loop principal
    void run();
    
    // Gerenciamento de estado
    bool isRunning() const { return m_isRunning; }
    void quit() { m_isRunning = false; }
    
    // Acesso aos subsistemas
    sf::RenderWindow& getWindow() { return m_window; }
    InputManager& getInputManager() { return m_inputManager; }
    Renderer& getRenderer() { return m_renderer; }
    ECS::World& getWorld() { return m_world; }

private:
    // Construtor privado (Singleton)
    Application() = default;
    
    // Métodos internos do loop
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    // Subsistemas
    sf::RenderWindow m_window;
    InputManager m_inputManager;
    Renderer m_renderer;
    ECS::World m_world;
    
    // Controle de tempo
    sf::Clock m_clock;
    float m_targetFrameTime;
    
    // Estado da aplicação
    bool m_isRunning = false;
    bool m_isInitialized = false;
};

} // namespace CitySim