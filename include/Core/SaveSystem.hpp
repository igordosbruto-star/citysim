#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Core/Game.hpp"

namespace CitySim {

class SaveSystem {
public:
    explicit SaveSystem(Game& game);
    
    bool saveMap(const std::string& filename);
    bool loadMap(const std::string& filename);
    
private:
    Game& m_game;
    
    // Funções auxiliares de serialização
    nlohmann::json serializeZones() const;
    nlohmann::json serializeBuildings() const;
    
    // Funções auxiliares de desserialização
    void deserializeZones(const nlohmann::json& data);
    void deserializeBuildings(const nlohmann::json& data);
};

} // namespace CitySim