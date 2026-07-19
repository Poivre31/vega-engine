#include "console/console.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "spdlog/common.h"

std::shared_ptr<spdlog::logger> console::create(
    const std::string& name, spdlog::level::level_enum level) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (console) {
        console->error(
            "Tried to create existing console [{:s}], returning nullptr "
            "(use create_or_get to ignore this error)",
            name);
        return nullptr;
    } else {
        console = spdlog::stdout_color_mt(name);
        console->set_level(level);
        console->set_pattern("[%T] [%^%l%$] [%n] %v");

        console->trace("Created console [{:s}]", name);
        return console;
    }
}

std::shared_ptr<spdlog::logger> console::create_or_get(
    const std::string& name, spdlog::level::level_enum level) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (console) {
        console->trace("Console already exists, returning myself [{:s}]", name);
        return console;
    } else {
        console = spdlog::stdout_color_mt(name);
        console->set_level(level);
        console->set_pattern("[%T] [%^%l%$] [%n] %v");

        console->trace("Console [{:s}] did not exist, created it", name);
        return console;
    }
}

std::shared_ptr<spdlog::logger> console::get(const std::string& name) {
    std::shared_ptr<spdlog::logger> console(spdlog::get(name));
    if (!console) {
        _vega_console->error(
            "Tried to get console [{:s}] that doesn't exist, "
            "returning nullptr (use "
            "create_or_get to automatically create it)",
            name);
        return nullptr;
    } else {
        console->trace("Found console [{:s}]", name);
        return console;
    }
}
