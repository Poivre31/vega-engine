#include <gtest/gtest.h>

#include <cmath>

#include "math/numbers.h"
#include "math/vec.h"

void print(const vec2d& v) { v.print(); }

TEST(TestMath, TestVec2) {
    double x = 3;
    double y = 2;
    auto v = vec2d(x, y);
    EXPECT_NO_FATAL_FAILURE(print(v));
    EXPECT_EQ(v == vec2d(3., 2.), true);
    EXPECT_EQ(v + vec2d(4., 2.), vec2d(3. + 4., 2. + 2.));
    double norm = sqrt((x * x) + (y * y));
    EXPECT_LE((v.normalized() - vec2d(3. / norm, 2. / norm)).norm_L1(), .00001);
    EXPECT_DOUBLE_EQ(v.max_abs(), 3.);
    EXPECT_LE(abs(dot(vec2d(axis::x), vec2d(axis::y))), .00001);
    EXPECT_LE((vec2(6.) / v - vec2d(2., 3.)).norm_L1(), .00001);
    EXPECT_EQ(vec2d(axis::x).norm_L0(), 1);
    EXPECT_EQ(cos(v), v.transformed(cosl));

    EXPECT_LE((rotate(vec2d(1, 1), math::pi_by_2) - vec2d(-1, 1)).norm_inf(),
              1e-10);
    EXPECT_EQ(project(v, vec2d(axis::y)), 2. * vec2d(axis::y));

    v.set_zero();
    EXPECT_EQ(v, project(vec2d(1, 0), vec2d(0, 1)));
}
