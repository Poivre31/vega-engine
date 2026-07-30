#pragma once

namespace math {

/** Checks if @param x is in the [ @param lower, @param upper ] range (bornes
 * included) */
template <typename T>
[[nodiscard]] constexpr bool is_within(T x, T lower, T upper) noexcept {
    return x <= upper && x >= lower;
}

/** Checks if @param x is in the ] @param lower, @param upper [ range (bornes
 * excluded) */
template <typename T>
[[nodiscard]] constexpr bool is_strictly_within(T x, T lower,
                                                T upper) noexcept {
    return x < upper && x > lower;
}
}  // namespace math
