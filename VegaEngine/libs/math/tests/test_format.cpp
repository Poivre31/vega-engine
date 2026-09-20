#include <console/console.hpp>
#include <gtest/gtest.h>

#include "math/vec.hpp"

using namespace vega;

using namespace vega::math;

TEST(TestConsole, TestPrintMath) {
  auto test_console = console::create("OrionConsole");
  vec3d a(3, 2, 1);
  EXPECT_NO_THROW(test_console->info("{:+.3f}", a););
}
