#include "Core/Application.hpp"

#include "Core/Game.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"
#include "Input/InputManager.hpp"
#include "Input/Keyboard.hpp"
#include "Utils/Logger.hpp"

#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <chrono>
#include <thread>

#include <SFML/Graphics/Color.hpp>

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
    
    // SFML 3 changed VideoMode constructors to take a vector for size.
#if SFML_VERSION_MAJOR >= 3
    sf::VideoMode videoMode(sf::Vector2u(static_cast<unsigned int>(Config::windowWidth()),
                                         static_cast<unsigned int>(Config::windowHeight())));
#else
    sf::VideoMode videoMode(Config::windowWidth(), Config::windowHeight());
#endif

    sf::ContextSettings contextSettings;

    if (!m_window.create(videoMode, Config::windowTitle(), contextSettings)) {
        LOG_ERROR("Falha ao criar janela principal");
        return false;
    }

    m_window.setFramerateLimit(Config::targetFps());
    m_window.setKeyRepeatEnabled(false);
    m_window.setVerticalSyncEnabled(Config::vsyncEnabled());

    m_renderer = std::make_unique<Graphics::Renderer>(m_window);
    m_camera = std::make_unique<Graphics::Camera>(m_window);
    m_camera->apply(*m_renderer);

    m_targetFrameTime = 1.0f / static_cast<float>(Config::targetFps());
    m_isInitialized = true;
    m_isRunning = true;

    LOG_INFO("Application inicializada com sucesso");
    return true;
}

void Application::shutdown() {
    if (!m_isInitialized) return;
    
    LOG_INFO("Encerrando Application...");
    
    // Primeiro, paramos o loop principal
    m_isRunning = false;
    
    // Liberamos os recursos na ordem inversa de criação
    if (m_renderer) {
        m_renderer.reset();
    }

    if (m_camera) {
        m_camera.reset();
    }

    if (m_window.isOpen()) {
        m_window.close();
    }
    
    // Marcamos a aplicação como não inicializada
    m_isInitialized = false;
    
    // Registramos que a aplicação foi encerrada antes de desligar o logger
    LOG_INFO("Application encerrada");
    
    // O Logger deve ser o último a ser desligado
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Pequena pausa para garantir que todas as mensagens foram processadas
    Logger::getInstance().shutdown();
}

void Application::run(Game& game) {
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
        
        m_inputManager.beginFrame();
        handleEvents(game);
        update(game, deltaTime);
        render(game);

        // Controle de framerate quando VSync está desativado
        if (!Config::vsyncEnabled() && deltaTime < m_targetFrameTime) {
            auto sleepDuration = std::chrono::microseconds(
                static_cast<long long>((m_targetFrameTime - deltaTime) * 1000000)
            );
            std::this_thread::sleep_for(sleepDuration);
        }
    }
    
    LOG_INFO("Loop principal finalizado");
}

void Application::handleEvents(Game& game) {
    m_inputManager.processEvents(m_window, [&](const sf::Event& event) {
#if SFML_VERSION_MAJOR >= 3
        if (event.is<sf::Event::Closed>()) {
            LOG_INFO("Evento: Janela fechada");
            quit();
        } else if (const auto* resized = event.getIf<sf::Event::Resized>()) {
            LOG_INFO_F("Evento: Janela redimensionada para %dx%d",
                      resized->size.x, resized->size.y);
            if (m_camera && m_renderer) {
                m_camera->resize(sf::Vector2u(resized->size.x, resized->size.y));
                m_camera->apply(*m_renderer);
            }
        } else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            LOG_DEBUG_F("Evento: Mouse pressionado - Botão: %d, Pos: (%d, %d)",
                       static_cast<int>(mousePressed->button),
                       mousePressed->position.x,
                       mousePressed->position.y);
        } else if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
            static unsigned int moveCount = 0;
            if (++moveCount % 10 == 0) {
                LOG_TRACE_F("Mouse movido para: (%d, %d)",
                           mouseMoved->position.x, mouseMoved->position.y);
            }
        }
#else
        switch (event.type) {
        case sf::Event::Closed:
            LOG_INFO("Evento: Janela fechada");
            quit();
            break;
        case sf::Event::Resized:
            LOG_INFO_F("Evento: Janela redimensionada para %dx%d",
                      event.size.width, event.size.height);
            if (m_camera && m_renderer) {
                m_camera->resize(sf::Vector2u(event.size.width, event.size.height));
                m_camera->apply(*m_renderer);
            }
            break;
        case sf::Event::MouseButtonPressed:
            LOG_DEBUG_F("Evento: Mouse pressionado - Botão: %d, Pos: (%d, %d)",
                       static_cast<int>(event.mouseButton.button),
                       event.mouseButton.x,
                       event.mouseButton.y);
            break;
        case sf::Event::MouseMoved: {
            static unsigned int moveCount = 0;
            if (++moveCount % 10 == 0) {
                LOG_TRACE_F("Mouse movido para: (%d, %d)",
                           event.mouseMove.x, event.mouseMove.y);
            }
            break;
        }
        default:
            break;
        }
#endif

        game.handleEvent(event);
    });
}

void Application::update(Game& game, float deltaTime) {
    static float updateTimer = 0.0f;
    updateTimer += deltaTime;

    // Log a cada 2 segundos para debug
    if (updateTimer >= 2.0f) {
        LOG_DEBUG("Update rodando...");
        updateTimer = 0.0f;
    }

    if (m_inputManager.keyboard().wasPressed(sf::Keyboard::Key::Escape)) {
        LOG_INFO("Tecla ESC detectada - encerrando aplicação");
        quit();
        return;
    }

    game.update(deltaTime);
}

void Application::render(Game& game) {
    if (!m_renderer) {
        return;
    }

    m_renderer->beginFrame(sf::Color(30, 30, 45));

    game.render();

    m_renderer->endFrame();
}

} // namespace CitySim
