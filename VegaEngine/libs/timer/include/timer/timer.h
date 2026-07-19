#pragma once
#include <console/console.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "spdlog/logger.h"

enum class time_unit : char { second, millisecond, microsecond, nanosecond };
const time_unit default_unit = time_unit::millisecond;
const std::string protected_global_console = "global";
const std::string main_console = "main";

struct timer_data {
    std::chrono::steady_clock::time_point t0;
    double offset = 0.;
    bool running = true;
};

/**
 * @brief Returns time difference between @param t1 and @param t2 in given time
 * unit @param unit
 *
 * @return double
 */
double delta_time(std::chrono::steady_clock::time_point t1,
                  std::chrono::steady_clock::time_point t2, time_unit unit);

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

    static void start(const std::string& name = main_console);

    static void pause(const std::string& name = main_console);

    static void restart(const std::string& name = main_console);

    static void reset(const std::string& name = main_console);

    static void destroy(const std::string& name = main_console);

    static void print_elapsed_time(const std::string& name = main_console,
                                   time_unit unit = default_unit,
                                   size_t precision = 4);

    static double get_elapsed_time(const std::string& name = main_console,
                                   time_unit unit = default_unit);

    static void stall(double time, time_unit unit = time_unit::second);

   private:
    static inline std::mutex _mutex;

    static inline std::shared_ptr<spdlog::logger> _console =
        console::create("VegaEngine.timer");

    static inline std::unordered_map<std::string, timer_data> _watches{
        std::pair(protected_global_console,
                  timer_data{.t0 = std::chrono::steady_clock::now()}),
        std::pair(main_console,
                  timer_data{.t0 = std::chrono::steady_clock::now()})};
};
