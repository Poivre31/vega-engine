#pragma once
#include <console/console.h>

#include <functional>

#include "math/coordinates.h"

namespace solver {

template <stable_space T>
class base_solver {
   public:
    virtual T iteration(const T& X, double t,
                        const std::function<T(T X, double t)>& dXdt,
                        double dt) = 0;

    void set_time(const double t) { _t = t; }
    [[nodiscard]] double get_time() const { return _t; }

    void set_state(const T& state) { _state = state; }
    [[nodiscard]] T get_state() const { return _state; }

    void set_initial_conditions(const T& state, const double t0) {
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

    T iterate(const double dt,
              const std::function<T(T X, double t)>& update_function) {
        _state = iteration(_state, _t, update_function, dt);
        _t += dt;
        return _state;
    }

    T solve(const double tf, const size_t N,
            const std::function<T(T X, double t)>& update_function) {
        if (!update_function) {
            console::get(default_consoles::math)
                ->error("Assign an update function before using the solver");
            return _state;
        } else if (N == 0) {
            return _state;
        }

        const double t0 = _t;
        const double dt = (tf - t0) / static_cast<double>(N);
        for (size_t i = 0; i < N + 1; i++) {
            _t += dt;
            _state = iteration(_state, _t, update_function, dt);
        }
        return _state;
    }

   private:
    double _t = 0;
    T _state{};
};

}  // namespace solver
