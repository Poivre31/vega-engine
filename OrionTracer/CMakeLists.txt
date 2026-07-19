cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(OrionTracer
   VERSION 0.0.1
   DESCRIPTION "A basic ray tracer built on Vega Engine"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------
# ------------------
add_executable(OrionTracer src/main.cpp)
target_link_libraries(OrionTracer VegaEngine)

# ------------------
# ------------------
target_compile_options(OrionTracer PRIVATE -Wall -Wextra)
