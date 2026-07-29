#pragma once
#include <concepts>

#include "math/types/vec3.h"
#include "math/types/vec3i.h"

template <std::floating_point T>
[[nodiscard]] constexpr T dot(const vec3<T>& u, const vec3<T>& v) noexcept {
    return u.dot(v);
}
template <std::integral T>
[[nodiscard]] constexpr T dot(const vec3i<T>& u, const vec3i<T>& v) noexcept {
    return u.dot(v);
}

template <std::floating_point T>
[[nodiscard]] constexpr vec3<T> cross(const vec3<T>& u,
                                      const vec3<T>& v) noexcept {
    return u.cross(v);
}
template <std::integral T>
[[nodiscard]] constexpr vec3i<T> cross(const vec3i<T>& u,
                                       const vec3i<T>& v) noexcept {
    return u.cross(v);
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> cos(const vec3<T>& u) noexcept {
    return vec3<T>(cos(u.x), cos(u.y), cos(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> sin(const vec3<T>& u) noexcept {
    return vec3<T>(sin(u.x), sin(u.y), sin(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> tan(const vec3<T>& u) {
    return vec3<T>(tan(u.x), tan(u.y), tan(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> exp(const vec3<T>& u) {
    return vec3<T>(exp(u.x), exp(u.y), exp(u.z));
}

/** According to right hand rule */
template <std::floating_point T>
[[nodiscard]] inline vec3<T> rotate(const vec3<T>& v, const axis ax,
                                    const double theta) noexcept {
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
        default:
            console::get(default_consoles::math)
                ->error(
                    "Trying to rotate vector around an axis that does not "
                    "exist");
            return v;
    }
}

template <std::floating_point T>
[[nodiscard]] constexpr vec3<T> project(const vec3<T>& vec,
                                        const vec3<T>& axis) noexcept {
    double d2 = axis.norm_sqr();
    if (d2 == 0.) {
        return vec3<T>(0.);
    } else {
        return dot(vec, axis) / d2 * axis;
    }
}

/** Returns zero if the two vectors don't define a plane (ie if they are zero or
 * colinear) */
template <std::floating_point T>
[[nodiscard]] constexpr vec3<T> project(
    const vec3<T>& vec, const std::pair<vec3<T>, vec3<T>>& plane) noexcept {
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