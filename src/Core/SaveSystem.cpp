#include "Core/SaveSystem.hpp"
#include "Utils/Logger.hpp"
#include "simulation/ZoneComponent.hpp"
#include "simulation/BuildingComponent.hpp"
#include "simulation/GridComponent.hpp"
#include <fstream>

using json = nlohmann::json;

namespace CitySim {

SaveSystem::SaveSystem(Game& game)
    : m_game(game) {
    LOG_INFO("SaveSystem initialized");
}

bool SaveSystem::saveMap(const std::string& filename) {
    try {
        json saveData;
        saveData["version"] = "1.0";
        saveData["zones"] = serializeZones();
        saveData["buildings"] = serializeBuildings();
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            LOG_ERROR_F("Failed to open file for saving: %s", filename.c_str());
            return false;
        }
        
        file << saveData.dump(4);
        LOG_INFO_F("Map saved successfully to %s", filename.c_str());
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR_F("Error saving map: %s", e.what());
        return false;
    }
}

bool SaveSystem::loadMap(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            LOG_ERROR_F("Failed to open file for loading: %s", filename.c_str());
            return false;
        }
        
        json saveData = json::parse(file);
        
        // Verificar versão
        std::string version = saveData["version"];
        if (version != "1.0") {
            LOG_WARNING_F("Loading map with version %s, current version is 1.0", version.c_str());
        }
        
        // Limpar dados existentes
        auto& registry = m_game.getRegistry();
        registry.clear();
        
        // Carregar dados
        deserializeZones(saveData["zones"]);
        deserializeBuildings(saveData["buildings"]);
        
        LOG_INFO_F("Map loaded successfully from %s", filename.c_str());
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR_F("Error loading map: %s", e.what());
        return false;
    }
}

json SaveSystem::serializeZones() const {
    json zones = json::array();
    auto& registry = m_game.getRegistry();
    
    auto view = registry.view<ZoneComponent, GridComponent>();
    for (auto entity : view) {
        const auto& zone = view.get<ZoneComponent>(entity);
        const auto& grid = view.get<GridComponent>(entity);
        
        json zoneData;
        zoneData["type"] = static_cast<int>(zone.type);
        zoneData["level"] = zone.level;
        zoneData["happiness"] = zone.happiness;
        zoneData["position"] = {
            {"x", grid.position.x},
            {"y", grid.position.y}
        };
        
        zones.push_back(zoneData);
    }
    
    return zones;
}

json SaveSystem::serializeBuildings() const {
    json buildings = json::array();
    auto& registry = m_game.getRegistry();
    
    auto view = registry.view<BuildingComponent, GridComponent>();
    for (auto entity : view) {
        const auto& building = view.get<BuildingComponent>(entity);
        const auto& grid = view.get<GridComponent>(entity);
        
        json buildingData;
        buildingData["demolishable"] = building.demolishable;
        buildingData["health"] = building.health;
        buildingData["position"] = {
            {"x", grid.position.x},
            {"y", grid.position.y}
        };
        
        buildings.push_back(buildingData);
    }
    
    return buildings;
}

void SaveSystem::deserializeZones(const json& data) {
    auto& registry = m_game.getRegistry();
    
    for (const auto& zoneData : data) {
        auto entity = registry.create();
        
        ZoneComponent zone;
        zone.type = static_cast<ZoneType>(zoneData["type"]);
        zone.level = zoneData["level"];
        zone.happiness = zoneData["happiness"];
        
        GridComponent grid;
        grid.position.x = zoneData["position"]["x"];
        grid.position.y = zoneData["position"]["y"];
        
        registry.emplace<ZoneComponent>(entity, zone);
        registry.emplace<GridComponent>(entity, grid);
    }
}

void SaveSystem::deserializeBuildings(const json& data) {
    auto& registry = m_game.getRegistry();
    
    for (const auto& buildingData : data) {
        auto entity = registry.create();
        
        BuildingComponent building;
        building.demolishable = buildingData["demolishable"];
        building.health = buildingData["health"];
        
        GridComponent grid;
        grid.position.x = buildingData["position"]["x"];
        grid.position.y = buildingData["position"]["y"];
        
        registry.emplace<BuildingComponent>(entity, building);
        registry.emplace<GridComponent>(entity, grid);
    }
}

} // namespace CitySim