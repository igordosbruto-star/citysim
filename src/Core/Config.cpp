#include "Core/Config.hpp"

#include "Utils/Logger.hpp"

#include <filesystem>
#include <fstream>
#include <mutex>

#if __has_include(<nlohmann/json.hpp>)
#define CITYSIM_HAS_JSON 1
#include <nlohmann/json.hpp>
#else
#define CITYSIM_HAS_JSON 0
#endif

namespace CitySim::Config {

namespace {

RuntimeConfig g_runtimeConfig{};
std::once_flag g_defaultsInitialized;

void ensureDefaults() {
    std::call_once(g_defaultsInitialized, [] {
        resetToDefaults();
    });
}

#if CITYSIM_HAS_JSON
void parseWindowSection(const nlohmann::json& json) {
    if (auto width = json.find("width"); width != json.end() && width->is_number_unsigned()) {
        g_runtimeConfig.window.width = width->get<unsigned int>();
    }
    if (auto height = json.find("height"); height != json.end() && height->is_number_unsigned()) {
        g_runtimeConfig.window.height = height->get<unsigned int>();
    }
    if (auto title = json.find("title"); title != json.end() && title->is_string()) {
        g_runtimeConfig.window.title = title->get<std::string>();
    }
    if (auto fullscreen = json.find("fullscreen"); fullscreen != json.end() && fullscreen->is_boolean()) {
        g_runtimeConfig.window.fullscreen = fullscreen->get<bool>();
    }
}

void parseRenderingSection(const nlohmann::json& json) {
    if (auto fps = json.find("target_fps"); fps != json.end() && fps->is_number_unsigned()) {
        g_runtimeConfig.rendering.targetFps = fps->get<unsigned int>();
    }
    if (auto vsync = json.find("vsync"); vsync != json.end() && vsync->is_boolean()) {
        g_runtimeConfig.rendering.vsyncEnabled = vsync->get<bool>();
    }
}
#endif

} // namespace

bool load(const std::filesystem::path& filePath) {
    ensureDefaults();
    resetToDefaults();

    const std::filesystem::path resolvedPath = filePath.empty()
        ? std::filesystem::path("assets/config/game.json")
        : filePath;

    if (!std::filesystem::exists(resolvedPath)) {
        LOG_INFO_F("Arquivo de configuração '%s' não encontrado. Usando valores padrão.",
                   resolvedPath.string().c_str());
        return false;
    }

#if CITYSIM_HAS_JSON
    try {
        std::ifstream file(resolvedPath);
        if (!file.is_open()) {
            LOG_ERROR_F("Não foi possível abrir o arquivo de configuração '%s'.", resolvedPath.string().c_str());
            return false;
        }

        nlohmann::json json;
        file >> json;

        if (auto window = json.find("window"); window != json.end() && window->is_object()) {
            parseWindowSection(*window);
        }

        if (auto rendering = json.find("rendering"); rendering != json.end() && rendering->is_object()) {
            parseRenderingSection(*rendering);
        }

        LOG_INFO_F("Configuração carregada de '%s'.", resolvedPath.string().c_str());
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR_F("Falha ao ler configuração '%s': %s", resolvedPath.string().c_str(), e.what());
    }
#else
    (void)resolvedPath;
    LOG_WARNING("Suporte a JSON indisponível. Recompile com nlohmann_json ou instale a dependência.");
#endif

    LOG_WARNING("Recuando para valores padrão de configuração.");
    resetToDefaults();
    return false;
}

void resetToDefaults() {
    g_runtimeConfig = RuntimeConfig{};
}

const RuntimeConfig& get() {
    ensureDefaults();
    return g_runtimeConfig;
}

unsigned int windowWidth() {
    return get().window.width;
}

unsigned int windowHeight() {
    return get().window.height;
}

const std::string& windowTitle() {
    return get().window.title;
}

unsigned int targetFps() {
    return get().rendering.targetFps;
}

bool vsyncEnabled() {
    return get().rendering.vsyncEnabled;
}

bool fullscreenEnabled() {
    return get().window.fullscreen;
}

} // namespace CitySim::Config
