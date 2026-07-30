#pragma once
#include <console/console.h>

#include <functional>
#include <stdexcept>

#include "math/types/stable_space.h"

namespace solver {

/**
 * @brief The base class to solve ODEs. You can create a solver by publicaly
 * inhereting from this base class and implementing the iteration() function
 * that matches your numerical ODE method. See 'euler', 'RK4' and such for
 * implementation exemples.

 * Usage is as follows:
 *  - Create a solver solver::method<T>
 *  - Set initial conditions (initial state and time) at the same time or one by
 * one using the appropriate function call
 *  - Either run 'iterate' (to advance one timestep) or 'solve' (to iterate
 * until given final time), providing the derivative function used to update the
 * state (eg f'(t)=3f(t)+t -> update_function(f,t) = 3*f+t)
 *
 * At all time you can access the stored state and time using the appropriate
 * getters.
 *
 * @tparam T is the unknown variable's type (eg double or vec3 but might be any
 * type that satisfies 'stable_space' criterias)
 */
template <math::stable_space T>
class base_solver {
   public:
    virtual ~base_solver() = default;

    [[nodiscard]] virtual T iteration(
        const T& X, double t, const std::function<T(T X, double t)>& dXdt,
        double dt) const = 0;

    constexpr void set_time(const double t) noexcept { _t = t; }
    [[nodiscard]] constexpr double get_time() const noexcept { return _t; }

    constexpr void set_state(const T& state) noexcept { _state = state; }
    [[nodiscard]] constexpr T get_state() const noexcept { return _state; }

    constexpr void set_initial_conditions(const T& state,
                                          const double t0) noexcept {
        _t = t0;
        _state = state;
    }

    // void set_update_function(
    //     const std::function<T(T X, double t)> update_function) {
    //     _update_function = update_function;
    // }
    // [[nodiscard]] const std::function<T(T X, double t)>&
    // get_update_function()
    //     const {
    //     return _update_function;
    // }

    T iterate(const double dt, const std::function<T(T X, double t)>& dXdt) {
        _state = iteration(_state, _t, dXdt, dt);
        _t += dt;
        return _state;
    }

    T solve(const double tf, const size_t N,
            const std::function<T(T X, double t)>& dXdt) {
        if (!dXdt) {
            throw std::invalid_argument("Function dXdt is null");
        }
        if (N == 0) {
            return _state;
        }

        const double t0 = _t;
        const double dt = (tf - t0) / static_cast<double>(N);
        for (size_t i = 0; i < N; i++) {
            _state = iteration(_state, _t, dXdt, dt);
            _t += dt;
        }
        return _state;
    }

   private:
    double _t = 0;
    T _state{};
};

}  // namespace solver
