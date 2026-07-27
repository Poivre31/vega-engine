#pragma once
#include <console/console.h>

#include <functional>

#include "math/solver.h"

namespace solver {

template <stable_space T>
class euler : public base_solver<T> {
    T iteration(const T& X, const double t,
                const std::function<T(T X, double t)>& dXdt,
                const double dt) final {
        return X + (dt * dXdt(X, t));
    }
};
}  // namespace solver
