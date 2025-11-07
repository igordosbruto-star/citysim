#include <gtest/gtest.h>
#include "simulation/ZoningSystem.hpp"
#include "Core/Game.hpp"

using namespace CitySim;

class ZoningSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        zoningSystem = std::make_unique<ZoningSystem>(registry);
    }

    entt::registry registry;
    std::unique_ptr<ZoningSystem> zoningSystem;
};

TEST_F(ZoningSystemTest, SetZoneAtEmptyPosition) {
    sf::Vector2i pos(5, 5);
    EXPECT_TRUE(zoningSystem->setZone(pos, ZoneType::Residential));
    EXPECT_EQ(zoningSystem->getZoneAt(pos), ZoneType::Residential);
}

TEST_F(ZoningSystemTest, OverwriteExistingZone) {
    sf::Vector2i pos(5, 5);
    EXPECT_TRUE(zoningSystem->setZone(pos, ZoneType::Residential));
    EXPECT_TRUE(zoningSystem->setZone(pos, ZoneType::Commercial));
    EXPECT_EQ(zoningSystem->getZoneAt(pos), ZoneType::Commercial);
}

TEST_F(ZoningSystemTest, RemoveZone) {
    sf::Vector2i pos(5, 5);
    EXPECT_TRUE(zoningSystem->setZone(pos, ZoneType::Residential));
    EXPECT_TRUE(zoningSystem->removeZone(pos));
    EXPECT_EQ(zoningSystem->getZoneAt(pos), ZoneType::None);
}

TEST_F(ZoningSystemTest, RemoveNonexistentZone) {
    sf::Vector2i pos(5, 5);
    EXPECT_FALSE(zoningSystem->removeZone(pos));
}

TEST_F(ZoningSystemTest, GetZoneAtEmptyPosition) {
    sf::Vector2i pos(5, 5);
    EXPECT_EQ(zoningSystem->getZoneAt(pos), ZoneType::None);
}

TEST_F(ZoningSystemTest, SetAllZoneTypes) {
    sf::Vector2i positions[] = {
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(2, 0)
    };
    
    ZoneType types[] = {
        ZoneType::Residential,
        ZoneType::Commercial,
        ZoneType::Industrial
    };
    
    for (size_t i = 0; i < 3; i++) {
        EXPECT_TRUE(zoningSystem->setZone(positions[i], types[i]));
        EXPECT_EQ(zoningSystem->getZoneAt(positions[i]), types[i]);
    }
}