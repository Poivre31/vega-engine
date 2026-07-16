set(CMAKE_CXX_STANDARD 20)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(google_test)

add_subdirectory(nanobench)

add_subdirectory(spdlog)
