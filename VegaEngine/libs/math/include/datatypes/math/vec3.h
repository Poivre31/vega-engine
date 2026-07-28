#pragma once
#include <console/console.h>

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdint>

enum class axis : std::uint8_t { x, y, z };

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

    vec3(T a) : x(a), y(a), z(a) {}

    vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    vec3(const vec3& ref) : x(ref.x), y(ref.y), z(ref.z) {}

    vec3(axis ax) {
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

    void set_zero() {
        x = 0.;
        y = 0.;
        z = 0.;
    }

    [[nodiscard]] double norm() const {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    [[nodiscard]] double norm_sqr() const {
        return (x * x) + (y * y) + (z * z);
    }

    void normalize() {
        double r = norm_sqr();
        if (r != 0) {
            *this *= static_cast<T>(1. / sqrt(r));
        }
    }

    [[nodiscard]] vec3 normalized() const {
        vec3 v(*this);
        double r = norm_sqr();
        if (r != 0) {
            v *= static_cast<T>(1. / sqrt(r));
        }
        return v;
    }

    [[nodiscard]] double sum() const { return x + y + z; }
    [[nodiscard]] double norm_L1() const { return abs(x) + abs(y) + abs(z); }
    [[nodiscard]] size_t norm_L0() const {
        return static_cast<size_t>(x != 0) + static_cast<size_t>(y != 0) +
               static_cast<size_t>(z != 0);
    }
    [[nodiscard]] double max() const { return std::max(x, std::max(y, z)); }
    [[nodiscard]] double max_abs() const {
        return std::max(abs(x), std::max(abs(y), abs(z)));
    }
    [[nodiscard]] double min() const { return std::min(x, std::min(y, z)); }
    [[nodiscard]] double min_abs() const {
        return std::min(abs(x), std::min(abs(y), abs(z)));
    }

    void round() {
        x = round(x);
        y = round(y);
        z = round(z);
    }
    [[nodiscard]] vec3 rounded() const {
        return vec3(round(x), round(y), round(z));
    }

    void floor() {
        x = floor(x);
        y = floor(y);
        z = floor(z);
    }
    [[nodiscard]] vec3 floored() const {
        return vec3(floor(x), floor(y), floor(z));
    }

    void ceil() {
        x = ceil(x);
        y = ceil(y);
        z = ceil(z);
    }
    [[nodiscard]] vec3 ceiled() const {
        return vec3(ceil(x), ceil(y), ceil(z));
    }

    void print() const { _console->info("{}", *this); }

    void print(const std::string& message) const {
        _console->info("{:s} {}", message, *this);
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

    void apply_element_wise(const std::function<T(T)>& func) {
        x = func(x);
        y = func(y);
        z = func(z);
    }

    [[nodiscard]] vec3 applied_element_wise(
        const std::function<T(T)>& func) const {
        return vec3(func(x), func(y), func(z));
    }

    template <std::floating_point U>
    operator vec3<U>() const {
        return vec3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    bool operator==(const vec3& v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    friend vec3 operator*(T a, const vec3& v) {
        vec3 out;
        out.x = v.x * a;
        out.y = v.y * a;
        out.z = v.z * a;
        return out;
    }

    friend vec3 operator*(const vec3& v, T a) { return a * v; }

    friend vec3 operator*(const vec3& u, const vec3& v) {
        vec3 out;
        out.x = u.x * v.x;
        out.y = u.y * v.y;
        out.z = u.z * v.z;
        return out;
    }

    vec3& operator*=(T a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    vec3& operator*=(const vec3& u) {
        x *= u.x;
        y *= u.y;
        z *= u.z;
        return *this;
    }

    friend vec3 operator/(const vec3& u, const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            _console->critical(
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

    friend vec3 operator/(const vec3& u, T a) {
        if (a == 0) {
            _console->critical(
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

    friend vec3 operator/(T a, const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            _console->critical(
                "Division by zero (trying to divide vec3 by vec3 with some "
                "zero components)");
            return vec3(a);
        }
        return vec3(a / v.x, a / v.y, a / v.z);
    }

    vec3& operator/=(const vec3& v) {
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            _console->critical(
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
    vec3& operator/=(U a) {
        if (a == 0) {
            _console->critical(
                "Division by zero (trying to divide vec3 by null number");
            return *this;
        }
        double inv = 1. / static_cast<double>(a);
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    friend vec3 operator+(const vec3& u, const vec3& v) {
        vec3 out;
        out.x = u.x + v.x;
        out.y = u.y + v.y;
        out.z = u.z + v.z;
        return out;
    }

    vec3& operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    friend vec3 operator-(const vec3& u, const vec3& v) {
        vec3 out;
        out.x = u.x - v.x;
        out.y = u.y - v.y;
        out.z = u.z - v.z;
        return out;
    }

    vec3& operator-=(const vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    vec3 operator-() const {
        vec3 out;
        out.x = -x;
        out.y = -y;
        out.z = -z;
        return out;
    }

    T dot(const vec3& u) const { return (x * u.x) + (y * u.y) + (z * u.z); }

    inline static const auto _console =
        console::create_or_get("VegaEngine.math");
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
