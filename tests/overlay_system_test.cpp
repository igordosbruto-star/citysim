#include <gtest/gtest.h>
#include <entt/entt.hpp>
#include "Core/Systems/OverlaySystem.hpp"
#include "Core/Components/PowerGridComponent.hpp"
#include "Core/Components/WaterGridComponent.hpp"
#include "Core/Components/PollutionComponent.hpp"
#include <SFML/Graphics.hpp>

using namespace CitySim;

class OverlaySystemTest : public ::testing::Test {
protected:
    entt::registry registry;
    std::unique_ptr<OverlaySystem> overlaySystem;
    sf::RenderWindow window;

    void SetUp() override {
        overlaySystem = std::make_unique<OverlaySystem>(registry);
        overlaySystem->setGridSize(sf::Vector2u(10, 10));  // 10x10 grid para testes
        window.create(sf::VideoMode(320, 320), "Test");  // 32 pixels * 10 = 320
    }

    // Helper para verificar a cor do pixel
    bool isColorInRange(const sf::Color& color, const sf::Color& target, int tolerance = 5) {
        return std::abs(static_cast<int>(color.r) - static_cast<int>(target.r)) <= tolerance &&
               std::abs(static_cast<int>(color.g) - static_cast<int>(target.g)) <= tolerance &&
               std::abs(static_cast<int>(color.b) - static_cast<int>(target.b)) <= tolerance;
    }
};

TEST_F(OverlaySystemTest, InitialState) {
    EXPECT_FALSE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, SetActiveOverlay) {
    overlaySystem->setActiveOverlay(OverlayType::Power);
    EXPECT_TRUE(overlaySystem->hasActiveOverlay());

    overlaySystem->clearOverlays();
    EXPECT_FALSE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, PowerOverlay) {
    // Adiciona uma usina de energia
    auto entity = registry.create();
    auto& power = registry.emplace<PowerGridComponent>(entity);
    power.hasPower = true;

    overlaySystem->setActiveOverlay(OverlayType::Power);
    overlaySystem->update(0.0f);

    window.clear();
    overlaySystem->render(window);
    window.display();

    // TODO: Adicionar verificações mais específicas quando tivermos
    // o sistema de grid espacial implementado
    EXPECT_TRUE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, WaterOverlay) {
    // Adiciona uma estação de água
    auto entity = registry.create();
    auto& water = registry.emplace<WaterGridComponent>(entity);
    water.hasWater = true;

    overlaySystem->setActiveOverlay(OverlayType::Water);
    overlaySystem->update(0.0f);

    window.clear();
    overlaySystem->render(window);
    window.display();

    EXPECT_TRUE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, PollutionOverlay) {
    // Adiciona uma fonte de poluição
    auto entity = registry.create();
    auto& pollution = registry.emplace<PollutionComponent>(entity);
    pollution.pollutionLevel = 50.0f;

    overlaySystem->setActiveOverlay(OverlayType::Pollution);
    overlaySystem->update(0.0f);

    window.clear();
    overlaySystem->render(window);
    window.display();

    EXPECT_TRUE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, MultipleOverlaySwitching) {
    overlaySystem->setActiveOverlay(OverlayType::Power);
    EXPECT_TRUE(overlaySystem->hasActiveOverlay());

    overlaySystem->setActiveOverlay(OverlayType::Water);
    EXPECT_TRUE(overlaySystem->hasActiveOverlay());

    overlaySystem->setActiveOverlay(OverlayType::Pollution);
    EXPECT_TRUE(overlaySystem->hasActiveOverlay());

    overlaySystem->clearOverlays();
    EXPECT_FALSE(overlaySystem->hasActiveOverlay());
}

TEST_F(OverlaySystemTest, GridSizeUpdate) {
    sf::Vector2u newSize(20, 20);
    overlaySystem->setGridSize(newSize);

    overlaySystem->setActiveOverlay(OverlayType::Power);
    overlaySystem->update(0.0f);

    window.create(sf::VideoMode(640, 640), "Test");  // 32 pixels * 20 = 640
    window.clear();
    overlaySystem->render(window);
    window.display();

    EXPECT_TRUE(overlaySystem->hasActiveOverlay());
}