add_library(timer STATIC
    "src/timer.cpp"
    "include/timer/timer.hpp"
)

target_include_directories(timer PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(timer PUBLIC console)

if(MSVC)
    target_compile_options(timer PRIVATE -Wall -W4)
else()
    target_compile_options(timer PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
