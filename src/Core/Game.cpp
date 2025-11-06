#include "Core/Game.hpp"

#include "Core/Config.hpp"
#include "Utils/Logger.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Angle.hpp>

#include <cmath>

namespace CitySim {

Game::Game(sf::RenderWindow& window)
    : m_window(&window) {
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

    // Configura o placeholder visual enquanto os sistemas reais são desenvolvidos.
    m_debugShape.setSize(sf::Vector2f(120.0f, 120.0f));
    m_debugShape.setFillColor(sf::Color(70, 160, 220));
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

    m_simulationClock.restart();
    m_state = State::Running;

    LOG_INFO("Game inicializado");
    return true;
}

void Game::shutdown() {
    if (m_state == State::Uninitialized) {
        return;
    }

    LOG_INFO("Encerrando Game...");
    m_state = State::Uninitialized;
    m_debugShapeInitialized = false;
}

void Game::handleEvent(const sf::Event& event) {
    if (!isInitialized()) {
        return;
    }

    if (const auto* resized = event.getIf<sf::Event::Resized>()) {
        onWindowResized(*resized);
    }
    else if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
            if (isPaused()) {
                resume();
                LOG_INFO("Jogo retomado");
            } else {
                pause();
                LOG_INFO("Jogo pausado");
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (!isInitialized() || isPaused()) {
        return;
    }

    updateDebugVisual(deltaTime);
}

void Game::render() {
    if (!isInitialized()) {
        return;
    }

    if (!m_debugShapeInitialized) {
        return;
    }

    m_window->draw(m_debugShape);
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

void Game::onWindowResized(const sf::Event::Resized& resizedEvent) {
    if (!m_debugShapeInitialized) {
        return;
    }

    m_debugShape.setPosition(sf::Vector2f(
        static_cast<float>(resizedEvent.size.x) / 2.0f,
        static_cast<float>(resizedEvent.size.y) / 2.0f
    ));
}

void Game::updateDebugVisual(float deltaTime) {
    constexpr float rotationSpeed = 90.0f; // graus por segundo
    m_debugShapeRotation += rotationSpeed * deltaTime;
    if (m_debugShapeRotation >= 360.0f) {
        m_debugShapeRotation = std::fmod(m_debugShapeRotation, 360.0f);
    }

    m_debugShape.setRotation(sf::degrees(m_debugShapeRotation));
}

} // namespace CitySim
