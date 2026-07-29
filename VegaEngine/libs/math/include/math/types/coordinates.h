#pragma once
#include <console/console.h>

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>

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

// template <stable_space T>
// class symplectic_view {
//    public:
//     operator std::pair<T, T>() const {
//         return std::make_pair(position, velocity);
//     }

//     [[nodiscard]] friend symplectic_view operator*(double a,
//                                                    const symplectic_view& X)
//                                                    {
//         return symplectic_view{a * X.position, a * X.velocity};
//     }
//     [[nodiscard]] friend symplectic_view operator*(const symplectic_view& X,
//                                                    double a) {
//         return symplectic_view{a * X.position, a * X.velocity};
//     }

//     [[nodiscard]] friend symplectic_view operator+(const symplectic_view& X,
//                                                    const symplectic_view& Y)
//                                                    {
//         return symplectic_view{X.position + Y.position,
//                                X.velocity + Y.velocity};
//     }

//     [[nodiscard]] friend symplectic_view operator-(const symplectic_view& X,
//                                                    const symplectic_view& Y)
//                                                    {
//         return symplectic_view{X.position - Y.position,
//                                X.velocity - Y.velocity};
//     }

//     [[nodiscard]] symplectic_view operator-() const {
//         return symplectic_view{-position, -velocity};
//     }

//     T position{};
//     T velocity{};
// };

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

// template <size_t N>
// using coordinates = Eigen::Vector<double, N>;

// using xyz = coordinates<3>;
// using vec3 = coordinates<3>;
// using xy = coordinates<2>;
// using vec2 = coordinates<2>;
// using polar = coordinates<2>;
// using cyl = coordinates<3>;
// using sph = coordinates<3>;

// template <typename T>
// std::vector<double> parse(std::vector<T> data, size_t index) {
//     std::vector<double> result(data.size());
//     for (size_t i = 0; i < data.size(); i++) {
//         result[i] = data[i][index];
//     }
//     return result;
// }

// template <typename T>
// std::vector<T> stride(std::vector<T> data, size_t stride) {
//     if (stride < 1) fmt::println("ERROR: stride must be positive");
//     std::vector<T> result;
//     for (size_t i = 0; i < data.size(); i += stride) {
//         result.push_back(data[i]);
//     }
//     return result;
// }

// template <typename T, typename U>
// std::vector<U> apply_element_wise(std::vector<T> X, std::function<U(T)> f) {
//     std::vector<U> Y(X.size());
//     for (size_t i = 0; i < X.size(); i++) {
//         Y[i] = f(X[i]);
//     }
//     return Y;
// }

// template <typename T, typename U>
// std::vector<U> apply_element_wise(std::vector<T> X, std::vector<T> Y,
//                                   std::function<U(T, T)> f) {
//     std::vector<U> Z(X.size());
//     for (size_t i = 0; i < X.size(); i++) {
//         Z[i] = f(X[i], Y[i]);
//     }
//     return Z;
// }

// vec3 get_radial_vector(xyz r) { return r.normalized(); }

// vec2 get_radial_vector(xy r) { return r.normalized(); }

// std::vector<polar> cart_to_polar(std::vector<xy> XY) {
//     std::vector<polar> pol(XY.size());
//     for (size_t i = 0; i < XY.size(); i++) {
//         pol[i] = {XY[i].norm(), atan2(XY[i][1], XY[i][0])};
//     }

//     return pol;
// }

// std::vector<xy> polar_to_cart(std::vector<polar> pol) {
//     std::vector<xy> XY(pol.size());
//     for (size_t i = 0; i < pol.size(); i++) {
//         XY[i] = {cos(pol[i][1]) * pol[i][0], sin(pol[i][1]) * pol[i][0]};
//     }

//     return XY;
// }

// size_t get_maximum_index(std::vector<double> data) {
//     size_t index = data.size() - 1;
//     double value = 0;
//     for (size_t i = 0; i < data.size() - 1; i++) {
//         if (data[i + 1] < data[i] && data[i] > value) {
//             value = data[i];
//             index = i;
//         }
//     }
//     return index;
// }

// template <typename T>
// std::vector<T> truncate_vector(std::vector<T> data, size_t max_index) {
//     std::vector<T> result(max_index + 1);
//     for (size_t i = 0; i < result.size(); i++) {
//         result[i] = data[i];
//     }
//     return result;
// }