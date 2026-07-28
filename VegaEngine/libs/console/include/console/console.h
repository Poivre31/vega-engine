#pragma once
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <memory>
#include <string>

#include "console/format.h"  // IWYU pragma: export

namespace level {

using spdlog::level::critical;
using spdlog::level::debug;
using spdlog::level::err;
using spdlog::level::info;
using spdlog::level::trace;
using spdlog::level::warn;

}  // namespace level

enum class default_consoles : uint8_t { vega, math, timer };

/**
 * @brief Console class to manage spdlog loggers
 * [VegaEngine] console is always available and the default return to `sget`
 *
 */
class console {
   public:
    /**
     * @brief Creates a spdlog logger called @param name if it doesn't exist
     yet, otherwise prints an error. Use `create_or_get` if the console might
     already exist.
     */
    static std::shared_ptr<spdlog::logger> create(
        const std::string& name,
        spdlog::level::level_enum level = level::trace);

    /**
    * @brief Creates a spdlog logger called @param name if it doesn't exist
    yet, otherwise returns existing logger.
    */
    static std::shared_ptr<spdlog::logger> create_or_get(
        const std::string& name,
        spdlog::level::level_enum level = level::trace);

    /**
     * @brief Returns existing spdlog logger called @param name, if it doesn't
     exist otherwise prints an error. Use `create_or_get` if the console might
     not already exist.
     * Default logger is [VegaEngine] which is created at program start.
     */
    static std::shared_ptr<spdlog::logger> get(
        const std::string& name = "VegaEngine");

    /**
     * @brief Returns one of the default spdlog logger such as [VegaEngine] or
     * [VegaMath].
     */
    static std::shared_ptr<spdlog::logger> get(
        default_consoles default_consoles);

   private:
    static inline auto _vega_console = create("VegaEngine", level::trace);
    static inline auto _math_console = create("VegaMath", level::trace);
    static inline auto _timer_console = create("VegaTimer", level::trace);
};
