add_library(Math
    "include/datatypes/math/coordinates.h"
    "include/datatypes/math/vec3.h"
    "include/math/vec.h"


    "src/integration/trapezium.cpp"
    "include/integration/math/trapezium.h"
    "include/math/integration.h"

    "include/math/numbers.h"


    "include/ode/math/solver.h"

    # "include/eqdiff/math/euler.h"
    # include/eqdiff/math/base_solver.h
    # include/eqdiff/math/solver_I.h
    # include/eqdiff/math/solver_II.h
)

target_include_directories(Math PUBLIC
    "include/datatypes"
    "include/integration"
    "include/ode"
    "include"
)


target_link_libraries(Math PUBLIC Console)

add_subdirectory(bench)

if(MSVC)
    target_compile_options(VegaEngine PRIVATE -Wall -W4)
else()
    target_compile_options(VegaEngine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()