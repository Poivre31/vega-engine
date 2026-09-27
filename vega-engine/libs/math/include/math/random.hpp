#pragma once

#include <console/console.hpp>

#include <concepts>
#include <random>

#include "math/numbers.hpp"
#include "math/types.hpp"

namespace vega::math {

/** A static class to generate random variables using Mersenne Twister 64
 * engine*/
class random {
 public:
  random() = delete;

  /** Returns true with probability @param success_probability and false with probability @param 1 -
   * success_probability.
   * If @param success_probability < 0, always returns false and if @param success_probability > 1
   * always returns true.
   */
  template <std::floating_point T>
  static bool boolean(T success_probability) {
    return uniform(T(0.), T(1.)) <= success_probability;
  }

  /** Uniformly distributed random real in [ @param lower, @param upper [ */
  template <std::floating_point T>
  static T uniform(const T lower, const T upper) {
    return std::uniform_real_distribution<T>(lower, upper)(_engine);
  }

  /** Uniformly distributed random integer in [ @param lower, @param upper ]
   */
  template <std::integral T>
  static T uniform(const T lower, const T upper) {
    return std::uniform_int_distribution<T>(lower, upper)(_engine);
  }

  /** Vec3 of uniformly distributed reals (respectively integers) in [ @param
   * lower, @param upper [ (respectively ]) */
  template <math::numeric T>
  static vec3<T> uniform_vec3(const T lower, const T upper) {
    return vec3<T>(uniform(lower, upper), uniform(lower, upper), uniform(lower, upper));
  }

  /** Vec3 of uniformly distributed reals (respectively integers) in [ @param
   * lower.x, @param upper.x [ (respectively ]), [ @param
   * lower.y, @param upper.y [ (respectively ])... */
  template <std::floating_point T>
  static vec3<T> uniform_vec3(const vec3<T>& lower, const vec3<T>& upper) {
    return vec3<T>(uniform(lower.x, upper.x), uniform(lower.y, upper.y), uniform(lower.z, upper.z));
  }

  /** Uniformly distributed vec3 of reals on the surface of the sphere of radius @param r */
  template <std::floating_point T>
  static vec3<T> on_sphere(T r) {
    return spherical_to_cartesian(
        vec3<T>{r, std::acos(uniform(T(-1), T(1))), uniform(T(0), T(2 * constants::pi))}
    );
  }

  /** Uniformly distributed vec3 of reals in the ball of radius @param r */
  template <std::floating_point T>
  static vec3<T> in_ball(T r) {
    return spherical_to_cartesian(
        vec3<T>{
            r * std::sqrt(uniform(T(0), T(1))),
            std::acos(uniform(T(-1), T(1))),
            uniform(T(0), T(2 * constants::pi))
        }
    );
  }

  /** Uniformly distributed vec3 of reals on the surface of the unit sphere */
  template <std::floating_point T>
  static vec3<T> on_unit_sphere() {
    return on_sphere(T(1));
  }

  /** Uniformly distributed vec3 of reals in the unit ball */
  template <std::floating_point T>
  static vec3<T> in_unit_ball() {
    return in_ball(T(1));
  }

  /** Array of @tparam N uniformly distributed doubles in [ @param lower,
   * @param upper [ */
  template <size_t N>
  static rn<N> uniform_Rn(const double lower, const double upper) {
    rn<N> X;
    for (auto& x : X) {
      x = uniform(lower, upper);
    }
    return X;
  }

  /** Array of @tparam N uniformly distributed doubles in [ @param lower[i],
   * @param upper[i] [ */
  template <size_t N>
  static rn<N> uniform_Rn(const rn<N>& lower, const rn<N>& upper) {
    rn<N> X;
    for (size_t i = 0; i < N; i++) {
      X[i] = uniform(lower[i], upper[i]);
    }
    return X;
  }

 private:
  static constexpr size_t _seed = 42;  // For now fixed seed shared across threads for
                                       // reproductability, will change in the future
  static thread_local inline std::default_random_engine _engine{_seed};
};

}  // namespace vega::math