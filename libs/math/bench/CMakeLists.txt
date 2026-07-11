add_executable(math_bench benchmark_integration.cpp)
target_link_libraries(math_bench PRIVATE nanobench)
target_link_libraries(math_bench PRIVATE Math)

# add_custom_target(bench
#         COMMAND $<TARGET_FILE:math_bench>
#         DEPENDS math_bench
#         COMMENT "Running nanobench benchmarks..."
#         USES_TERMINAL
#     )
