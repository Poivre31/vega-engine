add_library(console STATIC
    "include/console/format.hpp"

    "src/console.cpp"
    "include/console/console.hpp"
)

target_link_libraries(console PUBLIC spdlog::spdlog)

target_include_directories(console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(console PUBLIC "SILENCE_CONSOLE_MANAGEMENT=$<IF:$<CONFIG:Debug>,0,1>")

if(MSVC)
    target_compile_options(console PRIVATE -Wall -W4)
else()
    target_compile_options(console PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
