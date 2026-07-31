cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(BasicGUI
   VERSION 0.0.1
   DESCRIPTION "A basic GUI built on Vega Engine"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------
# ------------------
add_executable(BasicGUI src/main.cpp)
target_link_libraries(BasicGUI VegaEngine)

# ------------------
# ------------------
if(MSVC)
   target_compile_options(VegaEngine PRIVATE -Wall -W4)
else()
   target_compile_options(VegaEngine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
