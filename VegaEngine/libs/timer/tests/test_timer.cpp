#include "timer/timer.h"
#include <console/console.h>

#include <gtest/gtest.h>

TEST(TestTimer, TestTimerBasics) {
    EXPECT_NO_FATAL_FAILURE(
        console::get()->info("Expecting 0.05s wait time"); timer::start();
        timer::stall(0.05); timer::print_ellapsed_time();
        timer::print_ellapsed_time("main", time_unit::second);
        timer::print_ellapsed_time("main", time_unit::nanosecond, 8););

    EXPECT_NO_FATAL_FAILURE(
        console::get()->info("Expecting 5 errors");
        timer::print_ellapsed_time("nope"); timer::get_ellapsed_time("nope");
        timer::pause("nope"); timer::restart("nope"); timer::reset("global"););

    timer::start("start");
    timer::stall(0.05);
    EXPECT_NEAR(timer::get_ellapsed_time("start", time_unit::second), 0.05,
                0.001);
    timer::pause("start");
    timer::stall(0.1);
    EXPECT_NEAR(timer::get_ellapsed_time("start", time_unit::second), 0.05,
                0.001);
    timer::pause("start");
    timer::restart("start");
    timer::stall(0.1);
    EXPECT_NEAR(timer::get_ellapsed_time("start", time_unit::second), 0.15,
                0.001);

    timer::start("start");
    timer::stall(350000, time_unit::microsecond);
    EXPECT_NEAR(timer::get_ellapsed_time("start", time_unit::millisecond), 350,
                5);

    EXPECT_NO_FATAL_FAILURE(timer::print_ellapsed_time("global"));
}