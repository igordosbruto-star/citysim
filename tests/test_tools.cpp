#include <gtest/gtest.h>
#include "Tools/BrushTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/FillTool.hpp"

using namespace CitySim::Editor;

class ToolsTest : public ::testing::Test {
protected:
    void SetUp() override {
        brush = std::make_unique<BrushTool>();
        eraser = std::make_unique<EraserTool>();
        fill = std::make_unique<FillTool>();
    }

    std::unique_ptr<BrushTool> brush;
    std::unique_ptr<EraserTool> eraser;
    std::unique_ptr<FillTool> fill;
};

TEST_F(ToolsTest, ToolDefaultStates) {
    EXPECT_FALSE(brush->isActive());
    EXPECT_FALSE(eraser->isActive());
    EXPECT_FALSE(fill->isActive());
}

TEST_F(ToolsTest, ToolActivation) {
    brush->setActive(true);
    EXPECT_TRUE(brush->isActive());
    
    brush->setActive(false);
    EXPECT_FALSE(brush->isActive());
}

TEST_F(ToolsTest, BrushSizeChange) {
    const float newSize = 64.0f;
    brush->setSize(newSize);
    // Não podemos testar o tamanho diretamente pois é privado
    // mas podemos verificar se não houve crash
}

TEST_F(ToolsTest, ColorChange) {
    const sf::Color newColor(100, 150, 200);
    brush->setColor(newColor);
    fill->setColor(newColor);
    // Não podemos testar a cor diretamente pois é privada
    // mas podemos verificar se não houve crash
}

TEST_F(ToolsTest, ToolNames) {
    EXPECT_EQ(brush->getName(), "Brush");
    EXPECT_EQ(eraser->getName(), "Eraser");
    EXPECT_EQ(fill->getName(), "Fill");
}

TEST_F(ToolsTest, ToolDescriptions) {
    EXPECT_FALSE(brush->getDescription().empty());
    EXPECT_FALSE(eraser->getDescription().empty());
    EXPECT_FALSE(fill->getDescription().empty());
}