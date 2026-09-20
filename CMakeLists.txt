cmake_minimum_required(VERSION 3.28)

project(LibAndProject)

# ------------------
# ------------------
include(CTest)
enable_testing()

add_subdirectory(VegaEngine)
add_subdirectory(apps/OrionTracer)
add_subdirectory(apps/Compute)
add_subdirectory(apps/VulkanApp)

