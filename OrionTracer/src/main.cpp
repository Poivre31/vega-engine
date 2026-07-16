#include "console/console.h"
#include "math/trapezium.h"
#include "math/vec3.h"
#include <cmath>

double f(double x) { return sin(x); }

int main() {
  auto orion_console = create_console("OrionConsole");
  orion_console->set_level(level::debug);
  orion_console->info("Hello world !");

  vec3 a(3, 2, 1);

  orion_console->info("The integral of sin between 0 and pi is around : {:.4f}",
                      integration::trapezium(0, M_PI, f, 1000));

  orion_console->debug("Successeful integration !");

  return 0;
}