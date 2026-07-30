add_library(Math
    "include/math/types/coordinates.h"
    "include/math/types/vec3.h"
    "include/math/types/vec3_math.h"

    "include/math/vec.h"


    "src/integration/trapezium.cpp"
    "include/math/integration/trapezium.h"

    "include/math/integration.h"


    "include/math/numbers.h"


    "include/math/ode/solver.h"
    "include/math/ode/euler.h"

    "include/math/ode_solver.h"
)

target_include_directories(Math PUBLIC
    "include"
)


target_link_libraries(Math PUBLIC Console)

add_subdirectory(bench)

if(MSVC)
    target_compile_options(Math PRIVATE -Wall -W4)
else()
    target_compile_options(Math PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
