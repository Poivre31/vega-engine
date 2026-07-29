#include <console/console.h>
#include <math/integration.h>
#include <math/numbers.h>
#include <math/vec.h>
#include <timer/timer.h>

double f(double x) { return sin(x); }

int main() {
    timer::start("halo");
    auto orion_console = console::create("Orion");
    orion_console->set_level(level::debug);
    orion_console->info("Hello world !");

    vec3d a(3, 2, 1);

    orion_console->info("{: .2f}", a);

    orion_console->info(
        "The integral of sin between 0 and pi is around : {:.4f}",
        integration::trapezium(0, math::pi, f, 1000000));

    orion_console->debug("Successeful integration !");

    timer::print_elapsed_time("halo");
    timer::pause("halo");
    timer::print_elapsed_time();

    console::get()->warn("Ending program execution...");
    timer::stall(0.05, time_unit::second);

    timer::print_elapsed_time("halo");
    timer::print_elapsed_time();

    console::get(default_consoles::math)
        ->info("Reviving program thanks to maths !");
    vec3d v{3., 2., 1.};
    console::get(default_consoles::math)
        ->info(
            "Projecting {:.4g} on the plane defined by {:.4g} and {:.4g} "
            ": result is {:.4g}",
            v, vec3d{1., 2., 0.}, vec3d(axis::y),
            project(v, {{1., 2., 0.}, axis::y}));

    v.set_zero();
    v.print();
}
