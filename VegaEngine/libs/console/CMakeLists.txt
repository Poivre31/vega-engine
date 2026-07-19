add_library(Console
    "include/console/format.h"

    "src/console.cpp"
    "include/console/console.h"
)

target_link_libraries(Console PUBLIC spdlog::spdlog)

target_include_directories(Console PUBLIC "include")

if(MSVC)
    target_compile_options(VegaEngine PRIVATE -Wall -W4)
else()
    target_compile_options(VegaEngine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()