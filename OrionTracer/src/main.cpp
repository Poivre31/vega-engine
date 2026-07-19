#include <console/console.h>
#include <math/trapezium.h>
#include <math/vec3.h>
#include <timer/timer.h>

#include <numbers>

double f(double x) { return sin(x); }

int main() {
    timer::start("halo");
    auto orion_console = console::create("Orion");
    orion_console->set_level(level::debug);
    orion_console->info("Hello world !");

    vec3 a(3, 2, 1);

    orion_console->info("{: .2f}", a);

    orion_console->info(
        "The integral of sin between 0 and pi is around : {:.4f}",
        integration::trapezium(0, std::numbers::pi, f, 1000000));

    orion_console->debug("Successeful integration !");

    timer::print_elapsed_time("halo");
    timer::pause("halo");
    timer::print_elapsed_time();

    console::get()->warn("Ending program execution...");
    timer::stall(0.05, time_unit::second);

    timer::print_elapsed_time("halo");
    timer::print_elapsed_time();
}
