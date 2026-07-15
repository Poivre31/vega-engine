#include <gtest/gtest.h>

#include "math/vec3.h"

vec3 construct(double x, double y, double z) {
  vec3 v(3, 2, 1);
  return v;
}

void print(vec3 v) { v.print(); }

bool equals(vec3 a, vec3 b) {
  if (a.x == b.x && a.y == b.y && a.z == b.z)
    return true;
  else
    return false;
}

TEST(TestMath, TestVec3) {
  double x = 3, y = 2, z = 1;
  EXPECT_NO_FATAL_FAILURE(construct(x, y, z));
  auto v = construct(x, y, z);
  EXPECT_NO_FATAL_FAILURE(print(v));
  EXPECT_EQ(equals(v, vec3(3, 2, 1)), true);
}
