#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include <Core/Systems/WaterSystem.hpp>

using namespace CitySimulator;

class WaterSystemTest : public ::testing::Test {
protected:
    entt::registry registry;
    std::unique_ptr<WaterSystem> waterSystem;

    void SetUp() override {
        waterSystem = std::make_unique<WaterSystem>(registry);
    }
};

TEST_F(WaterSystemTest, WaterPlantCreation) {
    auto entity = registry.create();
    waterSystem->addWaterPlant(entity, 100.0f);

    ASSERT_TRUE(registry.all_of<WaterGridComponent>(entity));
    ASSERT_TRUE(registry.all_of<NetworkNodeComponent>(entity));

    const auto& water = registry.get<WaterGridComponent>(entity);
    EXPECT_FLOAT_EQ(water.waterCapacity, 100.0f);
    EXPECT_FLOAT_EQ(water.waterOutput, 100.0f);
    EXPECT_TRUE(water.isWaterPlant);
    EXPECT_TRUE(water.hasWater);

    const auto& node = registry.get<NetworkNodeComponent>(entity);
    EXPECT_TRUE(node.isActive);
    EXPECT_TRUE(node.hasWater);
}

TEST_F(WaterSystemTest, NodeConnection) {
    auto plant = registry.create();
    auto consumer = registry.create();

    waterSystem->addWaterPlant(plant, 100.0f);
    registry.emplace<WaterGridComponent>(consumer);
    registry.emplace<NetworkNodeComponent>(consumer);

    EXPECT_TRUE(waterSystem->connectNodes(plant, consumer));

    const auto& consumerNode = registry.get<NetworkNodeComponent>(consumer);
    EXPECT_FALSE(consumerNode.connections.empty());
}

TEST_F(WaterSystemTest, WaterPropagation) {
    auto plant = registry.create();
    auto consumer1 = registry.create();
    auto consumer2 = registry.create();

    waterSystem->addWaterPlant(plant, 100.0f);
    registry.emplace<WaterGridComponent>(consumer1);
    registry.emplace<NetworkNodeComponent>(consumer1);
    registry.emplace<WaterGridComponent>(consumer2);
    registry.emplace<NetworkNodeComponent>(consumer2);

    waterSystem->connectNodes(plant, consumer1);
    waterSystem->connectNodes(consumer1, consumer2);

    waterSystem->update(0.0f);

    const auto& water1 = registry.get<WaterGridComponent>(consumer1);
    const auto& water2 = registry.get<WaterGridComponent>(consumer2);

    EXPECT_TRUE(water1.hasWater);
    EXPECT_TRUE(water2.hasWater);
}

TEST_F(WaterSystemTest, WaterDemandCalculation) {
    auto plant = registry.create();
    auto consumer = registry.create();

    waterSystem->addWaterPlant(plant, 100.0f);
    auto& consumerWater = registry.emplace<WaterGridComponent>(consumer);
    consumerWater.waterDemand = 50.0f;
    registry.emplace<NetworkNodeComponent>(consumer);

    EXPECT_FLOAT_EQ(waterSystem->calculateTotalDemand(), 50.0f);
    EXPECT_FLOAT_EQ(waterSystem->calculateTotalOutput(), 100.0f);
}

TEST_F(WaterSystemTest, DisconnectedNodeHasNoWater) {
    auto plant = registry.create();
    auto disconnectedConsumer = registry.create();

    waterSystem->addWaterPlant(plant, 100.0f);
    auto& consumerWater = registry.emplace<WaterGridComponent>(disconnectedConsumer);
    registry.emplace<NetworkNodeComponent>(disconnectedConsumer);

    waterSystem->update(0.0f);

    EXPECT_FALSE(consumerWater.hasWater);
}