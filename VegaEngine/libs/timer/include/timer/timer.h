#pragma once
#include "spdlog/logger.h"
#include <chrono>
#include <console/console.h>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std::chrono;

enum class time_unit : size_t { second, millisecond, microsecond, nanosecond };
const time_unit default_unit = time_unit::millisecond;

struct timer_data {
    high_resolution_clock::time_point t0;
    double offset = 0.;
    bool running = true;
};

/**
 * @brief Returns time difference between @param t1 and @param t2 in given time
 * unit @param unit
 *
 * @return double
 */
double delta_time(high_resolution_clock::time_point t1,
                  high_resolution_clock::time_point t2, time_unit unit);

/**
 * @brief Timer class to manage multiple watches.
 * Start a timer with `start`, pause it with `pause`, start it again with
 `restart` and reset it to current time with `reset`.
 *
 * `time_unit` lets you define the unit (s, ms, µs, ns) you want to set or get a
 time with
 *
 * You can stall the execution of the program for a given time with `stall`
 *
 *  Status and time is printer using [VegaEngine.timer] console which is
 available with `get_console`
 *
 * [global] timer starts at program startup and can't be paused/reset.
 * [main] is available by default and can be manipulated like other timers.
 *
 */
class timer {
  public:
    static std::shared_ptr<spdlog::logger> get_console();

    static void start(std::string name = "main");

    static void pause(std::string name = "main");

    static void restart(std::string name = "main");

    static void reset(std::string name = "main");

    static void destroy(std::string name = "main");

    static void print_ellapsed_time(std::string name = "main",
                                    time_unit unit = default_unit,
                                    size_t precision = 4);

    static double get_ellapsed_time(std::string name = "main",
                                    time_unit unit = default_unit);

    static void stall(double time, time_unit unit = time_unit::second);

  private:
    static inline std::shared_ptr<spdlog::logger> _console =
        console::create("VegaEngine.timer");

    static inline std::unordered_map<std::string, timer_data> _watches{
        std::pair("global", timer_data{.t0 = high_resolution_clock::now()}),
        std::pair("main", timer_data{.t0 = high_resolution_clock::now()})};
};