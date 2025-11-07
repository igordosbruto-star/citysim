#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include <Core/Systems/GarbagePollutionSystem.hpp>
#include <Core/Components/PollutionComponent.hpp>

using namespace CitySimulator;

class GarbagePollutionSystemTest : public ::testing::Test {
protected:
    entt::registry registry;
    std::unique_ptr<GarbageSystem> garbageSystem;
    std::unique_ptr<PollutionSystem> pollutionSystem;

    void SetUp() override {
        garbageSystem = std::make_unique<GarbageSystem>(registry);
        pollutionSystem = std::make_unique<PollutionSystem>(registry);
    }
};

TEST_F(GarbagePollutionSystemTest, GarbageFacilityCreation) {
    auto entity = registry.create();
    garbageSystem->addGarbageFacility(entity, 100.0f);

    ASSERT_TRUE(registry.all_of<PollutionComponent>(entity));
    const auto& pollution = registry.get<PollutionComponent>(entity);
    
    EXPECT_TRUE(pollution.isGarbageFacility);
    EXPECT_GT(pollution.pollutionRadius, 0.0f);
    EXPECT_GT(pollution.pollutionLevel, 0.0f);
}

TEST_F(GarbagePollutionSystemTest, GarbageCapacityCalculation) {
    auto facility1 = registry.create();
    auto facility2 = registry.create();

    garbageSystem->addGarbageFacility(facility1, 100.0f);
    garbageSystem->addGarbageFacility(facility2, 200.0f);

    float totalCapacity = garbageSystem->calculateTotalCapacity();
    EXPECT_GT(totalCapacity, 0.0f);
}

TEST_F(GarbagePollutionSystemTest, GarbageGeneration) {
    // Adiciona algumas entidades para simular população
    for (int i = 0; i < 10; ++i) {
        registry.create();
    }

    float totalGarbage = garbageSystem->calculateTotalGarbage();
    EXPECT_GT(totalGarbage, 0.0f);
}

TEST_F(GarbagePollutionSystemTest, PollutionPropagation) {
    auto facility = registry.create();
    garbageSystem->addGarbageFacility(facility, 100.0f);

    garbageSystem->update(1.0f);
    pollutionSystem->update(1.0f);

    const auto& pollution = registry.get<PollutionComponent>(facility);
    EXPECT_GT(pollution.pollutionLevel, 0.0f);
}

TEST_F(GarbagePollutionSystemTest, PollutionLevel) {
    auto facility = registry.create();
    garbageSystem->addGarbageFacility(facility, 100.0f);

    sf::Vector2f position(0.0f, 0.0f);  // Posição arbitrária para teste
    float pollution = pollutionSystem->getPollutionAt(position);

    EXPECT_GE(pollution, 0.0f);
}

TEST_F(GarbagePollutionSystemTest, MultipleUpdateCycles) {
    auto facility = registry.create();
    garbageSystem->addGarbageFacility(facility, 100.0f);

    // Simula vários ciclos de atualização
    for (int i = 0; i < 10; ++i) {
        garbageSystem->update(0.1f);
        pollutionSystem->update(0.1f);
    }

    const auto& pollution = registry.get<PollutionComponent>(facility);
    EXPECT_GT(pollution.pollutionLevel, 0.0f);
}