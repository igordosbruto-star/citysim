#include <gtest/gtest.h>
#include "Graphics/Tilemap.hpp"
#include <memory>

using namespace CitySim;

class TilemapTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a dummy texture and tileset to avoid dependency on external assets
        auto texture = std::make_shared<sf::Texture>();
        m_Tileset = std::make_unique<Tileset>(texture, 32, 32);

        // Add some test tiles (use SFML3 IntRect constructor)
        sf::IntRect rect1({0, 0}, {32, 32});
        sf::IntRect rect2({32, 0}, {32, 32});
        sf::IntRect rect3({64, 0}, {32, 32});

        m_Tileset->AddTile(rect1, Tile::Flags::Terrain);
        m_Tileset->AddTile(rect2, Tile::Flags::Road);
        m_Tileset->AddTile(rect3, Tile::Flags::Building);
    }

    void TearDown() override {
        m_Tileset.reset();
    }

    std::unique_ptr<Tileset> m_Tileset;
};

TEST_F(TilemapTest, Creation) {
    Tilemap map;
    EXPECT_TRUE(map.Create(10, 10, *m_Tileset));
    auto [width, height] = map.GetSize();
    EXPECT_EQ(width, 10);
    EXPECT_EQ(height, 10);
}

TEST_F(TilemapTest, TileManipulation) {
    Tilemap map;
    map.Create(10, 10, *m_Tileset);

    // Verifica posição válida
    EXPECT_TRUE(map.IsValidPosition(5, 5));
    EXPECT_FALSE(map.IsValidPosition(10, 10));

    // Define e obtém tiles
    map.SetTile(5, 5, 1);
    EXPECT_EQ(map.GetTile(5, 5), 1);

    // Verifica tile fora dos limites
    EXPECT_EQ(map.GetTile(10, 10), -1);
}

TEST_F(TilemapTest, TileFlags) {
    // Verifica as flags dos tiles
    const Tile& terrainTile = m_Tileset->GetTile(0);
    EXPECT_TRUE(terrainTile.IsTerrain());
    EXPECT_FALSE(terrainTile.IsRoad());

    const Tile& roadTile = m_Tileset->GetTile(1);
    EXPECT_TRUE(roadTile.IsRoad());
    EXPECT_FALSE(roadTile.IsTerrain());

    const Tile& buildingTile = m_Tileset->GetTile(2);
    EXPECT_TRUE(buildingTile.IsBuilding());
    EXPECT_FALSE(buildingTile.IsRoad());
}
