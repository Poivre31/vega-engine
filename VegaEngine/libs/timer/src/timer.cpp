#include "timer/timer.h"

#include <console/console.h>

#include <chrono>
#include <mutex>
#include <ratio>
#include <string>
#include <thread>
#include <unordered_map>

using std::chrono::duration;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

bool is_protected(const std::string& name) {
    return !name.compare(protected_global_console);
}

const std::unordered_map<time_unit, double> factors{
    {time_unit::second, 1e-9},
    {time_unit::millisecond, 1e-6},
    {time_unit::microsecond, 1e-3},
    {time_unit::nanosecond, 1e0},
};

const std::unordered_map<time_unit, const std::string> units{
    {time_unit::second, "s"},
    {time_unit::millisecond, "ms"},
    {time_unit::microsecond, "µs"},
    {time_unit::nanosecond, "ns"},
};

double delta_time(steady_clock::time_point t1, steady_clock::time_point t2,
                  time_unit unit) {
    auto delta =
        static_cast<double>(duration_cast<nanoseconds>(t2 - t1).count());
    return delta * factors.at(unit);
}

std::shared_ptr<spdlog::logger> timer::get_console() { return _console; }

void timer::start(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (is_protected(name)) {
        _console->error("Trying to (re)create [global] timer");
    } else {
        _watches.insert_or_assign(name, timer_data{.t0 = steady_clock::now()});
        _console->trace("Started timer [{:s}]", name);
    }
}

void timer::pause(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (is_protected(name)) {
        _console->error("Trying to pause  [global] timer");
    } else if (!_watches.contains(name)) {
        _console->error(
            "Trying to pause a timer [{:s}] that hasn't been created", name);
    } else {
        auto& watch = _watches.at(name);
        if (!watch.running) {
            _console->warn("timer has already been paused");
            return;
        }
        watch.offset +=
            delta_time(watch.t0, steady_clock::now(), time_unit::nanosecond);
        watch.running = false;
        _console->trace("Paused timer [{:s}]", name);
    }
}

void timer::restart(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto t = steady_clock::now();
    if (is_protected(name)) {
        _console->error("Trying to restart [global] timer");
    } else if (!_watches.contains(name)) {
        _console->error(
            "Trying to restart a timer [{:s}] that hasn't been created", name);

    } else {
        auto& watch = _watches.at(name);
        if (watch.running) {
            _console->warn(
                "Trying to restart timer [{:s}] but it is already running",
                name);
        } else {
            watch.t0 = t;
            watch.running = true;
            _console->trace("Restarted timer [{:s}]", name);
        }
    }
}

void timer::reset(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (is_protected(name)) {
        _console->error("Trying to reset [global] timer");
    } else if (!_watches.contains(name)) {
        _console->error(
            "Trying to reset a timer [{:s}] that hasn't been created", name);

    } else {
        _watches.at(name) = {
            .t0 = steady_clock::now(), .offset = 0, .running = true};
        _console->trace("Reset timer [{:s}]", name);
    }
}

void timer::destroy(const std::string& name) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (is_protected(name)) {
        _console->error("Trying to destroy [global] timer");
    } else if (!_watches.contains(name)) {
        _console->error(
            "Trying to destroy a timer [{:s}] that hasn't been created", name);

    } else {
        _watches.erase(name);
    }
}

void timer::print_elapsed_time(const std::string& name, time_unit unit,
                               size_t precision) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto t = steady_clock::now();
    if (!_watches.contains(name)) {
        _console->error(
            "Trying to print the time of a timer [{:s}] that "
            "hasn't been created",
            name);
    } else {
        double dt = _watches.at(name).offset * factors.at(unit);
        if (_watches.at(name).running)
            dt += delta_time(_watches.at(name).t0, t, unit);
        _console->info(fmt::runtime("Time since timer [{:s}] start: {:." +
                                    std::to_string(precision) + "g} {:s}"),
                       name, dt, units.at(unit));
    }
}

double timer::get_elapsed_time(const std::string& name, time_unit unit) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto t = steady_clock::now();
    if (!_watches.contains(name)) {
        _console->error(
            "Trying to print the time of a timer [{:s}] that "
            "hasn't been created",
            name);
        return 0.;
    } else {
        double dt = _watches.at(name).offset * factors.at(unit);
        if (_watches.at(name).running) {
            dt += delta_time(_watches.at(name).t0, t, unit);
        }
        return dt;
    }
}

void timer::stall(double time, time_unit unit) {
    auto t0 = steady_clock::now();
    auto sleep_margin = duration<double, std::milli>(2);
    std::this_thread::sleep_for(
        duration<double, std::nano>(time / factors.at(unit)) - sleep_margin);
    while (delta_time(t0, steady_clock::now(), unit) < time) {
    }
}
