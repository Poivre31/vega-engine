#include <console/console.h>
#include <gtest/gtest.h>

#include <iostream>
#include <string>

TEST(TestConsole, TestLogLevels) {
    EXPECT_NO_FATAL_FAILURE(
        auto test_console = console::create("OrionConsole");
        test_console->set_level(level::trace); test_console->info(
            "The integral of sin between 0 and pi is around : {:.4f}", 2.);
        test_console->debug("Successeful integration !");

        double a = 2;

        test_console->trace("This is a message... {:s}", "(trace)");
        test_console->debug("This is a message... {:s}", "(debug)");
        test_console->info("This is a message... {:s}", "(info)");
        test_console->warn("This is a message... {:s}", "(warn)");
        test_console->error("This is a message... {:s}", "(error)");
        test_console->critical("This is a message... {:s}", "(critical)");
        test_console->info("This is a number... {:.5f}", M_PI);
        test_console->info("This is a number... {:+.5g}", M_PI););

    EXPECT_NO_FATAL_FAILURE(
        auto vega_console = console::get();
        vega_console->set_level(level::warn);
        std::cout << "Changed log level to 'warn'\n";
        vega_console->trace("This is a message... {:s}", "(trace)");
        vega_console->debug("This is a message... {:s}", "(debug)");
        vega_console->info("This is a message... {:s}", "(info)");
        vega_console->warn("This is a message... {:s}", "(warn)");
        vega_console->error("This is a message... {:s}", "(error)");
        vega_console->critical("This is a message... {:s}", "(critical)"););
}

TEST(TestConsole, TestConsoleAccess) {
    EXPECT_NO_FATAL_FAILURE(auto vega_console = console::get();
                            vega_console = console::create_or_get("VegaEngine");
                            auto test_conole = console::create_or_get("Test");
                            auto test2 = console::get("Test");
                            test_conole->debug("Working 1");
                            test2->debug("Working 2"););

    EXPECT_EQ(console::get("Lame"), nullptr);
    EXPECT_NO_FATAL_FAILURE(console::create("VegaEngine"));
}
