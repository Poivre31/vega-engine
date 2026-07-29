#include <gtest/gtest.h>

#include <cmath>

#include "math/numbers.h"
#include "math/vec.h"

void print(const vec3d& v) { v.print(); }

TEST(TestMath, TestVec3) {
    double x = 3;
    double y = 2;
    double z = 1;
    auto v = vec3d(x, y, z);
    EXPECT_NO_FATAL_FAILURE(print(v));
    EXPECT_EQ(v == vec3d(3., 2., 1.), true);
    EXPECT_EQ(v + vec3d(4., 2., 1.), vec3d(3. + 4., 2. + 2., 1. + 1.));
    double norm = sqrt(1. + 4. + 9.);
    EXPECT_LE(
        (v.normalized() - vec3d(3. / norm, 2. / norm, 1. / norm)).norm_L1(),
        .00001);
    EXPECT_DOUBLE_EQ(v.max_abs(), 3.);
    EXPECT_LE(
        (cross(vec3d(axis::x), vec3d(axis::y)) - vec3d(axis::z)).norm_L1(),
        .00001);
    EXPECT_LE(abs(dot(vec3d(axis::x), vec3d(axis::y))), .00001);
    EXPECT_LE((6. / v - vec3d(2., 3., 6.)).norm_L1(), .00001);
    EXPECT_EQ(vec3d(axis::x).norm_L0(), 1);
    EXPECT_EQ(cos(v), v.transformed(cosl));

    EXPECT_LE((rotate(vec3d(1, 1, 1), axis::x, math::pi_by_2) - vec3d(1, -1, 1))
                  .norm_inf(),
              1e-10);
    EXPECT_LE((rotate(vec3d(1, 1, 1), axis::y, math::pi_by_2) - vec3d(1, 1, -1))
                  .norm_inf(),
              1e-10);
    EXPECT_LE((rotate(vec3d(1, 1, 1), axis::z, math::pi_by_2) - vec3d(-1, 1, 1))
                  .norm_inf(),
              1e-10);
    EXPECT_EQ(project(v, vec3d(axis::y)), 2. * vec3d(axis::y));
    EXPECT_EQ(project(v, {vec3d(axis::x), vec3d(axis::z)}), vec3d(3., 0., 1.));
}
