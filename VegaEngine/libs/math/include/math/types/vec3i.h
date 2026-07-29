#pragma once
#include <console/console.h>

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdint>

template <std::floating_point T>
class vec3;

template <std::integral T>
class vec3i {
   public:
    T x{};
    T y{};
    T z{};

    vec3i() = default;
    ~vec3i() = default;

    vec3i& operator=(const vec3i& v) = default;
    vec3i(vec3i&& v) = default;
    vec3i& operator=(vec3i&& v) = default;

    constexpr explicit vec3i(T a) : x(a), y(a), z(a) {}

    constexpr vec3i(T x, T y, T z) : x(x), y(y), z(z) {}

    constexpr vec3i(const vec3i& ref) : x(ref.x), y(ref.y), z(ref.z) {}

    template <std::floating_point U>
    [[nodiscard]] constexpr explicit operator vec3<U>() const noexcept {
        return vec3i<T>(static_cast<T>(x), static_cast<T>(y),
                        static_cast<T>(z));
    }

    template <std::integral U>
    [[nodiscard]] constexpr explicit operator vec3i<U>() const noexcept {
        return vec3i<U>(static_cast<U>(x), static_cast<U>(y),
                        static_cast<U>(z));
    }

    constexpr void set_zero() noexcept {
        x = 0;
        y = 0;
        z = 0;
    }

    // template <std::floating_point U = double>
    // [[nodiscard]] U norm() const noexcept {
    //     return sqrt(static_cast<U>((x * x) + (y * y) + (z * z)));
    // }

    // [[nodiscard]] constexpr T norm_sqr() const noexcept {
    //     return (x * x) + (y * y) + (z * z);
    // }

    // template <std::floating_point U = double>
    // [[nodiscard]] vec3i<U> normalized() const noexcept {
    //     vec3i<U> v;
    //     double r = norm_sqr();
    //     if (r != 0) {
    //         v = x * static_cast<T>(1. / sqrt(r));
    //     }
    //     return v;
    // }

    [[nodiscard]] constexpr T sum() const noexcept { return x + y + z; }
    [[nodiscard]] constexpr size_t norm_L0() const noexcept {
        return static_cast<size_t>(x != 0) + static_cast<size_t>(y != 0) +
               static_cast<size_t>(z != 0);
    }
    [[nodiscard]] constexpr T norm_L1() const noexcept {
        return abs(x) + abs(y) + abs(z);
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

    void print() const {
        console::get(default_consoles::math)->info("{}", *this);
    }

    void print(const std::string& message) const {
        console::get(default_consoles::math)->info("{:s} {}", message, *this);
    }

    //     void print() const {
    //     std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    // }

    // void print(const std::string& message) const {
    //     std::cout << message << " (" << x << ", " << y << ", " << z << ")\n";
    // }

    void transform(const std::function<T(T)>& func) {
        x = func(x);
        y = func(y);
        z = func(z);
    }

    [[nodiscard]] vec3i transformed(const std::function<T(T)>& func) const {
        return vec3i(func(x), func(y), func(z));
    }

    template <std::floating_point U>
    [[nodiscard]] vec3i<U> transformed(const std::function<U(T)>& func) const {
        return vec3i<U>(func(x), func(y), func(z));
    }

    [[nodiscard]] constexpr bool operator==(const vec3i& v) const noexcept {
        return (x == v.x && y == v.y && z == v.z);
    }

    [[nodiscard]] constexpr friend vec3i operator*(T a,
                                                   const vec3i& v) noexcept {
        vec3i out;
        out.x = v.x * a;
        out.y = v.y * a;
        out.z = v.z * a;
        return out;
    }

    [[nodiscard]] constexpr friend vec3i operator*(const vec3i& v,
                                                   T a) noexcept {
        return a * v;
    }

    [[nodiscard]] constexpr friend vec3i operator*(const vec3i& u,
                                                   const vec3i& v) noexcept {
        vec3i out;
        out.x = u.x * v.x;
        out.y = u.y * v.y;
        out.z = u.z * v.z;
        return out;
    }

    constexpr vec3i& operator*=(T a) noexcept {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    constexpr vec3i& operator*=(const vec3i& u) noexcept {
        x *= u.x;
        y *= u.y;
        z *= u.z;
        return *this;
    }

    [[nodiscard]] constexpr friend vec3i operator+(const vec3i& u,
                                                   const vec3i& v) noexcept {
        vec3i out;
        out.x = u.x + v.x;
        out.y = u.y + v.y;
        out.z = u.z + v.z;
        return out;
    }

    constexpr vec3i& operator+=(const vec3i& v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    [[nodiscard]] constexpr friend vec3i operator-(const vec3i& u,
                                                   const vec3i& v) noexcept {
        vec3i out;
        out.x = u.x - v.x;
        out.y = u.y - v.y;
        out.z = u.z - v.z;
        return out;
    }

    constexpr vec3i& operator-=(const vec3i& v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    [[nodiscard]] constexpr vec3i operator-() const noexcept {
        vec3i out;
        out.x = -x;
        out.y = -y;
        out.z = -z;
        return out;
    }

    [[nodiscard]] constexpr T dot(const vec3i& u) const noexcept {
        return (x * u.x) + (y * u.y) + (z * u.z);
    }

    [[nodiscard]] constexpr vec3i cross(const vec3i& v) const noexcept {
        return vec3i((y * v.z) - (z * v.y), (z * v.x) - (x * v.z),
                     (x * v.y) - (y * v.x));
    }
};

using vec3ii = vec3i<int_fast32_t>;
using vec3iil = vec3i<int_fast64_t>;

template <typename T>
struct fmt::formatter<vec3i<T>> : fmt::formatter<int> {
    auto format(vec3i<T> v, format_context& ctx) const -> decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(), "(");

        ctx.advance_to(out);
        out = fmt::formatter<int>::format(v.x, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<int>::format(v.y, ctx);

        out = fmt::format_to(out, ", ");
        ctx.advance_to(out);
        out = fmt::formatter<int>::format(v.z, ctx);

        return fmt::format_to(out, ")");
    }
};
