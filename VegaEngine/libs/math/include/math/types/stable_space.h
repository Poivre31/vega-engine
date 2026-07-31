#pragma once
#include <console/console.h>

#include <concepts>

namespace math {
/**
 * @brief Class that supports default initialisation, scalar multiplication and
 * binary addition (eg double, vec3...)
 *
 * @tparam T
 */
template <typename T>
concept stable_space = requires(T x, T y, double a) {
    { T{} } -> std::same_as<T>;
    { a * x } -> std::same_as<T>;
    { x * a } -> std::same_as<T>;
    { x + y } -> std::same_as<T>;
    { x - y } -> std::same_as<T>;
    { -x } -> std::same_as<T>;
};

}  // namespace math
