#pragma once

#include <console/console.h>

#include <concepts>
#include <random>

#include "math/types/coordinates.h"
#include "math/vec.h"

const size_t seed = 42;

class random {
   public:
    random() = delete;

    template <std::floating_point T>
    static T uniform(const T lower, const T upper) {
        return std::uniform_real_distribution<T>(lower, upper)(_engine);
    }

    template <std::integral T>
    static T uniform(const T lower, const T upper) {
        return std::uniform_int_distribution<T>(lower, upper)(_engine);
    }

    template <std::floating_point T>
    static vec3<T> uniform_vec3(const T lower, const T upper) {
        return vec3<T>(uniform(lower, upper), uniform(lower, upper),
                       uniform(lower, upper));
    }

    template <std::floating_point T>
    static vec3<T> uniform_vec3(const vec3<T>& lower, const vec3<T>& upper) {
        return vec3<T>(uniform(lower.x, upper.x), uniform(lower.y, upper.y),
                       uniform(lower.z, upper.z));
    }

    template <size_t N>
    static Rn<N> uniform_Rn(const double lower, const double upper) {
        Rn<N> X;
        for (auto& x : X) {
            x = uniform(lower, upper);
        }
        return X;
    }

    template <size_t N>
    static Rn<N> uniform_Rn(const Rn<N>& lower, const Rn<N>& upper) {
        Rn<N> X;
        for (size_t i = 0; i < N; i++) {
            X[i] = uniform(lower[i], upper[i]);
        }
        return X;
    }

   private:
    static thread_local inline std::default_random_engine _engine{seed};
};
