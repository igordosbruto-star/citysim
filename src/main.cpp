#include "Core/Application.hpp"
#include "Core/Config.hpp"
#include "Core/Game.hpp"
#include "Utils/Logger.hpp"

int main() {
    try {
        // Inicializar logger PRIMEIRO
        CitySim::Logger::getInstance().initialize("city_simulator.log");

        if (!CitySim::Config::load()) {
            LOG_INFO("Usando configuração padrão");
        }

        // Usar as macros CORRETAS
        LOG_INFO("Iniciando City Simulator...");
        LOG_DEBUG_F("Configuração: %dx%d, %d FPS",
                    CitySim::Config::windowWidth(),
                    CitySim::Config::windowHeight(),
                    CitySim::Config::targetFps());

        auto& app = CitySim::Application::getInstance();

        if (!app.initialize()) {
            LOG_ERROR("Falha na inicialização da Application");
            return -1;
        }

        CitySim::Game game(app.getWindow());

        if (!game.initialize()) {
            LOG_ERROR("Falha na inicialização do Game");
            app.shutdown();
            return -1;
        }

        app.run(game);

        game.shutdown();
        app.shutdown();

        LOG_INFO("=== City Simulator finalizado com sucesso ===");
        return 0;

    } catch (const std::exception& e) {
        LOG_FATAL_F("Exceção não tratada: %s", e.what());
        return -1;
    } catch (...) {
        LOG_FATAL("Exceção desconhecida não tratada");
        return -1;
    }
}
