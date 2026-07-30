#include <gtest/gtest.h>
#include <spdlog/fmt/ranges.h>

#include <vector>

#include "console/console.h"
#include "math/random.h"
#include "math/vec.h"

TEST(TestMath, TestRandom) {
    auto console = console::create("Random");
    EXPECT_NO_FATAL_FAILURE(std::vector<double> v; v.reserve(10);
                            for (size_t i = 0; i < 10; i++) {
                                v.push_back(random::uniform(0., 2.));
                            } console->info("({:.4g})", fmt::join(v, ", ")););
    EXPECT_NO_FATAL_FAILURE(console->info(
        "Random vector: {:.4g}",
        random::uniform_vec3(vec3d(-1., 0., 1.), vec3d(1., 1., 3.))));
    for (size_t i = 0; i < 100; i++) {
        EXPECT_TRUE(random::uniform_vec3<double>({-3., 1., 0.}, {-1., 2., 7.})
                        .is_within({-3., 1., 0.}, {-1., 2., 7.}));
    }
}
