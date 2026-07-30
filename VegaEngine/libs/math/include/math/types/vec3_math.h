#pragma once
#include <concepts>

#include "math/types/vec3.h"

template <math::numeric T>
[[nodiscard]] constexpr T dot(const vec3<T>& u, const vec3<T>& v) noexcept {
    return u.dot(v);
}

template <math::numeric T>
[[nodiscard]] constexpr vec3<T> cross(const vec3<T>& u,
                                      const vec3<T>& v) noexcept {
    return u.cross(v);
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> cos(const vec3<T>& u) noexcept {
    return vec3<T>(std::cos(u.x), std::cos(u.y), std::cos(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> sin(const vec3<T>& u) noexcept {
    return vec3<T>(std::sin(u.x), std::sin(u.y), std::sin(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> tan(const vec3<T>& u) noexcept {
    return vec3<T>(std::tan(u.x), std::tan(u.y), std::tan(u.z));
}

template <std::floating_point T>
[[nodiscard]] inline vec3<T> exp(const vec3<T>& u) noexcept {
    return vec3<T>(std::exp(u.x), std::exp(u.y), std::exp(u.z));
}

/** Rotates vector around one of the cartesian axis according to right hand rule
 * and anti-clockwise rotatation */
template <std::floating_point T>
[[nodiscard]] inline vec3<T> rotate(const vec3<T>& v, const axis ax,
                                    const double theta) {
    const double cos_t = std::cos(theta);
    const double sin_t = std::sin(theta);
    switch (ax) {
        case axis::x:
            return vec3(v.x, (cos_t * v.y) - (sin_t * v.z),
                        (sin_t * v.y) + (cos_t * v.z));
        case axis::y:
            return vec3((cos_t * v.x) + (sin_t * v.z), v.y,
                        (-sin_t * v.x) + (cos_t * v.z));
        case axis::z:
            return vec3((cos_t * v.x) - (sin_t * v.y),
                        (sin_t * v.x) + (cos_t * v.y), v.z);
    }
    std::abort();
}

/**
 * @brief Projects vector @param vec on the axis @param axis (eg
 * project(vec={1,2,3},axis={0,1,0}) = {0,2,0}). @param axis does not need to be
 * normalized.
 */
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

/**
 * @brief Projects vector @param vec on the plane defined by the vector pair
 * @param plane (eg project(vec={1,2,3},plane=({1,0,0}, {0,1,0}) = {1,2,0}).
 * @param plane vectors do not need to be normalized.
 *
 * Returns zero if the two vectors don't define a plane (ie if they are zero or
 * colinear) */
template <std::floating_point T>
[[nodiscard]] constexpr vec3<T> project(
    const vec3<T>& vec, const std::pair<vec3<T>, vec3<T>>& plane) noexcept {
    auto u = cross(plane.first, plane.second);
    T d2 = u.norm_sqr();
    if (d2 == 0.) {
        // console::get(default_consoles::math)
        //     ->warn(
        //         "The two given vectors ({} and {}) do not define a plane,
        //         they " "must be non zero and non colinear", plane.first,
        //         plane.second);
        return vec3<T>(0.);
    } else {
        return vec - (dot(vec, u) / d2 * u);
    }
}

// template <std::floating_point T>
// void rotate(const vec3<T>& v, vec3<T> axis, const double theta) {
//     axis.normalize();
//     double x = ((axis.x * axis.x * (1 - cos(theta))) + cos(theta)) * v.x;
// }