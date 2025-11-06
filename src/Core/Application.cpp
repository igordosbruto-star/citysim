#include "Core/Application.hpp"
#include "Utils/Logger.hpp"

namespace CitySim {

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    // Evitar inicialização múltipla
    if (m_isInitialized) {
        LOG_WARNING("Application já está inicializada");
        return true;
    }
    
    LOG_INFO("Inicializando Application...");
    
    // Configuração da janela
    sf::VideoMode videoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;
    
    m_window.create(videoMode, "City Simulator", sf::Style::Close, contextSettings);
    m_window.setFramerateLimit(Config::TARGET_FPS);
    m_window.setKeyRepeatEnabled(false);
    
    // Inicializar subsistemas na ordem correta
    if (!m_renderer.initialize(m_window)) {
        LOG_ERROR("Falha ao inicializar Renderer");
        return false;
    }
    
    if (!m_inputManager.initialize()) {
        LOG_ERROR("Falha ao inicializar InputManager");
        return false;
    }
    
    // Inicializar o mundo ECS
    m_world.initialize();
    
    // Configurar tempo de frame
    m_targetFrameTime = 1.0f / Config::TARGET_FPS;
    
    m_isInitialized = true;
    m_isRunning = true;
    
    LOG_INFO("Application inicializada com sucesso");
    return true;
}

void Application::shutdown() {
    if (!m_isInitialized) return;
    
    LOG_INFO("Encerrando Application...");
    
    // Ordem reversa de inicialização
    m_world.shutdown();
    m_inputManager.shutdown();
    m_renderer.shutdown();
    
    if (m_window.isOpen()) {
        m_window.close();
    }
    
    m_isInitialized = false;
    m_isRunning = false;
    
    LOG_INFO("Application encerrada");
}

void Application::run() {
    if (!m_isInitialized) {
        LOG_ERROR("Application não inicializada. Chamando run() antes de initialize()");
        return;
    }
    
    LOG_INFO("Iniciando loop principal...");
    
    sf::Clock frameClock;
    
    while (m_isRunning && m_window.isOpen()) {
        float deltaTime = frameClock.restart().asSeconds();
        
        // Processar eventos
        handleEvents();
        
        // Atualizar lógica do jogo
        update(deltaTime);
        
        // Renderizar frame
        render();
        
        // Controle de FPS (se necessário)
        // sf::sleep(sf::seconds(m_targetFrameTime - deltaTime));
    }
}

void Application::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        // Passar evento para o InputManager
        m_inputManager.handleEvent(event);
        
        switch (event.type) {
            case sf::Event::Closed:
                quit();
                break;
                
            case sf::Event::Resized:
                // Atualizar viewport do renderizador
                m_renderer.handleResize(event.size.width, event.size.height);
                break;
                
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    quit();
                }
                break;
                
            default:
                break;
        }
    }
}

void Application::update(float deltaTime) {
    // Atualizar input
    m_inputManager.update();
    
    // Atualizar mundo ECS
    m_world.update(deltaTime);
    
    // Aqui futuramente atualizaremos:
    // - Sistema de física
    // - IA dos cidadãos
    // - Economia da cidade
    // - etc.
}

void Application::render() {
    m_window.clear(sf::Color(30, 30, 45)); // Cor de fundo escura
    
    // Renderizar através do nosso sistema de renderização
    m_renderer.beginFrame();
    
    // Renderizar o mundo ECS
    m_world.render(m_renderer);
    
    m_renderer.endFrame();
    
    m_window.display();
}

} // namespace CitySim