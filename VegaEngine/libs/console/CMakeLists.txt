add_library(Console
    "include/console/format.hpp"

    "src/console.cpp"
    "include/console/console.hpp"
)

target_link_libraries(Console PUBLIC spdlog::spdlog)

target_include_directories(Console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(Console PUBLIC "SILENCE_CONSOLE_MANAGEMENT=$<IF:$<CONFIG:Debug>,0,1>")

if(MSVC)
    target_compile_options(Console PRIVATE -Wall -W4)
else()
    target_compile_options(Console PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
