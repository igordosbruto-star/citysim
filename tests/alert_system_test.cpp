#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include <Core/Systems/AlertSystem.hpp>
#include <Core/Components/PowerGridComponent.hpp>
#include <Core/Components/WaterGridComponent.hpp>
#include <Core/Components/PollutionComponent.hpp>

using namespace CitySimulator;

class AlertSystemTest : public ::testing::Test {
protected:
    entt::registry registry;
    std::unique_ptr<AlertSystem> alertSystem;
    sf::RenderWindow window;

    void SetUp() override {
        alertSystem = std::make_unique<AlertSystem>(registry);
        window.create(sf::VideoMode(800, 600), "Test");
    }
};

TEST_F(AlertSystemTest, InitialState) {
    EXPECT_EQ(alertSystem->getActiveAlertCount(), 0);
}

TEST_F(AlertSystemTest, PowerAlert) {
    auto entity = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity);
    power.hasPower = false;

    alertSystem->update(0.0f);

    EXPECT_GT(alertSystem->getActiveAlertCount(), 0);
}

TEST_F(AlertSystemTest, WaterAlert) {
    auto entity = registry.create();
    auto& water = registry.emplace<WaterGridComponent>(entity);
    water.hasWater = false;

    alertSystem->update(0.0f);

    EXPECT_GT(alertSystem->getActiveAlertCount(), 0);
}

TEST_F(AlertSystemTest, PollutionAlert) {
    auto entity = registry.create();
    auto& pollution = registry.emplace<PollutionComponent>(entity);
    pollution.pollutionLevel = 80.0f;  // Acima do limite

    alertSystem->update(0.0f);

    EXPECT_GT(alertSystem->getActiveAlertCount(), 0);
}

TEST_F(AlertSystemTest, AlertDuration) {
    auto entity = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity);
    power.hasPower = false;

    alertSystem->update(0.0f);
    size_t initialCount = alertSystem->getActiveAlertCount();

    // Avança o tempo além da duração do alerta
    alertSystem->update(6.0f);  // Duração do alerta é 5 segundos

    EXPECT_LT(alertSystem->getActiveAlertCount(), initialCount);
}

TEST_F(AlertSystemTest, AlertClear) {
    auto entity = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity);
    power.hasPower = false;

    alertSystem->update(0.0f);
    EXPECT_GT(alertSystem->getActiveAlertCount(), 0);

    alertSystem->clearAlerts();
    EXPECT_EQ(alertSystem->getActiveAlertCount(), 0);
}

TEST_F(AlertSystemTest, MultipleAlerts) {
    auto entity1 = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity1);
    power.hasPower = false;

    auto entity2 = registry.create();
    auto& water = registry.emplace<WaterGridComponent>(entity2);
    water.hasWater = false;

    alertSystem->update(0.0f);

    // Deve haver alertas tanto para energia quanto para água
    EXPECT_GT(alertSystem->getActiveAlertCount(), 1);
}

TEST_F(AlertSystemTest, RenderingTest) {
    auto entity = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity);
    power.hasPower = false;

    alertSystem->update(0.0f);

    window.clear();
    alertSystem->render(window);
    window.display();

    EXPECT_GT(alertSystem->getActiveAlertCount(), 0);
}