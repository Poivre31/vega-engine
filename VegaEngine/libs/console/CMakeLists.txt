add_library(Console
    "include/console/format.h"

    "src/console.cpp"
    "include/console/console.h"
)

target_link_libraries(Console PUBLIC spdlog::spdlog)

target_include_directories(Console PUBLIC "include")

target_compile_options(Console PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
