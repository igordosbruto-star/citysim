#include <gtest/gtest.h>
#include "simulation/BuildingSystem.hpp"
#include "simulation/BuildingComponent.hpp"
#include "Core/Game.hpp"

using namespace CitySim;

class BuildingSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>();
        buildingSystem = std::make_unique<BuildingSystem>(*game);
        
        // Criar entidade de teste com BuildingComponent
        entity = game->getRegistry().create();
        game->getRegistry().emplace<BuildingComponent>(entity, true);
        game->getRegistry().emplace<GridComponent>(entity, sf::Vector2i(5, 5));
    }
    
    void TearDown() override {
        if (game->getRegistry().valid(entity)) {
            game->getRegistry().destroy(entity);
        }
    }

    std::unique_ptr<Game> game;
    std::unique_ptr<BuildingSystem> buildingSystem;
    entt::entity entity;
};

TEST_F(BuildingSystemTest, DemolishExistingBuilding) {
    sf::Vector2i pos(5, 5);
    EXPECT_TRUE(buildingSystem->demolish(pos));
}

TEST_F(BuildingSystemTest, DemolishNonexistentBuilding) {
    sf::Vector2i pos(10, 10);
    EXPECT_FALSE(buildingSystem->demolish(pos));
}

TEST_F(BuildingSystemTest, DemolishNonDemolishableBuilding) {
    sf::Vector2i pos(5, 5);
    auto& building = game->getRegistry().get<BuildingComponent>(entity);
    building.demolishable = false;
    EXPECT_FALSE(buildingSystem->demolish(pos));
}

TEST_F(BuildingSystemTest, DemolishBuildingTwice) {
    sf::Vector2i pos(5, 5);
    EXPECT_TRUE(buildingSystem->demolish(pos));
    EXPECT_FALSE(buildingSystem->demolish(pos));
}