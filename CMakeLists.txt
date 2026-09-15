cmake_minimum_required(VERSION 3.28)



project(LibAndProject)

# ------------------
# ------------------
include(CTest)
enable_testing()

add_compile_definitions("DEBUG=$<CONFIG:Debug>")
add_compile_definitions("RELEASE=$<CONFIG:Release>")

add_subdirectory(VegaEngine)
# add_subdirectory(apps/OrionTracer)
# add_subdirectory(apps/BasicGUI)
add_subdirectory(apps/VulkanApp)