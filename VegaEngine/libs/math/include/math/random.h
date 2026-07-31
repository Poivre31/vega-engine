#pragma once

#include <console/console.h>

#include <concepts>
#include <random>

#include "math/numbers.h"
#include "math/types.h"

/** A static class to generate random variables using Mersenne Twister 64
 * engine*/
class random {
   public:
    random() = delete;

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
        return vec3<T>(uniform(lower, upper), uniform(lower, upper),
                       uniform(lower, upper));
    }

    /** Vec3 of uniformly distributed reals (respectively integers) in [ @param
     * lower.x, @param upper.x [ (respectively ]), [ @param
     * lower.y, @param upper.y [ (respectively ])... */
    template <std::floating_point T>
    static vec3<T> uniform_vec3(const vec3<T>& lower, const vec3<T>& upper) {
        return vec3<T>(uniform(lower.x, upper.x), uniform(lower.y, upper.y),
                       uniform(lower.z, upper.z));
    }

    /** Array of @tparam N uniformly distributed doubles in [ @param lower,
     * @param upper [ */
    template <size_t N>
    static Rn<N> uniform_Rn(const double lower, const double upper) {
        Rn<N> X;
        for (auto& x : X) {
            x = uniform(lower, upper);
        }
        return X;
    }

    /** Array of @tparam N uniformly distributed doubles in [ @param lower[i],
     * @param upper[i] [ */
    template <size_t N>
    static Rn<N> uniform_Rn(const Rn<N>& lower, const Rn<N>& upper) {
        Rn<N> X;
        for (size_t i = 0; i < N; i++) {
            X[i] = uniform(lower[i], upper[i]);
        }
        return X;
    }

   private:
    static constexpr size_t _seed =
        42;  // For now fixed seed shared across threads for reproductability,
             // will change in the future
    static thread_local inline std::default_random_engine _engine{_seed};
};
