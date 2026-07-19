#include <console/console.h>
#include <gtest/gtest.h>

#include "math/vec3.h"

TEST(TestConsole, TestPrintMath) {
    auto test_console = console::create("OrionConsole");
    vec3 a(3, 2, 1);
    EXPECT_NO_THROW(test_console->info("{:+.3f}", a););
}
