#pragma once
#include <console/console.h>
#include <iostream>

class vec3 {
public:
  double x;
  double y;
  double z;

  vec3(double x, double y, double z) : x(x), y(y), z(z) {};

  void print() { std::cout << x << " " << y << " " << z << std::endl; }
};

template <> struct fmt::formatter<vec3> : fmt::formatter<float> {

  auto format(vec3 v, format_context &ctx) const -> decltype(ctx.out()) {
    auto out = fmt::format_to(ctx.out(), "(");

    ctx.advance_to(out);
    out = fmt::formatter<float>::format(v.x, ctx);

    out = fmt::format_to(out, ", ");
    ctx.advance_to(out);
    out = fmt::formatter<float>::format(v.y, ctx);

    out = fmt::format_to(out, ", ");
    ctx.advance_to(out);
    out = fmt::formatter<float>::format(v.z, ctx);

    return fmt::format_to(out, ")");
  }
};