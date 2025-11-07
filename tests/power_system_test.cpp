#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include <Core/Systems/PowerSystem.hpp>

using namespace CitySim;

class PowerSystemTest : public ::testing::Test {
protected:
    entt::registry registry;
    std::unique_ptr<PowerSystem> powerSystem;

    void SetUp() override {
        powerSystem = std::make_unique<PowerSystem>(registry);
    }
};

TEST_F(PowerSystemTest, PowerPlantCreation) {
    auto entity = registry.create();
    powerSystem->addPowerPlant(entity, 100.0f);

    ASSERT_TRUE(registry.all_of<PowerGridComponent>(entity));
    ASSERT_TRUE(registry.all_of<NetworkNodeComponent>(entity));

    const auto& power = registry.get<PowerGridComponent>(entity);
    EXPECT_FLOAT_EQ(power.powerCapacity, 100.0f);
    EXPECT_FLOAT_EQ(power.powerOutput, 100.0f);
    EXPECT_TRUE(power.isPowerPlant);
    EXPECT_TRUE(power.hasPower);

    const auto& node = registry.get<NetworkNodeComponent>(entity);
    EXPECT_TRUE(node.isActive);
    EXPECT_TRUE(node.isPowered);
}

TEST_F(PowerSystemTest, NodeConnection) {
    auto plant = registry.create();
    auto consumer = registry.create();

    powerSystem->addPowerPlant(plant, 100.0f);
    registry.emplace<PowerGridComponent>(consumer);
    registry.emplace<NetworkNodeComponent>(consumer);

    EXPECT_TRUE(powerSystem->connectNodes(plant, consumer));

    const auto& consumerNode = registry.get<NetworkNodeComponent>(consumer);
    EXPECT_FALSE(consumerNode.connections.empty());
}

TEST_F(PowerSystemTest, PowerPropagation) {
    auto plant = registry.create();
    auto consumer1 = registry.create();
    auto consumer2 = registry.create();

    powerSystem->addPowerPlant(plant, 100.0f);
    registry.emplace<PowerGridComponent>(consumer1);
    registry.emplace<NetworkNodeComponent>(consumer1);
    registry.emplace<PowerGridComponent>(consumer2);
    registry.emplace<NetworkNodeComponent>(consumer2);

    powerSystem->connectNodes(plant, consumer1);
    powerSystem->connectNodes(consumer1, consumer2);

    powerSystem->update(0.0f);

    const auto& power1 = registry.get<PowerGridComponent>(consumer1);
    const auto& power2 = registry.get<PowerGridComponent>(consumer2);

    EXPECT_TRUE(power1.hasPower);
    EXPECT_TRUE(power2.hasPower);
}

TEST_F(PowerSystemTest, PowerDemandCalculation) {
    auto plant = registry.create();
    auto consumer = registry.create();

    powerSystem->addPowerPlant(plant, 100.0f);
    auto& consumerPower = registry.emplace<PowerGridComponent>(consumer);
    consumerPower.powerDemand = 50.0f;
    registry.emplace<NetworkNodeComponent>(consumer);

    EXPECT_FLOAT_EQ(powerSystem->calculateTotalDemand(), 50.0f);
    EXPECT_FLOAT_EQ(powerSystem->calculateTotalOutput(), 100.0f);
}

TEST_F(PowerSystemTest, DisconnectedNodeHasNoPower) {
    auto plant = registry.create();
    auto disconnectedConsumer = registry.create();

    powerSystem->addPowerPlant(plant, 100.0f);
    auto& consumerPower = registry.emplace<PowerGridComponent>(disconnectedConsumer);
    registry.emplace<NetworkNodeComponent>(disconnectedConsumer);

    powerSystem->update(0.0f);

    EXPECT_FALSE(consumerPower.hasPower);
}