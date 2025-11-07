// Arquivo de testes para os sistemas vitais
#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include <Core/Components/PowerGridComponent.hpp>
#include <Core/Components/WaterGridComponent.hpp>
#include <Core/Components/PollutionComponent.hpp>
#include <Core/Components/NetworkNodeComponent.hpp>

using namespace CitySim;

class VitalSystemsTest : public ::testing::Test {
protected:
    entt::registry registry;

    void SetUp() override {
    }
};

TEST_F(VitalSystemsTest, PowerGridComponentInitialization) {
    auto entity = registry.create();
    auto &power = registry.emplace<PowerGridComponent>(entity);
    
    EXPECT_FLOAT_EQ(power.powerCapacity, 0.0f);
    EXPECT_FLOAT_EQ(power.powerOutput, 0.0f);
    EXPECT_FLOAT_EQ(power.powerDemand, 0.0f);
    EXPECT_FALSE(power.isPowerPlant);
    EXPECT_FALSE(power.hasPower);
    //EXPECT_EQ(power.gridId, 0U);
}

TEST_F(VitalSystemsTest, WaterGridComponentInitialization) {
    auto entity = registry.create();
    auto &water = registry.emplace<WaterGridComponent>(entity);
    
    EXPECT_FLOAT_EQ(water.waterCapacity, 0.0f);
    EXPECT_FLOAT_EQ(water.waterOutput, 0.0f);
    EXPECT_FLOAT_EQ(water.waterDemand, 0.0f);
    EXPECT_FALSE(water.isWaterPlant);
    EXPECT_FALSE(water.hasWater);
    //EXPECT_EQ(water.gridId, 0U);
}

TEST_F(VitalSystemsTest, PollutionComponentInitialization) {
    auto entity = registry.create();
    auto &pollution = registry.emplace<PollutionComponent>(entity);
    
    EXPECT_FLOAT_EQ(pollution.pollutionLevel, 0.0f);
    EXPECT_FLOAT_EQ(pollution.pollutionRadius, 0.0f);
    EXPECT_FLOAT_EQ(pollution.pollutionRate, 0.0f);
    EXPECT_FALSE(pollution.isGarbageFacility);
}

TEST_F(VitalSystemsTest, NetworkNodeComponentInitialization) {
    auto entity = registry.create();
    auto &node = registry.emplace<NetworkNodeComponent>(entity);
    
    //EXPECT_EQ(node.nodeId, 0U);
    EXPECT_TRUE(node.connections.empty());
    EXPECT_FALSE(node.isActive);
    EXPECT_FLOAT_EQ(node.connectionRange, 1.0f);
    EXPECT_FALSE(node.isPowered);
    EXPECT_FALSE(node.hasWater);
}