#include "console/console.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <stdexcept>

#include "spdlog/common.h"

std::shared_ptr<spdlog::logger> console::create(const std::string& name,
                                                spdlog::level::level_enum level,
                                                bool silence) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (console) {
        throw std::invalid_argument(fmt::format(
            "Tried to create existing console [{:s}], (use create_or_get to "
            "ignore this error)",
            name));
    } else {
        console = spdlog::stdout_color_mt(name);
        console->set_level(level);
        console->set_pattern("[%T] [%^%l%$] [%n] %v");
        if (!silence) {
            console->trace("Created console [{:s}]", name);
        }
        return console;
    }
}

std::shared_ptr<spdlog::logger> console::create_or_get(
    const std::string& name, spdlog::level::level_enum level, bool silence) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (console) {
        if (!silence) {
            console->trace("Console already exists, returning myself [{:s}]",
                           name);
        }
        return console;
    } else {
        console = spdlog::stdout_color_mt(name);
        console->set_level(level);
        console->set_pattern("[%T] [%^%l%$] [%n] %v");

        if (!silence) {
            console->trace("Console [{:s}] did not exist, created it", name);
        }
        return console;
    }
}

std::shared_ptr<spdlog::logger> console::get(const std::string& name,
                                             bool silence) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (!console) {
        throw std::invalid_argument(
            fmt::format("Tried to get console [{:s}] that doesn't exist,  (use "
                        "create_or_get to automatically create it)",
                        name));
    } else {
        if (!silence) {
            console->trace("Found console [{:s}]", name);
        }
        return console;
    }
}

std::shared_ptr<spdlog::logger> console::get(default_consoles default_consoles,
                                             bool silence) {
    switch (default_consoles) {
        case default_consoles::vega:
            if (!silence) {
                _vega_console->trace("Found default console [VegaEngine]");
            }
            return _vega_console;
        case default_consoles::math:
            if (!silence) {
                _math_console->trace("Found default console [VegaMath]");
            }
            return _math_console;
        case default_consoles::timer:
            if (!silence) {
                _timer_console->trace("Found default console [VegaTimer]");
            }
            return _timer_console;
        case default_consoles::test:
            if (!silence) {
                _test_console->trace("Found default console [VegaTest]");
            }
            return _test_console;
    }
    std::abort();
}
