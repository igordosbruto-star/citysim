# Test ECS core functionality
add_executable(ecs-tests
    ecs_test_basic.cpp
)

target_link_libraries(ecs-tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    entt::entt
)

# Register with CTest
add_test(
    NAME test_ecs_core
    COMMAND ecs-tests
)