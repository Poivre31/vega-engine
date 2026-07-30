#include <nanobench.h>

#include "console/console.h"
#include "math/random.h"
#include "math/vec.h"

int main() {
    ankerl::nanobench::Bench bench;
    bench.warmup(1000000).minEpochIterations(1000000);
    auto v = random::uniform_vec3(-1., 1.);
    auto a = random::uniform_vec3(-1., 1.);
    double x1 = random::uniform(-1., 1.);
    double x2 = random::uniform(-1., 1.);
    bench.run("Double ops",
              [&] { ankerl::nanobench::doNotOptimizeAway(x1 / x2); });
    double x = 1;
    bench.run("Vec3 ops", [&] {
        ankerl::nanobench::detail::doNotOptimizeAway(x += (v / (x * a)).norm());
    });
}
