#pragma once
#include <console/console.h>

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdint>

enum class axis : std::uint8_t { x, y, z };

template <std::integral T>
class vec3i;

template <std::floating_point T>
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

    constexpr vec3(axis ax) noexcept {
        x = 0., y = 0., z = 0.;
        switch (ax) {
            case axis::x:
                x = 1.;
                break;
            case axis::y:
                y = 1.;
                break;
            case axis::z:
                z = 1.;
                break;
        }
    }

    template <std::integral U>
    [[nodiscard]] constexpr explicit operator vec3i<U>() const noexcept {
        return vec3(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z));
    }

    template <std::floating_point U>
    [[nodiscard]] constexpr explicit operator vec3<U>() const noexcept {
        return vec3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    constexpr void set_zero() noexcept {
        x = 0.;
        y = 0.;
        z = 0.;
    }

    [[nodiscard]] T norm() const noexcept {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    [[nodiscard]] constexpr T norm_sqr() const noexcept {
        return (x * x) + (y * y) + (z * z);
    }

    void normalize() noexcept {
        T r = norm_sqr();
        if (r != 0) {
            *this *= static_cast<T>(1. / sqrt(r));
        }
    }

    [[nodiscard]] vec3 normalized() const noexcept {
        vec3 v(*this);
        double r = norm_sqr();
        if (r != 0) {
            v *= static_cast<T>(1. / sqrt(r));
        }
        return v;
    }

    [[nodiscard]] constexpr T sum() const noexcept { return x + y + z; }
    [[nodiscard]] constexpr T norm_L1() const noexcept {
        return abs(x) + abs(y) + abs(z);
    }
    [[nodiscard]] constexpr size_t norm_L0() const noexcept {
        return static_cast<size_t>(x != 0) + static_cast<size_t>(y != 0) +
               static_cast<size_t>(z != 0);
    }
    [[nodiscard]] constexpr T norm_inf() const noexcept { return max_abs(); }
    [[nodiscard]] constexpr T max() const noexcept {
        return std::max(x, std::max(y, z));
    }
    [[nodiscard]] constexpr T max_abs() const noexcept {
        return std::max(abs(x), std::max(abs(y), abs(z)));
    }
    [[nodiscard]] constexpr T min() const noexcept {
        return std::min(x, std::min(y, z));
    }
    [[nodiscard]] constexpr T min_abs() const noexcept {
        return std::min(abs(x), std::min(abs(y), abs(z)));
    }

    void round() noexcept {
        x = round(x);
        y = round(y);
        z = round(z);
    }
    [[nodiscard]] vec3 rounded() const noexcept {
        return vec3(round(x), round(y), round(z));
    }

    void floor() noexcept {
        x = floor(x);
        y = floor(y);
        z = floor(z);
    }
    [[nodiscard]] vec3 floored() const noexcept {
        return vec3(floor(x), floor(y), floor(z));
    }

    void ceil() noexcept {
        x = ceil(x);
        y = ceil(y);
        z = ceil(z);
    }
    [[nodiscard]] vec3 ceiled() const noexcept {
        return vec3(ceil(x), ceil(y), ceil(z));
    }

    void print() const {
        console::get(default_consoles::math)->info("{}", *this);
    }

    void print(const std::string& message) const {
        console::get(default_consoles::math)->info("{:s} {}", message, *this);
    }

    // vec3<bool> Equals(vec3<T> ref) {
    //     return vec3<bool>(x == ref.x, y == ref.y, z == ref.z);
    // }

    // vec3<bool> Less(vec3<T> ref) {
    //     return vec3<bool>(x < ref.x, y < ref.y, z < ref.z);
    // }

    // vec3<bool> Less(T ref) { return vec3<bool>(x < ref, y < ref, z < ref); }

    // vec3<bool> LessEq(vec3<T> ref) {
    //     return vec3<bool>(x <= ref.x, y <= ref.y, z <= ref.z);
    // }

    // vec3<bool> Greater(vec3<T> ref) {
    //     return vec3<bool>(x > ref.x, y > ref.y, z > ref.z);
    // }

    // vec3<bool> GreaterEq(vec3<T> ref) {
    //     return vec3<bool>(x >= ref.x, y >= ref.y, z >= ref.z);
    // }

    void transform(const std::function<T(T)>& func) {
        x = func(x);
        y = func(y);
        z = func(z);
    }

    [[nodiscard]] vec3 transformed(const std::function<T(T)>& func) const {
        return vec3(func(x), func(y), func(z));
    }

    [[nodiscard]] constexpr bool operator==(const vec3& v) const noexcept {
        return (x == v.x && y == v.y && z == v.z);
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

    [[nodiscard]] constexpr friend vec3 operator/(const vec3& u,
                                                  const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            console::get(default_consoles::math)
                ->critical(
                    "Division by zero (trying to divide vec3 by vec3 with some "
                    "zero components)");
            return u;
        }
        vec3 out;
        out.x = u.x / v.x;
        out.y = u.y / v.y;
        out.z = u.z / v.z;
        return out;
    }

    [[nodiscard]] constexpr friend vec3 operator/(const vec3& u, T a) {
        if (a == 0) {
            console::get(default_consoles::math)
                ->critical(
                    "Division by zero (trying to divide vec3 by null number");
            return u;
        }
        vec3 out;
        double inv = 1. / static_cast<double>(a);
        out.x = u.x * inv;
        out.y = u.y * inv;
        out.z = u.z * inv;
        return out;
    }

    [[nodiscard]] constexpr friend vec3 operator/(T a, const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            console::get(default_consoles::math)
                ->critical(
                    "Division by zero (trying to divide vec3 by vec3 with some "
                    "zero components)");
            return vec3(a);
        }
        return vec3(a / v.x, a / v.y, a / v.z);
    }

    constexpr vec3& operator/=(const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            console::get(default_consoles::math)
                ->critical(
                    "Division by zero (trying to divide vec3 by vec3 with some "
                    "zero components)");
            return *this;
        }
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    template <typename U>
    constexpr vec3& operator/=(U a) {
        if (a == 0) {
            console::get(default_consoles::math)
                ->critical(
                    "Division by zero (trying to divide vec3 by null number");
            return *this;
        }
        double inv = 1. / static_cast<double>(a);
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
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

    [[nodiscard]] constexpr T dot(const vec3& u) const noexcept {
        return (x * u.x) + (y * u.y) + (z * u.z);
    }

    [[nodiscard]] constexpr vec3 cross(const vec3& v) const noexcept {
        return vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z),
                    (x * v.y) - (y * v.x));
    }
};

using vec3f = vec3<float>;
using vec3d = vec3<double>;

template <typename T>
struct fmt::formatter<vec3<T>> : fmt::formatter<double> {
    auto format(vec3<T> v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.x, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.y, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<double>::format(v.z, ctx);

        return fmt::format_to(out, ")");
    }
};
