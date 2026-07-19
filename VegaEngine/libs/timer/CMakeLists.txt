add_library(Timer
    "src/timer.cpp"
    "include/timer/timer.h"
)

target_include_directories(Timer PUBLIC
    "include"
)

target_link_libraries(Timer PUBLIC Console)

target_compile_options(Timer PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
