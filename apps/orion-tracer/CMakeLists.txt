cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(orion-tracer
   VERSION 0.0.1
   DESCRIPTION "A basic ray tracer built on Vega Engine"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------
# ------------------
add_executable(orion-tracer src/main.cpp)
target_link_libraries(orion-tracer vega-engine)

# ------------------
# ------------------
if(MSVC)
   target_compile_options(orion-tracer PRIVATE -Wall -W4)
else()
   target_compile_options(orion-tracer PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
