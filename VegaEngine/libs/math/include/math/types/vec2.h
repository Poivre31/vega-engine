#pragma once
#include <console/console.h>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "math/numbers.h"

template <math::numeric T>
class vec2 {
   public:
    T x{};
    T y{};

    vec2() = default;
    ~vec2() = default;

    vec2& operator=(const vec2& v) = default;
    vec2(vec2&& v) = default;
    vec2& operator=(vec2&& v) = default;

    constexpr explicit vec2(T a) : x(a), y(a) {}

    constexpr vec2(T x, T y) : x(x), y(y) {}

    constexpr vec2(const vec2& ref) : x(ref.x), y(ref.y) {}

    constexpr vec2(axis ax) noexcept
        requires std::floating_point<T>;

    template <math::numeric U>
    [[nodiscard]] constexpr explicit operator vec2<U>() const noexcept {
        return vec2<U>(static_cast<U>(x), static_cast<U>(y));
    }

    constexpr void set_zero() noexcept;
    constexpr void fill(T a) noexcept;
    constexpr void copy(const vec2& v) noexcept;

    [[nodiscard]] constexpr T sum() const noexcept;
    [[nodiscard]] constexpr size_t norm_L0() const noexcept;
    [[nodiscard]] constexpr T norm_L1() const noexcept;
    [[nodiscard]] constexpr T norm_inf() const noexcept;
    [[nodiscard]] constexpr T max() const noexcept;
    [[nodiscard]] constexpr T max_abs() const noexcept;
    [[nodiscard]] constexpr T min() const noexcept;
    [[nodiscard]] constexpr T min_abs() const noexcept;

    [[nodiscard]] T norm() const noexcept
        requires std::floating_point<T>;
    [[nodiscard]] constexpr T norm_sqr() const noexcept
        requires std::floating_point<T>;

    void normalize() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec2 normalized() const noexcept
        requires std::floating_point<T>;

    void round() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec2 rounded() const noexcept
        requires std::floating_point<T>;

    void floor() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec2 floored() const noexcept
        requires std::floating_point<T>;

    void ceil() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec2 ceiled() const noexcept
        requires std::floating_point<T>;

    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes included) */
    [[nodiscard]] constexpr bool is_within(T lower, T upper) noexcept;
    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes included) */
    [[nodiscard]] constexpr bool is_within(vec2 lower, vec2 upper) noexcept;

    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes excluded) */
    [[nodiscard]] constexpr bool is_strictly_within(T lower, T upper) noexcept;
    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes excluded) */
    [[nodiscard]] constexpr bool is_strictly_within(vec2 lower,
                                                    vec2 upper) noexcept;

    [[nodiscard]] constexpr T dot(const vec2& u) const noexcept;

    void print(const std::shared_ptr<spdlog::logger>& console =
                   console::get(default_consoles::math)) const;

    void print(const std::string& message,
               const std::shared_ptr<spdlog::logger>& console =
                   console::get(default_consoles::math)) const;

    void transform(const std::function<T(T)>& func);

    [[nodiscard]] vec2 transformed(const std::function<T(T)>& func) const;

    template <std::floating_point U>
    [[nodiscard]] vec2<U> transformed(const std::function<U(T)>& func) const
        requires std::integral<T>
    {
        return vec2<U>(func(x), func(y));
    }

    [[nodiscard]] constexpr bool operator==(const vec2& v) const noexcept {
        return (x == v.x && y == v.y);
    }

    [[nodiscard]] constexpr friend vec2 operator+(const vec2& u,
                                                  const vec2& v) noexcept {
        vec2 out;
        out.x = u.x + v.x;
        out.y = u.y + v.y;
        return out;
    }

    constexpr vec2& operator+=(const vec2& v) noexcept {
        x += v.x;
        y += v.y;
        return *this;
    }

    [[nodiscard]] constexpr friend vec2 operator-(const vec2& u,
                                                  const vec2& v) noexcept {
        vec2 out;
        out.x = u.x - v.x;
        out.y = u.y - v.y;
        return out;
    }

    constexpr vec2& operator-=(const vec2& v) noexcept {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    [[nodiscard]] constexpr vec2 operator-() const noexcept {
        vec2 out;
        out.x = -x;
        out.y = -y;
        return out;
    }

    [[nodiscard]] constexpr friend vec2 operator*(T a, const vec2& v) noexcept {
        vec2 out;
        out.x = v.x * a;
        out.y = v.y * a;
        return out;
    }

    [[nodiscard]] constexpr friend vec2 operator*(const vec2& v, T a) noexcept {
        return a * v;
    }

    [[nodiscard]] constexpr friend vec2 operator*(const vec2& u,
                                                  const vec2& v) noexcept {
        vec2 out;
        out.x = u.x * v.x;
        out.y = u.y * v.y;
        return out;
    }

    constexpr vec2& operator*=(T a) noexcept {
        x *= a;
        y *= a;
        return *this;
    }

    constexpr vec2& operator*=(const vec2& u) noexcept {
        x *= u.x;
        y *= u.y;
        return *this;
    }

    [[nodiscard]] constexpr friend vec2 operator/(const vec2& u, const vec2& v)
        requires std::floating_point<T>
    {
        if (v.x == 0 || v.y == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec2 by vec2 with some "
                "zero components)");
        }
        vec2 out;
        out.x = u.x / v.x;
        out.y = u.y / v.y;
        return out;
    }

    [[nodiscard]] constexpr friend vec2 operator/(const vec2& u, T a)
        requires std::floating_point<T>
    {
        if (a == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec2 by null number ");
        }
        vec2 out;
        out.x = u.x / a;
        out.y = u.y / a;
        return out;
    }

    constexpr vec2& operator/=(const vec2& v)
        requires std::floating_point<T>
    {
        if (v.x == 0 || v.y == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec2 by vec2 with some "
                "zero components)");
        }
        x /= v.x;
        y /= v.y;
        return *this;
    }

    template <typename U>
    constexpr vec2& operator/=(U a)
        requires std::floating_point<T>
    {
        if (a == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec2 by null number ");
        }
        x /= a;
        y /= a;
        return *this;
    }
};

using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2i = vec2<int32_t>;
using vec2l = vec2<int64_t>;

template <math::numeric T>
struct fmt::formatter<vec2<T>> : fmt::formatter<T> {
    auto format(vec2<T> v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<T>::format(v.x, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<T>::format(v.y, ctx);

        return fmt::format_to(out, ")");
    }
};