#include "Core/Game.hpp"

#include "Core/Config.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"
#include "Input/InputManager.hpp"
#include "Input/Keyboard.hpp"
#include "Utils/Logger.hpp"

#include <SFML/Graphics/Color.hpp>
#include <cmath>

namespace CitySim {

Game::Game(Graphics::Window& window, Graphics::Renderer& renderer, Input::InputManager& inputManager)
    : m_window(&window)
    , m_renderer(&renderer)
    , m_inputManager(&inputManager) {
}

Game::~Game() {
    shutdown();
}

bool Game::initialize() {
    if (m_state != State::Uninitialized) {
        LOG_WARNING("Game já inicializado");
        return true;
    }

    LOG_INFO("Inicializando Game...");

    // 1. Inicializar ECS primeiro
    if (!initializeECS()) {
        LOG_ERROR("Falha na inicialização do ECS");
        return false;
    }

    // 2. Inicializar tilemap
    if (!initializeTilemap()) {
        LOG_ERROR("Falha na inicialização do tilemap");
        return false;
    }

    // 3. Configurar debug shape (fallback visual)
    setupDebugVisual();

    m_simulationClock.restart();
    m_state = State::Running;

    LOG_INFO("Game inicializado com todos os sistemas ECS");
    return true;
}

bool Game::initializeECS() {
    // Registrar todos os sistemas ECS
    m_world.RegisterSystem<TransformSystem>();
    m_world.RegisterSystem<RenderSystem>(m_renderer);
    m_world.RegisterSystem<PowerSystem>();
    m_world.RegisterSystem<WaterSystem>();
    m_world.RegisterSystem<GarbageSystem>();
    m_world.RegisterSystem<PollutionSystem>();
    m_world.RegisterSystem<AlertSystem>();
    m_world.RegisterSystem<OverlaySystem>();
    
    // Inicializar sistemas ECS
    if (!m_world.InitSystems()) {
        LOG_ERROR("Failed to initialize ECS systems");
        return false;
    }
    
    // Obter referências para sistemas ECS
    m_renderSystem = m_world.GetSystem<RenderSystem>();
    m_transformSystem = m_world.GetSystem<TransformSystem>();
    m_powerSystem = m_world.GetSystem<PowerSystem>();
    m_waterSystem = m_world.GetSystem<WaterSystem>();
    m_garbageSystem = m_world.GetSystem<GarbageSystem>();
    m_pollutionSystem = m_world.GetSystem<PollutionSystem>();
    m_alertSystem = m_world.GetSystem<AlertSystem>();
    m_overlaySystem = m_world.GetSystem<OverlaySystem>();
    
    // Verificar sistemas essenciais
    if (!m_renderSystem || !m_transformSystem) {
        LOG_ERROR("Falha ao obter sistemas ECS essenciais");
        return false;
    }

    // Configurar sistemas específicos
    if (m_overlaySystem) {
        m_overlaySystem->setGridSize(sf::Vector2u(50, 50));
    }
    
    // Criar entidade de teste para validação
    Entity testEntity = m_world.CreateEntity("TestPowerPlant");
    auto& transform = testEntity.GetComponent<TransformComponent>();
    transform.position = {200.0f, 150.0f};
    
    // Adicionar usina de energia de teste se o sistema estiver disponível
    if (m_powerSystem) {
        m_powerSystem->addPowerPlant(testEntity.GetHandle(), 1000.0f);
    }
    
    LOG_INFO("ECS inicializado com {} sistemas", m_world.GetSystemCount());
    return true;
}

bool Game::initializeTilemap() {
    m_tilemap = std::make_unique<Tilemap>();
    
    // Tentar carregar tileset
    if (!m_tilemap->loadTileset("assets/tilesets/city_tileset.png")) {
        LOG_WARNING("Não foi possível carregar tileset, criando tilemap básico");
        
        // Criar tilemap básico como fallback
        constexpr int MAP_WIDTH = 50;
        constexpr int MAP_HEIGHT = 50;
        m_tilemap->create(MAP_WIDTH, MAP_HEIGHT, 64); // 64px tiles
        
        // Preencher com tiles básicos
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                // Criar padrão de tiles (grama, estrada, etc.)
                int tileId = (x + y) % 4; // Tile IDs básicos
                m_tilemap->setTile(x, y, tileId);
            }
        }
    }
    
    LOG_INFO("Tilemap inicializado");
    return true;
}

void Game::setupDebugVisual() {
    m_debugShape.setSize(sf::Vector2f(120.0f, 120.0f));
    m_debugShape.setFillColor(sf::Color(70, 160, 220, 128)); // Mais transparente
    m_debugShape.setOutlineColor(sf::Color(20, 40, 70));
    m_debugShape.setOutlineThickness(6.0f);
    m_debugShape.setOrigin(m_debugShape.getSize() / 2.0f);

    const auto windowSize = m_window->getSize();
    m_debugShape.setPosition(sf::Vector2f(
        static_cast<float>(windowSize.x) / 2.0f,
        static_cast<float>(windowSize.y) / 2.0f
    ));

    m_debugShapeRotation = 0.0f;
    m_debugShapeInitialized = true;
}

void Game::shutdown() {
    if (m_state == State::Uninitialized) {
        return;
    }

    LOG_INFO("Encerrando Game...");
    
    // Limpar recursos na ordem inversa de criação
    m_tilemap.reset();
    
    // Limpar ECS (o World já gerencia a destruição dos sistemas)
    m_world.Clear();
    
    m_state = State::Uninitialized;
    m_debugShapeInitialized = false;
}

void Game::handleEvent(const sf::Event& event) {
    if (!isInitialized()) {
        return;
    }

#if SFML_VERSION_MAJOR >= 3
    if (const auto* resized = event.getIf<sf::Event::Resized>()) {
        onWindowResized(*resized);
    }
#else
    if (event.type == sf::Event::Resized) {
        onWindowResized(event.size);
    }
#endif
}

void Game::update(float deltaTime) {
    if (!isInitialized() || isPaused()) {
        return;
    }

    // ATUALIZAR TODOS OS SISTEMAS ECS (incluindo os novos convertidos)
    m_world.Update(deltaTime);

    // Input para pausa (mantido do código original)
    if (m_inputManager && m_inputManager->keyboard().wasPressed(sf::Keyboard::Key::P)) {
        togglePause();
    }

    // Debug visual (mantido do código original)
    updateDebugVisual(deltaTime);
}

void Game::render() {
    if (!isInitialized()) {
        return;
    }

    // 1. RENDERIZAR TILEMAP (fundo)
    if (m_tilemap) {
        m_tilemap->draw(*m_renderer);
    }

    // 2. RENDERIZAR SISTEMAS ECS (RenderSystem cuida das entidades)
    // O RenderSystem já renderiza automaticamente no Update do World

    // 3. RENDERIZAR OVERLAYS (se ativo)
    if (m_overlaySystem && m_overlaySystem->hasActiveOverlay()) {
        m_overlaySystem->render(*m_renderer);
    }

    // 4. RENDERIZAR ALERTAS
    if (m_alertSystem) {
        m_alertSystem->render(*m_renderer);
    }

    // 5. DEBUG SHAPE (sobrepor tudo - mantido para compatibilidade)
    if (m_debugShapeInitialized && m_renderer) {
        m_renderer->draw(m_debugShape);
    }
}

void Game::pause() {
    if (!isInitialized() || m_state == State::Paused) {
        return;
    }

    m_state = State::Paused;
}

void Game::resume() {
    if (!isInitialized() || m_state == State::Running) {
        return;
    }

    m_state = State::Running;
    m_simulationClock.restart();
}

void Game::togglePause() {
    if (isPaused()) {
        resume();
        LOG_INFO("Jogo retomado");
    } else {
        pause();
        LOG_INFO("Jogo pausado");
    }
}

#if SFML_VERSION_MAJOR >= 3
void Game::onWindowResized(const sf::Event::Resized& resizedEvent) {
    if (!m_debugShapeInitialized) {
        return;
    }

    m_debugShape.setPosition(sf::Vector2f(
        static_cast<float>(resizedEvent.size.x) / 2.0f,
        static_cast<float>(resizedEvent.size.y) / 2.0f
    ));
}
#else
void Game::onWindowResized(const sf::Event::SizeEvent& resizedEvent) {
    if (!m_debugShapeInitialized) {
        return;
    }

    m_debugShape.setPosition(sf::Vector2f(
        static_cast<float>(resizedEvent.width) / 2.0f,
        static_cast<float>(resizedEvent.height) / 2.0f
    ));
}
#endif

void Game::updateDebugVisual(float deltaTime) {
    constexpr float rotationSpeed = 90.0f; // graus por segundo
    m_debugShapeRotation += rotationSpeed * deltaTime;
    if (m_debugShapeRotation >= 360.0f) {
        m_debugShapeRotation = std::fmod(m_debugShapeRotation, 360.0f);
    }

#if SFML_VERSION_MAJOR >= 3
    // SFML 3 uses sf::Angle for rotations
    m_debugShape.setRotation(sf::degrees(m_debugShapeRotation));
#else
    m_debugShape.setRotation(m_debugShapeRotation);
#endif
}

} // namespace CitySim