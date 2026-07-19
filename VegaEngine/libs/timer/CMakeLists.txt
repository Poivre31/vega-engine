add_library(Timer
    "src/timer.cpp"
    "include/timer/timer.h"
)

target_include_directories(Timer PUBLIC
    "include"
)

target_link_libraries(Timer PUBLIC Console)

if(MSVC)
    target_compile_options(VegaEngine PRIVATE -Wall -W4)
else()
    target_compile_options(VegaEngine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()