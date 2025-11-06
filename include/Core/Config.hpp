#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

namespace CitySim::Config {

struct WindowConfig {
    unsigned int width = 1280;
    unsigned int height = 720;
    std::string title = "City Simulator";
    bool fullscreen = false;
};

struct RenderingConfig {
    unsigned int targetFps = 60;
    bool vsyncEnabled = false;
};

struct RuntimeConfig {
    WindowConfig window;
    RenderingConfig rendering;
};

// Inicializa as configurações carregando um arquivo opcional.
// Retorna true se o arquivo foi processado com sucesso.
bool load(const std::filesystem::path& filePath = {});

// Restaura os valores padrão previstos pelo projeto.
void resetToDefaults();

// Acesso direto à configuração atual.
const RuntimeConfig& get();

// Conveniências para acesso rápido.
unsigned int windowWidth();
unsigned int windowHeight();
const std::string& windowTitle();
unsigned int targetFps();
bool vsyncEnabled();
bool fullscreenEnabled();

} // namespace CitySim::Config
