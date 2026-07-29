

#include <gtest/gtest.h>

#include <cmath>
#include <functional>

#include "console/console.h"
#include "math/ode_solver.h"

double f1(double x, double t) { return x * cos(t); }
Rn<6> f2(Rn<6> x, double t) { return -0.3 * x; }

TEST(TestMath, TestODE) {
    double x0 = 1.;
    double tf = 2.;
    size_t n = 1000;
    solver::euler<double> solver;
    solver.set_initial_conditions(x0, 0.);
    EXPECT_NEAR(solver.solve(tf, n, f1), x0 * exp(sin(tf)), 0.01);
    console::get(default_consoles::math)
        ->info("Result of ODE solve is {:.5g}", solver.get_state());

    solver::euler<Rn<6>> solver_n;
    Rn<6> X0{1., 2., 3., 4., 5., 6.};
    solver_n.set_initial_conditions(X0, 0.);
    solver_n.solve(tf, n, f2);
    EXPECT_LE((solver_n.get_state() - X0 * exp(-tf * 0.3)).max_abs(), 0.01);
    console::get(default_consoles::math)
        ->info("Result of ODE solve is {:.5g}", solver_n.get_state()[0]);
}
