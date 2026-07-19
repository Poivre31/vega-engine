#include <gtest/gtest.h>

#include <cmath>
#include <functional>

#include "math/trapezium.h"

TEST(TestMath, TestIntegrate) {
    double a = -.5;
    double b = 3;
    size_t n = 100;

    double max_error =
        abs((b - a) * (b - a) * (b - a) / static_cast<double>(12 * n * n) *
            exp(-std::min(a, b)));  //> Estimated error for trapezoidal rule

    EXPECT_NEAR(integration::trapezium(
                    a, b, [](double x) { return exp(-x); }, n),
                exp(-a) - exp(-b), 1.1 * max_error);
}
