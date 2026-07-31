#pragma once
#include <utility>

#include "math/types/stable_space.h"


/**
 * @brief Provides the stable_space requirements to a (position,velocity) pair.
 *
 * @tparam T, the base stable_space used by position and velocity
 */
template <math::stable_space T>
class symplectic_view {
   public:
    operator std::pair<T, T>() const {
        return std::make_pair(position, velocity);
    }

    [[nodiscard]] friend symplectic_view operator*(double a,
                                                   const symplectic_view& X) {
        return symplectic_view{a * X.position, a * X.velocity};
    }
    [[nodiscard]] friend symplectic_view operator*(const symplectic_view& X,
                                                   double a) {
        return symplectic_view{a * X.position, a * X.velocity};
    }

    [[nodiscard]] friend symplectic_view operator+(const symplectic_view& X,
                                                   const symplectic_view& Y) {
        return symplectic_view{X.position + Y.position,
                               X.velocity + Y.velocity};
    }

    [[nodiscard]] friend symplectic_view operator-(const symplectic_view& X,
                                                   const symplectic_view& Y) {
        return symplectic_view{X.position - Y.position,
                               X.velocity - Y.velocity};
    }

    [[nodiscard]] symplectic_view operator-() const {
        return symplectic_view{-position, -velocity};
    }

    T position{};
    T velocity{};
};