#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include "Core/SaveSystem.hpp"
#include "Core/Game.hpp"
#include "simulation/ZoneComponent.hpp"
#include "simulation/BuildingComponent.hpp"
#include "simulation/GridComponent.hpp"

using namespace CitySim;
namespace fs = std::filesystem;

class SaveSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>();
        saveSystem = std::make_unique<SaveSystem>(*game);
        testFilePath = "test_save.json";
        
        // Criar algumas entidades de teste
        createTestEntities();
    }
    
    void TearDown() override {
        // Limpar arquivo de teste se existir
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
    
    void createTestEntities() {
        auto& registry = game->getRegistry();
        
        // Criar uma zona
        auto zoneEntity = registry.create();
        registry.emplace<ZoneComponent>(zoneEntity, ZoneType::Residential);
        registry.emplace<GridComponent>(zoneEntity, sf::Vector2i(1, 1));
        
        // Criar um edifício
        auto buildingEntity = registry.create();
        registry.emplace<BuildingComponent>(buildingEntity, true);
        registry.emplace<GridComponent>(buildingEntity, sf::Vector2i(2, 2));
    }
    
    bool entitiesMatch() {
        auto& registry = game->getRegistry();
        
        // Verificar zonas
        bool foundZone = false;
        auto zoneView = registry.view<ZoneComponent, GridComponent>();
        for (auto entity : zoneView) {
            const auto& zone = zoneView.get<ZoneComponent>(entity);
            const auto& grid = zoneView.get<GridComponent>(entity);
            
            if (zone.type == ZoneType::Residential && 
                grid.position == sf::Vector2i(1, 1)) {
                foundZone = true;
                break;
            }
        }
        
        // Verificar edifícios
        bool foundBuilding = false;
        auto buildingView = registry.view<BuildingComponent, GridComponent>();
        for (auto entity : buildingView) {
            const auto& building = buildingView.get<BuildingComponent>(entity);
            const auto& grid = buildingView.get<GridComponent>(entity);
            
            if (building.demolishable && 
                grid.position == sf::Vector2i(2, 2)) {
                foundBuilding = true;
                break;
            }
        }
        
        return foundZone && foundBuilding;
    }
    
    std::unique_ptr<Game> game;
    std::unique_ptr<SaveSystem> saveSystem;
    std::string testFilePath;
};

TEST_F(SaveSystemTest, SaveAndLoadMap) {
    EXPECT_TRUE(saveSystem->saveMap(testFilePath));
    EXPECT_TRUE(fs::exists(testFilePath));
    
    // Limpar registro e verificar que entidades foram removidas
    game->getRegistry().clear();
    EXPECT_FALSE(entitiesMatch());
    
    // Recarregar e verificar que entidades foram restauradas
    EXPECT_TRUE(saveSystem->loadMap(testFilePath));
    EXPECT_TRUE(entitiesMatch());
}

TEST_F(SaveSystemTest, LoadInvalidFile) {
    EXPECT_FALSE(saveSystem->loadMap("nonexistent.json"));
}

TEST_F(SaveSystemTest, SaveToInvalidPath) {
    EXPECT_FALSE(saveSystem->saveMap("/invalid/path/test.json"));
}

TEST_F(SaveSystemTest, LoadCorruptedFile) {
    // Criar arquivo corrompido
    std::ofstream file(testFilePath);
    file << "{ invalid json";
    file.close();
    
    EXPECT_FALSE(saveSystem->loadMap(testFilePath));
}