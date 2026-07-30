#pragma once
#include <cstdlib>

#include "math/types/vec3.h"

template <math::numeric T>
constexpr vec3<T>::vec3(axis ax) noexcept
    requires std::floating_point<T>
{
    set_zero();
    switch (ax) {
        case axis::x:
            x = static_cast<T>(1);
            break;
        case axis::y:
            y = static_cast<T>(1);
            break;
        case axis::z:
            z = static_cast<T>(1);
            break;
    }
}

template <math::numeric T>
constexpr void vec3<T>::set_zero() noexcept {
    fill(static_cast<T>(0));
}

template <math::numeric T>
constexpr void vec3<T>::fill(const T a) noexcept {
    x = a;
    y = a;
    z = a;
}

template <math::numeric T>
constexpr void vec3<T>::copy(const vec3& v) noexcept {
    x = v.x;
    y = v.y;
    z = v.z;
}

template <math::numeric T>
T vec3<T>::norm() const noexcept
    requires std::floating_point<T>
{
    return std::sqrt((x * x) + (y * y) + (z * z));
}

template <math::numeric T>
constexpr T vec3<T>::norm_sqr() const noexcept
    requires std::floating_point<T>
{
    return (x * x) + (y * y) + (z * z);
}

template <math::numeric T>
void vec3<T>::normalize() noexcept
    requires std::floating_point<T>
{
    T r = norm_sqr();
    if (r != 0) {
        *this *= static_cast<T>(1) / std::sqrt(r);
    }
}

template <math::numeric T>
vec3<T> vec3<T>::normalized() const noexcept
    requires std::floating_point<T>
{
    vec3 v(*this);
    T r = norm_sqr();
    if (r != 0) [[likely]] {
        v *= static_cast<T>(1) / std::sqrt(r);
    }
    return v;
}

template <math::numeric T>
constexpr T vec3<T>::sum() const noexcept {
    return x + y + z;
}

template <math::numeric T>
constexpr size_t vec3<T>::norm_L0() const noexcept {
    return static_cast<size_t>(x != 0) + static_cast<size_t>(y != 0) +
           static_cast<size_t>(z != 0);
}

template <math::numeric T>
constexpr T vec3<T>::norm_L1() const noexcept {
    return std::abs(x) + std::abs(y) + std::abs(z);
}

template <math::numeric T>
constexpr T vec3<T>::norm_inf() const noexcept {
    return max_abs();
}

template <math::numeric T>
constexpr T vec3<T>::max() const noexcept {
    return std::max(x, std::max(y, z));
}

template <math::numeric T>
constexpr T vec3<T>::max_abs() const noexcept {
    return std::max(std::abs(x), std::max(std::abs(y), std::abs(z)));
}

template <math::numeric T>
constexpr T vec3<T>::min() const noexcept {
    return std::min(x, std::min(y, z));
}

template <math::numeric T>
constexpr T vec3<T>::min_abs() const noexcept {
    return std::min(std::abs(x), std::min(std::abs(y), std::abs(z)));
}

template <math::numeric T>
void vec3<T>::round() noexcept
    requires std::floating_point<T>
{
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
}
template <math::numeric T>
vec3<T> vec3<T>::rounded() const noexcept
    requires std::floating_point<T>
{
    return vec3(std::round(x), std::round(y), std::round(z));
}

template <math::numeric T>
void vec3<T>::floor() noexcept
    requires std::floating_point<T>
{
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
}
template <math::numeric T>
vec3<T> vec3<T>::floored() const noexcept
    requires std::floating_point<T>
{
    return vec3(std::floor(x), std::floor(y), std::floor(z));
}

template <math::numeric T>
void vec3<T>::ceil() noexcept
    requires std::floating_point<T>
{
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
}
template <math::numeric T>
vec3<T> vec3<T>::ceiled() const noexcept
    requires std::floating_point<T>
{
    return vec3(std::ceil(x), std::ceil(y), std::ceil(z));
}

template <math::numeric T>
constexpr T vec3<T>::dot(const vec3& u) const noexcept {
    return (x * u.x) + (y * u.y) + (z * u.z);
}
template <math::numeric T>
constexpr vec3<T> vec3<T>::cross(const vec3& v) const noexcept {
    return vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z),
                (x * v.y) - (y * v.x));
}

template <math::numeric T>
void vec3<T>::print(const std::shared_ptr<spdlog::logger>& console) const {
    console->info("{}", *this);
}

template <math::numeric T>
void vec3<T>::print(const std::string& message,
                    const std::shared_ptr<spdlog::logger>& console) const {
    console->info("{:s} {}", message, *this);
}

template <math::numeric T>
void vec3<T>::transform(const std::function<T(T)>& func) {
    x = func(x);
    y = func(y);
    z = func(z);
}

template <math::numeric T>
vec3<T> vec3<T>::transformed(const std::function<T(T)>& func) const {
    return vec3(func(x), func(y), func(z));
}
