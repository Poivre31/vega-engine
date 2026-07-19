#pragma once
#include <console/console.h>

#include <iostream>

class vec3 {
   public:
    double x;
    double y;
    double z;

    vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    void print() { std::cout << x << " " << y << " " << z << "\n"; }
};

template <>
struct fmt::formatter<vec3> : fmt::formatter<double> {
    auto format(vec3 v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.x, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.y, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.z, ctx);

        return fmt::format_to(out, ")");
    }
};
