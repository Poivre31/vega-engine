#include <nanobench.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "console/console.h"
#include "math/ode_solver.h"
#include "math/types.h"

// template <size_t N>
// symplectic_view<Rn<N>> g(symplectic_view<Rn<N>> X, double t) {
//     auto dXdt(X);
//     for (size_t i = 0; i < N; i++) {
//         dXdt.position.at(i) = X.velocity.at(i);
//     }
//     for (size_t i = 0; i < N; i++) {
//         double a_i = 0;
//         for (size_t j = 0; j < N; j++) {
//             if (i != j) {
//                 a_i += std::copysign(
//                     1 / (1 + ((X.position.at(j) - X.position.at(i)) *
//                               (X.position.at(j) - X.position.at(i)))),
//                     X.position.at(j) - X.position.at(i));
//             }
//         }
//         dXdt.velocity.at(i) = a_i;
//     }
//     return dXdt;
// }

// template <size_t N>
// Rn<N> g2(Rn<N> positions, Rn<N> velocities, double t) {
//     Rn<N> acceleration;
//     for (size_t i = 0; i < N; i++) {
//         double a_i = 0;
//         for (size_t j = 0; j < N; j++) {
//             if (i != j) {
//                 a_i += std::copysign(
//                     1 / (1 + ((positions.at(j) - positions.at(i)) *
//                               (positions.at(j) - positions.at(i)))),
//                     positions.at(j) - positions.at(i));
//             }
//         }
//         acceleration.at(i) = a_i;
//     }
//     return acceleration;
// }

const size_t N = 10;
const Rn<N> x0{1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};

Rn<N> unabstracted(double t0, double tf, size_t n) {
    Rn<N> x(x0);
    double dt = (tf - t0) / double(n);
    for (size_t i = 0; i < n; i++) {
        x = x - 0.3 * x * dt;
    }
    return x;
}

int main() {
    ankerl::nanobench::Bench bench;
    console::get()->set_level(level::info);
    console::get(default_consoles::math)->set_level(level::info);
    Rn<N> result{};

    solver::euler<Rn<N>> _solver;
    // _solver.set_update_function([](Rn<N> x, double t) { return -0.3 * x; });
    bench.warmup(1);
    for (size_t n = 10; n <= static_cast<size_t>(1e5); n *= 10) {
        bench.complexityN(n).run(
            "Solved f'(x)=a*f(x) with euler (sovler class)", [&] {
                _solver.set_initial_conditions(x0, 0);
                result = _solver.solve(
                    3, n, [](Rn<N> x, double t) { return -0.3 * x; });
            });
    }
    console::get()->info("Method 1 (class) result : {:.10g}, {:.10g}",
                         result[0], result[9]);
    std::cout << bench.complexityBigO() << "\n";

    bench = ankerl::nanobench::Bench();
    for (size_t n = 10; n <= static_cast<size_t>(1e5); n *= 10) {
        bench.complexityN(n).run("Solved f'(x)=a*f(x) with euler (inlined)",
                                 [&] { result = unabstracted(0, 3, n); });
    }
    console::get()->info("Method 3 (inlined) result : {:.10g}, {:.10g}",
                         result[0], result[9]);
    std::cout << bench.complexityBigO() << "\n";

    // bench = ankerl::nanobench::Bench();

    // solver_euler<symplectic_view<Rn<50>>> _solver2;

    // symplectic_view<Rn<50>> X0;
    // for (auto& x : X0.position) {
    //     x = ((double(rand()) / RAND_MAX) - 0.5) * 20;
    // }

    // _solver2.set_update_function(g<50>);

    // for (size_t n = 10; n <= static_cast<size_t>(1e4); n *= 10) {
    //     bench.complexityN(n).run("Solved", [&] {
    //         _solver2.set_initial_conditions(X0, 0);
    //         _solver2.solve(1, n);
    //     });
    // }
    // std::cout << bench.complexityBigO() << "\n";

    // solver_euler_II<Rn<50>> _solver3;
    // _solver3.set_acceleration_function(g2<50>);

    // Rn<50> pos0;
    // for (size_t i = 0; i < 50; i++) {
    //     pos0.at(i) = X0.position.at(i);
    // }
    // Rn<50> vel0{};

    // for (size_t n = 10; n <= static_cast<size_t>(1e4); n *= 10) {
    //     bench.complexityN(n).run(
    //         "Solved N body simulation with Euler method", [&] {
    //             console::get()->info(
    //                 "Method 2 : {}",
    //                 _solver3
    //                     .solve({.position = pos0, .velocity = vel0}, 0, 3, n)
    //                     .position[0]);
    //         });
    // }
    // std::cout << bench.complexityBigO() << "\n";
}
