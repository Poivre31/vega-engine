cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(VulkanApp
   VERSION 0.0.1
   DESCRIPTION "A basic ray tracer built on Vega Engine"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------
# ------------------
add_executable(VulkanApp src/main.cpp)
target_link_libraries(VulkanApp VegaEngine)

# ------------------
# ------------------
if(MSVC)
   target_compile_options(VulkanApp PRIVATE -Wall -W4)
else()
   target_compile_options(VulkanApp PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
