#pragma once
#include <console/console.h>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "math/numbers.h"

template <math::numeric T>
class vec3 {
   public:
    T x{};
    T y{};
    T z{};

    vec3() = default;
    ~vec3() = default;

    vec3& operator=(const vec3& v) = default;
    vec3(vec3&& v) = default;
    vec3& operator=(vec3&& v) = default;

    constexpr explicit vec3(T a) : x(a), y(a), z(a) {}

    constexpr vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    constexpr vec3(const vec3& ref) : x(ref.x), y(ref.y), z(ref.z) {}

    constexpr vec3(axis ax) noexcept
        requires std::floating_point<T>;

    template <math::numeric U>
    [[nodiscard]] constexpr explicit operator vec3<U>() const noexcept {
        return vec3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    constexpr void set_zero() noexcept;
    constexpr void fill(T a) noexcept;
    constexpr void copy(const vec3& v) noexcept;

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
    [[nodiscard]] vec3 normalized() const noexcept
        requires std::floating_point<T>;

    void round() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec3 rounded() const noexcept
        requires std::floating_point<T>;

    void floor() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec3 floored() const noexcept
        requires std::floating_point<T>;

    void ceil() noexcept
        requires std::floating_point<T>;
    [[nodiscard]] vec3 ceiled() const noexcept
        requires std::floating_point<T>;

    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes included) */
    [[nodiscard]] constexpr bool is_within(T lower, T upper) noexcept;
    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes included) */
    [[nodiscard]] constexpr bool is_within(vec3 lower, vec3 upper) noexcept;

    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes excluded) */
    [[nodiscard]] constexpr bool is_strictly_within(T lower, T upper) noexcept;
    /** Checks if x, y and z are in the [ @param lower, @param upper ] range
     * (bornes excluded) */
    [[nodiscard]] constexpr bool is_strictly_within(vec3 lower,
                                                    vec3 upper) noexcept;

    [[nodiscard]] constexpr T dot(const vec3& u) const noexcept;
    [[nodiscard]] constexpr vec3 cross(const vec3& v) const noexcept;

    void print(const std::shared_ptr<spdlog::logger>& console =
                   console::get(default_consoles::math)) const;

    void print(const std::string& message,
               const std::shared_ptr<spdlog::logger>& console =
                   console::get(default_consoles::math)) const;

    void transform(const std::function<T(T)>& func);

    [[nodiscard]] vec3 transformed(const std::function<T(T)>& func) const;

    template <std::floating_point U>
    [[nodiscard]] vec3<U> transformed(const std::function<U(T)>& func) const
        requires std::integral<T>
    {
        return vec3<U>(func(x), func(y), func(z));
    }

    [[nodiscard]] constexpr bool operator==(const vec3& v) const noexcept {
        return (x == v.x && y == v.y && z == v.z);
    }

    [[nodiscard]] constexpr friend vec3 operator+(const vec3& u,
                                                  const vec3& v) noexcept {
        vec3 out;
        out.x = u.x + v.x;
        out.y = u.y + v.y;
        out.z = u.z + v.z;
        return out;
    }

    constexpr vec3& operator+=(const vec3& v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    [[nodiscard]] constexpr friend vec3 operator-(const vec3& u,
                                                  const vec3& v) noexcept {
        vec3 out;
        out.x = u.x - v.x;
        out.y = u.y - v.y;
        out.z = u.z - v.z;
        return out;
    }

    constexpr vec3& operator-=(const vec3& v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    [[nodiscard]] constexpr vec3 operator-() const noexcept {
        vec3 out;
        out.x = -x;
        out.y = -y;
        out.z = -z;
        return out;
    }

    [[nodiscard]] constexpr friend vec3 operator*(T a, const vec3& v) noexcept {
        vec3 out;
        out.x = v.x * a;
        out.y = v.y * a;
        out.z = v.z * a;
        return out;
    }

    [[nodiscard]] constexpr friend vec3 operator*(const vec3& v, T a) noexcept {
        return a * v;
    }

    [[nodiscard]] constexpr friend vec3 operator*(const vec3& u,
                                                  const vec3& v) noexcept {
        vec3 out;
        out.x = u.x * v.x;
        out.y = u.y * v.y;
        out.z = u.z * v.z;
        return out;
    }

    constexpr vec3& operator*=(T a) noexcept {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    constexpr vec3& operator*=(const vec3& u) noexcept {
        x *= u.x;
        y *= u.y;
        z *= u.z;
        return *this;
    }

    [[nodiscard]] constexpr friend vec3 operator/(const vec3& u, const vec3& v)
        requires std::floating_point<T>
    {
        if (v.x == 0 || v.y == 0 || v.z == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec3 by vec3 with some "
                "zero components)");
        }
        vec3 out;
        out.x = u.x / v.x;
        out.y = u.y / v.y;
        out.z = u.z / v.z;
        return out;
    }

    [[nodiscard]] constexpr friend vec3 operator/(const vec3& u, T a)
        requires std::floating_point<T>
    {
        if (a == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec3 by null number ");
        }
        vec3 out;
        out.x = u.x / a;
        out.y = u.y / a;
        out.z = u.z / a;
        return out;
    }

    constexpr vec3& operator/=(const vec3& v)
        requires std::floating_point<T>
    {
        if (v.x == 0 || v.y == 0 || v.z == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec3 by vec3 with some "
                "zero components)");
        }
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    template <typename U>
    constexpr vec3& operator/=(U a)
        requires std::floating_point<T>
    {
        if (a == 0) [[unlikely]] {
            throw std::runtime_error(
                "Division by zero (trying to divide vec3 by null number ");
        }
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }
};

using vec3f = vec3<float>;
using vec3d = vec3<double>;
using vec3i = vec3<int32_t>;
using vec3l = vec3<int64_t>;

template <math::numeric T>
struct fmt::formatter<vec3<T>> : fmt::formatter<T> {
    auto format(vec3<T> v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<T>::format(v.x, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<T>::format(v.y, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<T>::format(v.z, ctx);

        return fmt::format_to(out, ")");
    }
};