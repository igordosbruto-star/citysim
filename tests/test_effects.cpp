#include <gtest/gtest.h>
#include "Graphics/Effects.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

using namespace CitySim;

class EffectsTest : public ::testing::Test {
protected:
    void SetUp() override {
        effects = std::make_unique<Effects>();
    }

    std::unique_ptr<Effects> effects;
};

TEST_F(EffectsTest, SelectionEffect) {
    effects->addSelection(sf::Vector2f(100, 100), 32.0f);
    effects->update(0.1f);  // Não deve remover seleção automaticamente
    effects->removeSelection();
}

TEST_F(EffectsTest, BuildEffect) {
    effects->addBuildEffect(sf::Vector2f(100, 100));
    effects->update(0.1f);  // Efeito deve persistir
    effects->update(1.0f);  // Efeito deve desaparecer após 0.5s
}

TEST_F(EffectsTest, DemolishEffect) {
    effects->addDemolishEffect(sf::Vector2f(100, 100));
    effects->update(0.1f);  // Efeito deve persistir
    effects->update(1.0f);  // Efeito deve desaparecer após 0.5s
}

TEST_F(EffectsTest, ErrorEffect) {
    effects->addErrorEffect(sf::Vector2f(100, 100));
    effects->update(0.1f);  // Efeito deve persistir
    effects->update(0.5f);  // Efeito deve desaparecer após 0.3s
}

TEST_F(EffectsTest, MultipleEffects) {
    effects->addBuildEffect(sf::Vector2f(100, 100));
    effects->addDemolishEffect(sf::Vector2f(200, 200));
    effects->addErrorEffect(sf::Vector2f(300, 300));
    effects->update(0.1f);  // Todos os efeitos devem persistir
}