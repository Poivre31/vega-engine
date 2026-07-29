add_executable(math_bench benchmark_ode.cpp)
target_link_libraries(math_bench PRIVATE nanobench)
target_link_libraries(math_bench PRIVATE Math)
