#include <gtest/gtest.h>
#include <iostream>
#include "engine_simulator.h"
#include "user_input.h"

Engine engine;
void initialize_engine()
{
    engine.initialize(500, 9000);
}

TEST(engine_simulator, get_eng_rpm_initial)
{
    GTEST_ASSERT_EQ(engine.get_eng_rpm(), 0);
}

TEST(engine_simulator, Ignition_off)
{
    GTEST_ASSERT_EQ(engine.get_eng_sts(), false);
}

TEST(engine_simulator, Ignition_on)
{
    engine.Ignition(true, 0, 100, gear_lever_position::P);
    GTEST_ASSERT_EQ(engine.get_eng_sts(), true);
}

int main(int argc, char* argv[])
{
    initialize_engine();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}