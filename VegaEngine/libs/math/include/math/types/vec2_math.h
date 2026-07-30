#pragma once
#include <concepts>

#include "math/types/vec2.h"

template <math::numeric T>
[[nodiscard]] constexpr T dot(const vec2<T>& u, const vec2<T>& v) noexcept {
    return u.dot(v);
}

template <std::floating_point T>
[[nodiscard]] inline vec2<T> cos(const vec2<T>& u) noexcept {
    return vec2<T>(std::cos(u.x), std::cos(u.y));
}

template <std::floating_point T>
[[nodiscard]] inline vec2<T> sin(const vec2<T>& u) noexcept {
    return vec2<T>(std::sin(u.x), std::sin(u.y));
}

template <std::floating_point T>
[[nodiscard]] inline vec2<T> tan(const vec2<T>& u) noexcept {
    return vec2<T>(std::tan(u.x), std::tan(u.y));
}

template <std::floating_point T>
[[nodiscard]] inline vec2<T> exp(const vec2<T>& u) noexcept {
    return vec2<T>(std::exp(u.x), std::exp(u.y));
}

/** Rotates vector according to anti-clockwise rotatation */
template <std::floating_point T>
[[nodiscard]] inline vec2<T> rotate(const vec2<T>& v, const double theta) {
    const double cos_t = std::cos(theta);
    const double sin_t = std::sin(theta);

    return vec2((cos_t * v.x) - (sin_t * v.y), (sin_t * v.x) + (cos_t * v.y));
}

/**
 * @brief Projects vector @param vec on the axis @param axis (eg
 * project(vec={1,2},axis={0,1}) = {0,2}). @param axis does not need to be
 * normalized.
 */
template <std::floating_point T>
[[nodiscard]] constexpr vec2<T> project(const vec2<T>& vec,
                                        const vec2<T>& axis) noexcept {
    double d2 = axis.norm_sqr();
    if (d2 == 0.) {
        return vec2<T>(0.);
    } else {
        return dot(vec, axis) / d2 * axis;
    }
}
