#include <console/console.h>
#include <gtest/gtest.h>
#include <string>

TEST(TestConsole, TestPrint) {
  auto test_console = create_console("OrionConsole");
  test_console->set_level(level::trace);
  test_console->info("The integral of sin between 0 and pi is around : {:.4f}",
                     2.);
  test_console->debug("Successeful integration !");

  double a = 2;
  EXPECT_NO_THROW(
      test_console->trace("This is a message... {:s}", "(trace)");
      test_console->debug("This is a message... {:s}", "(debug)");
      test_console->info("This is a message... {:s}", "(info)");
      test_console->warn("This is a message... {:s}", "(warn)");
      test_console->error("This is a message... {:s}", "(error)");
      test_console->critical("This is a message... {:s}", "(critical)");
      test_console->info("This is a number... {:.5f}", M_PI);
      test_console->info("This is a number... {:+.5g}", M_PI););
}