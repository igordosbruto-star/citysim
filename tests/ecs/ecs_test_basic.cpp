#include <gtest/gtest.h>
#include "ECS/World.hpp"
#include "ECS/Components/BasicComponents.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/TransformSystem.hpp"

using namespace CitySimulator;

#include <entt/entt.hpp>

using namespace CitySim;

class ECSTestBasic : public ::testing::Test {
protected:
    void SetUp() override {
        world = std::make_unique<World>();
    }

    void TearDown() override {
        world.reset();
    }

    std::unique_ptr<World> world;
};

TEST_F(ECSTest, CreateEntity) {
    auto entity = world->CreateEntity();
    EXPECT_TRUE(entity.IsValid());
    EXPECT_TRUE(entity.HasComponent<TransformComponent>());
}

TEST_F(ECSTest, CreateNamedEntity) {
    const std::string name = "TestEntity";
    auto entity = world->CreateEntity(name);
    EXPECT_TRUE(entity.IsValid());
    EXPECT_TRUE(entity.HasComponent<TagComponent>());
    EXPECT_EQ(entity.GetComponent<TagComponent>().tag, name);
}

TEST_F(ECSTest, DestroyEntity) {
    auto entity = world->CreateEntity();
    EXPECT_TRUE(entity.IsValid());
    world->DestroyEntity(entity);
    EXPECT_FALSE(entity.IsValid());
}

TEST_F(ECSTest, AddRemoveComponent) {
    auto entity = world->CreateEntity();
    
    // Entity should start with Transform component
    EXPECT_TRUE(entity.HasComponent<TransformComponent>());
    
    // Add Renderable component
    entity.AddComponent<RenderableComponent>(true, 1);
    EXPECT_TRUE(entity.HasComponent<RenderableComponent>());
    
    // Check component values
    auto& renderable = entity.GetComponent<RenderableComponent>();
    EXPECT_TRUE(renderable.visible);
    EXPECT_EQ(renderable.layer, 1);
    
    // Remove component
    entity.RemoveComponent<RenderableComponent>();
    EXPECT_FALSE(entity.HasComponent<RenderableComponent>());
}

TEST_F(ECSTest, ModifyComponent) {
    auto entity = world->CreateEntity();
    auto& transform = entity.GetComponent<TransformComponent>();
    
    // Modify transform values
    transform.x = 100.0f;
    transform.y = 200.0f;
    transform.rotation = 45.0f;
    
    // Verify changes
    auto& transformCheck = entity.GetComponent<TransformComponent>();
    EXPECT_FLOAT_EQ(transformCheck.x, 100.0f);
    EXPECT_FLOAT_EQ(transformCheck.y, 200.0f);
    EXPECT_FLOAT_EQ(transformCheck.rotation, 45.0f);
}

TEST_F(ECSTest, FindEntityByName) {
    const std::string name = "UniqueEntity";
    auto entity = world->CreateEntity(name);
    
    // Find existing entity
    auto found = world->FindEntityByName(name);
    EXPECT_TRUE(found.IsValid());
    EXPECT_EQ(found.GetHandle(), entity.GetHandle());
    
    // Try to find non-existent entity
    auto notFound = world->FindEntityByName("NonExistent");
    EXPECT_FALSE(notFound.IsValid());
}

TEST_F(ECSTest, WorldClear) {
    world->CreateEntity("Entity1");
    world->CreateEntity("Entity2");
    
    // Add a system
    world->AddSystem<TransformSystem>();
    
    // Clear everything
    world->Clear();
    
    // Check that no entities exist
    auto found1 = world->FindEntityByName("Entity1");
    auto found2 = world->FindEntityByName("Entity2");
    EXPECT_FALSE(found1.IsValid());
    EXPECT_FALSE(found2.IsValid());
}

TEST_F(ECSTest, SystemManagement) {
    // Add systems
    auto& transformSys = world->AddSystem<TransformSystem>();

    // Mock render target for testing
    // Create a render target for testing
    sf::RenderWindow mockWindow(sf::VideoMode({800, 600}), "Test", sf::Style::None);
    auto& renderSys = world->AddSystem<RenderSystem>(&mockWindow);
    
    // Initialize systems
    EXPECT_TRUE(world->InitSystems());
    
    // Check system retrieval
    auto* foundTransform = world->GetSystem<TransformSystem>();
    EXPECT_NE(foundTransform, nullptr);
    EXPECT_EQ(foundTransform, &transformSys);
    
    auto* foundRender = world->GetSystem<RenderSystem>();
    EXPECT_NE(foundRender, nullptr);
    EXPECT_EQ(foundRender, &renderSys);
    
    // Check system names
    EXPECT_EQ(transformSys.GetName(), "TransformSystem");
    EXPECT_EQ(renderSys.GetName(), "RenderSystem");
    
    // Test enable/disable
    EXPECT_TRUE(transformSys.IsEnabled());
    transformSys.SetEnabled(false);
    EXPECT_FALSE(transformSys.IsEnabled());
}