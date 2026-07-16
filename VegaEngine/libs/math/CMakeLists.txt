add_library(Math
    "src/datatypes/vec3.cpp"
    "include/datatypes/math/vec3.h"

    "src/integration/trapezium.cpp"
    "include/integration/math/trapezium.h"
)

target_include_directories(Math PUBLIC
    "include/datatypes"
    "include/integration"
)

target_link_libraries(Math PRIVATE Console)

add_subdirectory(bench)