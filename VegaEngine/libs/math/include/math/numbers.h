#pragma once

#include <concepts>
#include <cstdint>
#include <numbers>

namespace math {

/**Signed integers or floating point numbers */
template <typename T>
concept numeric = std::signed_integral<T> || std::floating_point<T>;

using std::numbers::e;
using std::numbers::egamma;
using std::numbers::inv_pi;
using std::numbers::inv_sqrt3;
using std::numbers::inv_sqrtpi;
using std::numbers::ln10;
using std::numbers::ln2;
using std::numbers::log10e;
using std::numbers::log2e;
using std::numbers::phi;
using std::numbers::pi;
using std::numbers::sqrt2;
using std::numbers::sqrt3;

/** 2 * pi */
inline constexpr double tau = 6.283185307179586476925286766559005768;
/** sqrt(pi) */
inline constexpr double sqrtpi = 1.772453850905516027298167483341145182;
/** pi / 2 */
inline constexpr double pi_by_2 = 1.570796326794896619231321691639751442;
/** 3 * pi /2 */
inline constexpr double pi_3_by_2 = 4.712388980384689857693965074919254326;

}  // namespace math

/** Cartesian axis x, y and z */
enum class axis : std::uint8_t { x, y, z };
