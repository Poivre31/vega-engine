add_library(Math
    "src/vec3.cpp"
    "include/math/vec3.h"
)

target_include_directories(Math PUBLIC "include")
