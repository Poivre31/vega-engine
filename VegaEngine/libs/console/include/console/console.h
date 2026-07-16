#pragma once
#include "console/format.h" // IWYU pragma: export
#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

/**
 * @brief Create a spdlog console (color mt) named @param name if it doesn't
 * exist, returns existing console otherwise
 *
 * @param name Console name
 * @return Shared pointer to spdlog logger
 */
std::shared_ptr<spdlog::logger> create_console(std::string name);

namespace level {

using spdlog::level::critical;
using spdlog::level::debug;
using spdlog::level::err;
using spdlog::level::info;
using spdlog::level::trace;
using spdlog::level::warn;

} // namespace level
