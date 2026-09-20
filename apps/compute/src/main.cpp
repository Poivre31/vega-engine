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
using namespace vega::math;

int main() {
  timer::create("halo");
  auto console = console::get(consoles::math);
  console->info("Hello world !");

  vec3d a(3, 2, 1);

  console->info("{: .2f}", a);

  console->info(
      "The integral of sin between 0 and pi is around : {:.4f}",
      integration::trapezium(0, constants::pi, f, 1000000)
  );

  vec3d v{3., 2., 1.};
  console::get(consoles::math)
      ->info(
          "Projecting {:.4g} on the plane defined by {:.4g} and {:.4g} "
          ": result is {:.4g}",
          v,
          vec3d{1., 2., 0.},
          vec3d(axis::y),
          project(v, {{1., 2., 0.}, axis::y})
      );
}
