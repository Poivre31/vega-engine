cmake_minimum_required(VERSION 3.28)

project(samples)

# ------------------
# ------------------
include(CTest)
enable_testing()

add_subdirectory(vega-engine)
add_subdirectory(apps/orion-tracer)
add_subdirectory(apps/compute)
add_subdirectory(apps/vulkan-renderer)

