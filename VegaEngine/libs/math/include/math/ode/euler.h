#pragma once
#include <console/console.h>

#include <functional>

#include "math/ode/solver.h"

namespace solver {

/**
 * @brief The first order explicit euler method to solve ODEs.
 * Usage is as follows:
 *  - Create a solver solver::euler<T>
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
class euler : public base_solver<T> {
    T iteration(const T& X, const double t,
                const std::function<T(T X, double t)>& dXdt,
                const double dt) const final {
        return X + (dt * dXdt(X, t));
    }
};
}  // namespace solver
