#pragma once
#include <concepts>

#include "math/vec3.h"

/** According to right hand rule */
template <std::floating_point T>
vec3<T> rotate(const vec3<T>& v, const axis ax, const double theta) {
    switch (ax) {
        case axis::x:
            return vec3(v.x, (cos(theta) * v.y) - (sin(theta) * v.z),
                        (sin(theta) * v.y) + (cos(theta) * v.z));
        case axis::y:
            return vec3((cos(theta) * v.x) + (sin(theta) * v.z), v.y,
                        (-sin(theta) * v.x) + (cos(theta) * v.z));
        case axis::z:
            return vec3((cos(theta) * v.x) - (sin(theta) * v.y),
                        (sin(theta) * v.x) + (cos(theta) * v.y), v.z);
    }
}

template <std::floating_point T>
vec3<T> project(const vec3<T>& vec, vec3<T> axis) {
    double d2 = axis.norm_sqr();
    if (d2 == 0.) {
        return 0.;
    } else {
        return dot(vec, axis) / d2 * axis;
    }
}

/** Returns zero if the two vectors don't define a plane (ie if they are zero or
 * colinear) */
template <std::floating_point T>
vec3<T> project(const vec3<T>& vec, const std::pair<vec3<T>, vec3<T>>& plane) {
    auto u = cross(plane.first, plane.second);
    double d2 = u.norm_sqr();
    if (d2 == 0.) {
        // console::get(default_consoles::math)
        //     ->warn(
        //         "The two given vectors ({} and {}) do not define a plane,
        //         they " "must be non zero and non colinear", plane.first,
        //         plane.second);
        return vec3(0.);
    } else {
        return vec - (dot(vec, u) / d2 * u);
    }
}

// template <std::floating_point T>
// void rotate(const vec3<T>& v, vec3<T> axis, const double theta) {
//     axis.normalize();
//     double x = ((axis.x * axis.x * (1 - cos(theta))) + cos(theta)) * v.x;
// }