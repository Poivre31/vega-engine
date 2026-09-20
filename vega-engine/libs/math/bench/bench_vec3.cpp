#include <nanobench.h>

#include "console/console.hpp"
#include "math/random.hpp"
#include "math/vec.hpp"

using namespace vega::math;

int main() {
  ankerl::nanobench::Bench bench;
  bench.warmup(1000).minEpochIterations(1000000);
  auto v    = random::uniform_vec3(-1., 1.);
  auto a    = random::uniform_vec3(-1., 1.);
  double x1 = random::uniform(-1., 1.);
  double x2 = random::uniform(-1., 1.);
  bench.run("Double ops", [&] { ankerl::nanobench::doNotOptimizeAway(x1 / x2); });
  double x = 1;
  bench.run("Vec3 ops", [&] { ankerl::nanobench::doNotOptimizeAway(x += (v / (x * a)).norm()); });
  bench.minEpochIterations(0);
  vega::console::get(vega::consoles::math)->set_level(vega::level::critical);  // Silences the
                                                                               // console to
                                                                               // benchmark
                                                                               // v.print() overhead
  bench.run("Vec3 print", [&] { v.print(); });
}
