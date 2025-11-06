#pragma once

namespace CitySim {
namespace Config {

    // Configurações de janela
    constexpr unsigned int WINDOW_WIDTH = 1280;
    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int TARGET_FPS = 60;
    
    // Configurações de renderização
    constexpr bool VSYNC_ENABLED = true;
    constexpr unsigned int ANTIALIASING_LEVEL = 8;
    
    // Configurações do mundo
    constexpr unsigned int CHUNK_SIZE = 16;
    constexpr unsigned int WORLD_SIZE_IN_CHUNKS = 100;

} // namespace Config
} // namespace CitySim