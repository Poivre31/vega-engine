#include "console/console.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> create_console(std::string name) {
  std::shared_ptr<spdlog::logger> console(spdlog::get(name));
  if (console) {
    console->trace("Tried to create existing console, returning myself");
    return console;
  } else {
    console = spdlog::stdout_color_mt(name);
    console->set_level(spdlog::level::trace);
    console->set_pattern("[%T] [%^%l%$] [%n] %v");
    return console;
  }
}
