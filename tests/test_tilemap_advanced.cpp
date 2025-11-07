#include <gtest/gtest.h>
#include "Graphics/Tilemap.hpp"
#include <SFML/Graphics.hpp>

namespace CitySimulator {

class TilemapAdvancedTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_tilemap = std::make_unique<Tilemap>();
        // Create a minimal tileset with a dummy texture to avoid dependency on external assets
        auto tex = std::make_shared<sf::Texture>();
        m_tileset = std::make_unique<Tileset>(tex, 32, 32);
        // Add a default tile so IDs 0/1/2 are valid if used
        m_tileset->AddTile(sf::IntRect({0,0},{32,32}), Tile::Flags::Terrain);
        m_tileset->AddTile(sf::IntRect({32,0},{32,32}), Tile::Flags::Road);
        m_tileset->AddTile(sf::IntRect({64,0},{32,32}), Tile::Flags::Building);
    }

    void TearDown() override {
        m_tilemap.reset();
        m_tileset.reset();
    }

    std::unique_ptr<Tilemap> m_tilemap;
    std::unique_ptr<Tileset> m_tileset;
};

TEST_F(TilemapAdvancedTest, CreateWithValidDimensions) {
    EXPECT_TRUE(m_tilemap->Create(10, 10, *m_tileset));
    auto [w, h] = m_tilemap->GetSize();
    EXPECT_EQ(w, 10);
    EXPECT_EQ(h, 10);
}

TEST_F(TilemapAdvancedTest, SetAndGetTile) {
    m_tilemap->Create(5, 5, *m_tileset);
    
    // Test setting and getting a tile
    m_tilemap->SetTile(2, 3, 1);
    EXPECT_EQ(m_tilemap->GetTile(2, 3), 1);
}

TEST_F(TilemapAdvancedTest, InvalidPositions) {
    m_tilemap->Create(5, 5, *m_tileset);
    
    // Test out of bounds
    m_tilemap->SetTile(10, 10, 1);
    EXPECT_EQ(m_tilemap->GetTile(10, 10), -1);
}

TEST_F(TilemapAdvancedTest, EmptyTileHandling) {
    m_tilemap->Create(3, 3, *m_tileset);
    
    // Check if empty tiles return -1
    EXPECT_EQ(m_tilemap->GetTile(1, 1), -1);
    
    // Set and clear a tile (use size_t(-1) to clear)
    m_tilemap->SetTile(1, 1, 1);
    EXPECT_EQ(m_tilemap->GetTile(1, 1), 1);

    m_tilemap->SetTile(1, 1, static_cast<size_t>(-1));
    EXPECT_EQ(m_tilemap->GetTile(1, 1), -1);
}

TEST_F(TilemapAdvancedTest, TilesetAssociation) {
    // Tilemap does not expose the tileset pointer publicly; ensure Create succeeds
    EXPECT_TRUE(m_tilemap->Create(4, 4, *m_tileset));
}

} // namespace CitySimulator