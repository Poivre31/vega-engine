#pragma once
#include <cstdlib>

#include "math/types/vec2.h"

/** Returns (0,0) if axis is axis::z */
template <math::numeric T>
constexpr vec2<T>::vec2(axis ax) noexcept
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
            break;
    }
}

template <math::numeric T>
constexpr void vec2<T>::set_zero() noexcept {
    fill(static_cast<T>(0));
}

template <math::numeric T>
constexpr void vec2<T>::fill(const T a) noexcept {
    x = a;
    y = a;
}

template <math::numeric T>
constexpr void vec2<T>::copy(const vec2& v) noexcept {
    x = v.x;
    y = v.y;
}

template <math::numeric T>
T vec2<T>::norm() const noexcept
    requires std::floating_point<T>
{
    return std::sqrt((x * x) + (y * y));
}

template <math::numeric T>
constexpr T vec2<T>::norm_sqr() const noexcept
    requires std::floating_point<T>
{
    return (x * x) + (y * y);
}

template <math::numeric T>
void vec2<T>::normalize() noexcept
    requires std::floating_point<T>
{
    T r = norm_sqr();
    if (r != 0) {
        *this *= static_cast<T>(1) / std::sqrt(r);
    }
}

template <math::numeric T>
vec2<T> vec2<T>::normalized() const noexcept
    requires std::floating_point<T>
{
    vec2 v(*this);
    T r = norm_sqr();
    if (r != 0) [[likely]] {
        v *= static_cast<T>(1) / std::sqrt(r);
    }
    return v;
}

template <math::numeric T>
constexpr T vec2<T>::sum() const noexcept {
    return x + y;
}

template <math::numeric T>
constexpr size_t vec2<T>::norm_L0() const noexcept {
    return static_cast<size_t>(x != 0) + static_cast<size_t>(y != 0);
}

template <math::numeric T>
constexpr T vec2<T>::norm_L1() const noexcept {
    return std::abs(x) + std::abs(y);
}

template <math::numeric T>
constexpr T vec2<T>::norm_inf() const noexcept {
    return max_abs();
}

template <math::numeric T>
constexpr T vec2<T>::max() const noexcept {
    return std::max(x, y);
}

template <math::numeric T>
constexpr T vec2<T>::max_abs() const noexcept {
    return std::max(std::abs(x), std::abs(y));
}

template <math::numeric T>
constexpr T vec2<T>::min() const noexcept {
    return std::min(x, y);
}

template <math::numeric T>
constexpr T vec2<T>::min_abs() const noexcept {
    return std::min(std::abs(x), std::abs(y));
}

template <math::numeric T>
void vec2<T>::round() noexcept
    requires std::floating_point<T>
{
    x = std::round(x);
    y = std::round(y);
}
template <math::numeric T>
vec2<T> vec2<T>::rounded() const noexcept
    requires std::floating_point<T>
{
    return vec2(std::round(x), std::round(y));
}

template <math::numeric T>
void vec2<T>::floor() noexcept
    requires std::floating_point<T>
{
    x = std::floor(x);
    y = std::floor(y);
}
template <math::numeric T>
vec2<T> vec2<T>::floored() const noexcept
    requires std::floating_point<T>
{
    return vec2(std::floor(x), std::floor(y));
}

template <math::numeric T>
void vec2<T>::ceil() noexcept
    requires std::floating_point<T>
{
    x = std::ceil(x);
    y = std::ceil(y);
}
template <math::numeric T>
vec2<T> vec2<T>::ceiled() const noexcept
    requires std::floating_point<T>
{
    return vec2(std::ceil(x), std::ceil(y));
}

template <math::numeric T>
constexpr T vec2<T>::dot(const vec2& u) const noexcept {
    return (x * u.x) + (y * u.y);
}

template <math::numeric T>
void vec2<T>::print(const std::shared_ptr<spdlog::logger>& console) const {
    console->info("{}", *this);
}

template <math::numeric T>
void vec2<T>::print(const std::string& message,
                    const std::shared_ptr<spdlog::logger>& console) const {
    console->info("{:s} {}", message, *this);
}

template <math::numeric T>
void vec2<T>::transform(const std::function<T(T)>& func) {
    x = func(x);
    y = func(y);
}

template <math::numeric T>
vec2<T> vec2<T>::transformed(const std::function<T(T)>& func) const {
    return vec2(func(x), func(y));
}
