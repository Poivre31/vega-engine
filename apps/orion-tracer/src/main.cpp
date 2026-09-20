#include <console/console.hpp>
#include <math/integration.hpp>
#include <math/numbers.hpp>
#include <math/vec.hpp>
#include <timer/timer.hpp>

#include <cmath>

double f(double x) {
  return std::sin(x);
}

using vega::timer;
using vega::console;
using vega::consoles;

int main() {
  timer::create("halo");
  auto orion_console = console::create("Orion");
  orion_console->set_level(vega::level::debug);
  orion_console->info("Hello world !");
}
