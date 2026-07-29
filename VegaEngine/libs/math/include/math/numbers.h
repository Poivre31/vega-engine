#pragma once

#include <numbers>
#include <type_traits>

template <typename T>
concept is_numeric = std::is_integral<T>() || std::is_floating_point<T>();

namespace math {
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
const double tau = 6.283185307179586476925286766559005768L;
/** sqrt(pi) */
const double sqrtpi = 1.772453850905516027298167483341145182L;
/** pi / 2 */
const double pi_by_2 = 1.570796326794896619231321691639751442L;
/** 3 * pi /2 */
const double pi_3_by_2 = 4.712388980384689857693965074919254326L;

}  // namespace math