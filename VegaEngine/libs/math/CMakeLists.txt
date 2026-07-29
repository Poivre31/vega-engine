add_library(Math
    "include/datatypes/math/coordinates.h"
    "include/datatypes/math/vec3.h"
    "include/datatypes/math/vec3_math.h"
    "include/datatypes/math/vec3_ops.h"

    "include/math/vec.h"


    "src/integration/trapezium.cpp"
    "include/integration/math/trapezium.h"

    "include/math/integration.h"


    "include/math/numbers.h"


    "include/ode/math/solver.h"
    "include/ode/math/euler.h"

    "include/math/ode_solver.h"
)

target_include_directories(Math PUBLIC
    "include/datatypes"
    "include/integration"
    "include/ode"
    "include/random"
    "include"
)


target_link_libraries(Math PUBLIC Console)

add_subdirectory(bench)

if(MSVC)
    target_compile_options(VegaEngine PRIVATE -Wall -W4)
else()
    target_compile_options(VegaEngine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()