cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(compute
   VERSION 0.0.1
   DESCRIPTION "An app for scientific computing"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------*
# ------------------
add_executable(compute src/main.cpp)
target_link_libraries(compute vega-engine)

# ------------------
# ------------------
if(MSVC)
   target_compile_options(compute PRIVATE -Wall -W4)
else()
   target_compile_options(compute PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
