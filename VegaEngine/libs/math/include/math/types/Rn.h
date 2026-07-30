#pragma once
#include <console/console.h>

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>

#include "math/types/stable_space.H"

/**
 * @brief A fixed size vector derived from std::array<double> satisfying
 * stable_space requirements (mainly a vector addition law and a scalar
 * multiplication law). Also provides norms (L0,L1,L2,Linf), dot product,
 * min/max and fmt formatter.
 *
 * @tparam N
 */
template <size_t N>
class Rn : public std::array<double, N> {
   public:
    [[nodiscard]] constexpr friend Rn operator*(double a,
                                                const Rn& X) noexcept {
        Rn Y;
        for (size_t i = 0; i < N; i++) {
            Y[i] = X[i] * a;
        }
        return Y;
    }
    [[nodiscard]] constexpr friend Rn operator*(const Rn& X,
                                                double a) noexcept {
        return a * X;
    }

    [[nodiscard]] constexpr friend Rn operator+(const Rn& X,
                                                const Rn& Y) noexcept {
        Rn Z;
        for (size_t i = 0; i < N; i++) {
            Z[i] = X[i] + Y[i];
        }
        return Z;
    }

    [[nodiscard]] constexpr friend Rn operator-(const Rn& X,
                                                const Rn& Y) noexcept {
        Rn Z;
        for (size_t i = 0; i < N; i++) {
            Z[i] = X[i] - Y[i];
        }
        return Z;
    }

    [[nodiscard]] constexpr Rn operator-() const noexcept {
        Rn Y;
        for (size_t i = 0; i < N; i++) {
            Y[i] = -this->at(i);
        }
        return Y;
    }

    [[nodiscard]] friend constexpr bool operator==(const Rn& X,
                                                   const Rn& Y) noexcept {
        for (size_t i = 0; i < N; i++) {
            if (X[i] != Y[i]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr double dot(const Rn& v) const noexcept {
        double result = 0.;
        for (size_t i = 0; i < N; i++) {
            result += this->at(i) * v[i];
        }
        return result;
    }

    /** Returns number of non zero elements (L0 "norm") */
    [[nodiscard]] constexpr size_t norm_L0() const noexcept {
        size_t result = 0;
        for (size_t i = 0; i < N; i++) {
            result += static_cast<size_t>(this->at(i) != 0);
        }
        return result;
    }

    /** Returns sum of absolute values of elements (L1 norm) */
    [[nodiscard]] constexpr double norm_L1() const noexcept {
        double result = 0.;
        for (size_t i = 0; i < N; i++) {
            result += abs(this->at(i));
        }
        return result;
    }

    /** Returns square root of the sum of squares (L2 norm) */
    [[nodiscard]] double norm_L2() const noexcept {
        double result = 0.;
        for (size_t i = 0; i < N; i++) {
            result += this->at(i) * this->at(i);
        }
        return sqrt(result);
    }

    /** Returns the biggest element in magnitude (infinite norm)*/
    [[nodiscard]] constexpr double norm_inf() const noexcept {
        return max_abs();
    }

    /** Returns the biggest element */
    [[nodiscard]] constexpr double max() const noexcept {
        double _max = this->at(0);
        for (size_t i = 0; i < N; i++) {
            if (this->at(i) > _max) {
                _max = this->at(i);
            }
        }
        return _max;
    }

    /** Returns the biggest element in magnitude (equivalent to norm_inf())
     */
    [[nodiscard]] constexpr double max_abs() const noexcept {
        double _max = abs(this->at(0));
        for (size_t i = 0; i < N; i++) {
            if (abs(this->at(i)) > _max) {
                _max = abs(this->at(i));
            }
        }
        return _max;
    }

    /** Returns the smallest element */
    [[nodiscard]] constexpr double min() const noexcept {
        double _min = this->at(0);
        for (size_t i = 0; i < N; i++) {
            if (this->at(i) < _min) {
                _min = this->at(i);
            }
        }
        return _min;
    }

    /** Returns the smallest element in magnitude */
    [[nodiscard]] constexpr double min_abs() const noexcept {
        double _min = abs(this->at(0));
        for (size_t i = 0; i < N; i++) {
            if (abs(this->at(i)) < _min) {
                _min = abs(this->at(i));
            }
        }
        return _min;
    }

    /** Applies a function @param f to every element of the vector */
    [[nodiscard]] Rn transform(
        const std::function<double(double)>& f) const noexcept {
        Rn Y;
        for (size_t i = 0; i < N; i++) {
            Y[i] = f(this->at(i));
        }
        return Y;
    }
};

template <size_t N>
struct fmt::formatter<Rn<N>> : fmt::formatter<double> {
    auto format(Rn<N> v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v[0], ctx);

        for (size_t i = 1; i < N; i++) {
            out = fmt::format_to(out, ", ");
            ctx.advance_to(out);
            out = fmt::formatter<double>::format(v[i], ctx);
        }

        return fmt::format_to(out, ")");
    }
};