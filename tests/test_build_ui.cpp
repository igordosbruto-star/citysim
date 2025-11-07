#include <gtest/gtest.h>
#include "ui/BuildUI.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

using namespace CitySim;

class BuildUITest : public ::testing::Test {
protected:
    void SetUp() override {
        buildUI = std::make_unique<BuildUI>();
    }

    std::unique_ptr<BuildUI> buildUI;
};

TEST_F(BuildUITest, DefaultToolIsNone) {
    EXPECT_EQ(buildUI->getSelectedTool(), BuildTool::None);
}

TEST_F(BuildUITest, CanSelectTool) {
    buildUI->setSelectedTool(BuildTool::Residential);
    EXPECT_EQ(buildUI->getSelectedTool(), BuildTool::Residential);
    
    buildUI->setSelectedTool(BuildTool::Commercial);
    EXPECT_EQ(buildUI->getSelectedTool(), BuildTool::Commercial);
    
    buildUI->setSelectedTool(BuildTool::Industrial);
    EXPECT_EQ(buildUI->getSelectedTool(), BuildTool::Industrial);
    
    buildUI->setSelectedTool(BuildTool::Demolish);
    EXPECT_EQ(buildUI->getSelectedTool(), BuildTool::Demolish);
}