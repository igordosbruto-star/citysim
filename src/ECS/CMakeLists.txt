cmake_minimum_required(VERSION 3.25)

# ===== ECS Core Library =====
add_library(city-ecs STATIC
    src/ECS/Entity.cpp
    src/ECS/World.cpp
    src/ECS/Systems/RenderSystem.cpp
    src/ECS/Systems/TransformSystem.cpp
)

target_include_directories(city-ecs PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(city-ecs PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
    EnTT::EnTT
)

# ===== ECS Tests =====
if(BUILD_TESTS)
    enable_testing()
    
    # Find GTest
    find_package(GTest REQUIRED)
    
    # Test executable
    add_executable(ecs-tests
        tests/ecs/ecs_test_basic.cpp
    )
    
    target_link_libraries(ecs-tests PRIVATE
        city-ecs
        GTest::gtest
        GTest::gtest_main
    )
    
    # Register with CTest
    add_test(
        NAME test_ecs_core
        COMMAND ecs-tests
    )
endif()