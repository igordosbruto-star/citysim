#include <gtest/gtest.h>

#include "Core/Application.hpp"
#include "Core/Game.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"
#include "Input/InputManager.hpp"

#include <chrono>
#include <thread>

namespace {

class ApplicationGuard {
public:
    ApplicationGuard()
        : m_app(CitySim::Application::getInstance()) {}

    ~ApplicationGuard() {
        if (m_app.isRunning()) {
            m_app.quit();
        }
        m_app.shutdown();
    }

    CitySim::Application& app() { return m_app; }

private:
    CitySim::Application& m_app;
};

} // namespace

TEST(GameSmokeTest, InitializesAndHandlesBasicLoopCalls) {
    CitySim::Graphics::Window window;
    CitySim::Graphics::Renderer renderer(window);
    CitySim::Input::InputManager inputManager;
    CitySim::Game game(window, renderer, inputManager);

    EXPECT_EQ(game.state(), CitySim::Game::State::Uninitialized);
    ASSERT_TRUE(game.initialize());
    EXPECT_TRUE(game.isInitialized());
    EXPECT_EQ(game.state(), CitySim::Game::State::Running);

    game.update(0.016f);
    EXPECT_EQ(game.state(), CitySim::Game::State::Running);

    game.pause();
    EXPECT_TRUE(game.isPaused());

    game.update(0.016f);
    EXPECT_TRUE(game.isPaused());

    game.resume();
    EXPECT_FALSE(game.isPaused());

    game.shutdown();
    EXPECT_FALSE(game.isInitialized());
    EXPECT_EQ(game.state(), CitySim::Game::State::Uninitialized);
}

TEST(ApplicationSmokeTest, InitializesRunsSingleLoopAndShutsDown) {
    ApplicationGuard guard;
    auto& app = guard.app();

    if (!app.initialize()) {
        GTEST_SKIP() << "Application failed to initialize. Likely missing graphics context in test environment.";
    }

    EXPECT_TRUE(app.isRunning());

    CitySim::Game game(app.window(), app.renderer(), app.input());
    ASSERT_TRUE(game.initialize());

    std::thread runner([&]() {
        app.run(game);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    app.quit();
    runner.join();

    EXPECT_FALSE(app.isRunning());

    game.shutdown();
}
