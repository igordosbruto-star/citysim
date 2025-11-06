#include "Core/Application.hpp"
#include "Utils/Logger.hpp"
#include <thread>
#include <SFML/Graphics/RectangleShape.hpp>
#include <optional>

namespace CitySim {

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    Logger::getInstance().initialize("city_simulator.log");
    
    if (m_isInitialized) {
        LOG_WARNING("Application já está inicializada");
        return true;
    }
    
    LOG_INFO("Inicializando Application...");
    
    // ✅ SFML 3: VideoMode com sf::Vector2u
    sf::VideoMode videoMode(sf::Vector2u(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    
    // ✅ SFML 3: ContextSettings
    sf::ContextSettings contextSettings;
    
    // ✅ SFML 3: Window creation - create() retorna void, não bool
    try {
        m_window.create(videoMode, "City Simulator");
        
        // Verifica se a janela foi criada com sucesso
        if (!m_window.isOpen()) {
            LOG_ERROR("Falha ao criar a janela - janela não está aberta");
            return false;
        }
        
        m_window.setFramerateLimit(Config::TARGET_FPS);
        m_window.setKeyRepeatEnabled(false);
        m_window.setVerticalSyncEnabled(Config::VSYNC_ENABLED);
        
    } catch (const std::exception& e) {
        LOG_ERROR_F("Exceção ao criar janela: %s", e.what());
        return false;
    } catch (...) {
        LOG_ERROR("Exceção desconhecida ao criar janela");
        return false;
    }
    
    m_targetFrameTime = 1.0f / Config::TARGET_FPS;
    m_isInitialized = true;
    m_isRunning = true;
    
    LOG_INFO("Application inicializada com sucesso");
    return true;
}

void Application::shutdown() {
    if (!m_isInitialized) return;
    
    LOG_INFO("Encerrando Application...");
    
    if (m_window.isOpen()) {
        m_window.close();
    }
    
    m_isInitialized = false;
    m_isRunning = false;
    
    LOG_INFO("Application encerrada");
    Logger::getInstance().shutdown();
}

void Application::run() {
    if (!m_isInitialized) {
        LOG_ERROR("Application não inicializada");
        return;
    }
    
    LOG_INFO("Iniciando loop principal...");
    
    sf::Clock frameClock;
    sf::Clock fpsClock;
    unsigned int frameCount = 0;
    
    // ✅ Corrigindo warning C4127
    while (m_isRunning) {
        if (!m_window.isOpen()) {
            m_isRunning = false;
            break;
        }
        
        float deltaTime = frameClock.restart().asSeconds();
        frameCount++;
        
        // Cálculo do FPS a cada segundo
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            float fps = frameCount / fpsClock.restart().asSeconds();
            frameCount = 0;
            LOG_DEBUG_F("FPS: %.1f, DeltaTime: %.3fms", fps, deltaTime * 1000.0f);
        }
        
        handleEvents();
        update(deltaTime);
        render();
        
        // Controle de framerate quando VSync está desativado
        if (!Config::VSYNC_ENABLED && deltaTime < m_targetFrameTime) {
            auto sleepDuration = std::chrono::microseconds(
                static_cast<long long>((m_targetFrameTime - deltaTime) * 1000000)
            );
            std::this_thread::sleep_for(sleepDuration);
        }
    }
    
    LOG_INFO("Loop principal finalizado");
}

void Application::handleEvents() {
    // ✅ SFML 3: pollEvent retorna std::optional
    while (std::optional<sf::Event> event = m_window.pollEvent()) {
        // ✅ SFML 3: Usar event->is<T>() e event->getIf<T>()
        if (event->is<sf::Event::Closed>()) {
            LOG_INFO("Evento: Janela fechada");
            quit();
        }
        else if (const sf::Event::Resized* resized = event->getIf<sf::Event::Resized>()) {
            LOG_INFO_F("Evento: Janela redimensionada para %dx%d", 
                      resized->size.x, resized->size.y);
        }
        else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                LOG_INFO("Evento: Tecla ESC pressionada - saindo");
                quit();
            }
        }
        else if (const sf::Event::MouseButtonPressed* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            LOG_DEBUG_F("Evento: Mouse pressionado - Botão: %d, Pos: (%d, %d)",
                       static_cast<int>(mousePressed->button),
                       mousePressed->position.x,
                       mousePressed->position.y);
        }
        else if (const sf::Event::MouseMoved* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            static unsigned int moveCount = 0;
            if (++moveCount % 10 == 0) {
                LOG_TRACE_F("Mouse movido para: (%d, %d)", 
                           mouseMoved->position.x, mouseMoved->position.y);
            }
        }
    }
}

void Application::update(float deltaTime) {
    static float updateTimer = 0.0f;
    updateTimer += deltaTime;
    
    // Log a cada 2 segundos para debug
    if (updateTimer >= 2.0f) {
        LOG_DEBUG("Update rodando...");
        updateTimer = 0.0f;
    }
}

void Application::render() {
    // Limpa a tela com cor escura
    m_window.clear(sf::Color(30, 30, 45));
    
    static sf::RectangleShape testShape(sf::Vector2f(100, 100));
    static bool initialized = false;
    
    if (!initialized) {
        testShape.setFillColor(sf::Color::Green);
        
        // ✅ SFML 3: setPosition com sf::Vector2f
        testShape.setPosition(sf::Vector2f(
            Config::WINDOW_WIDTH / 2.0f - 50.0f,
            Config::WINDOW_HEIGHT / 2.0f - 50.0f
        ));
        initialized = true;
        LOG_DEBUG("Shape de teste inicializado");
    }
    
    // ✅ SFML 3: Rotação com sf::degrees
    static float rotation = 0.0f;
    rotation += 90.0f * m_clock.getElapsedTime().asSeconds();
    if (rotation >= 360.0f) rotation = 0.0f;
    
    testShape.setRotation(sf::degrees(rotation));
    
    // Desenha e exibe
    m_window.draw(testShape);
    m_window.display();
}

} // namespace CitySim