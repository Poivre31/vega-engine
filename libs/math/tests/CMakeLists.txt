if(BUILD_TESTING)
    add_executable(math_test test_vec3.cpp test_integration.cpp)
    target_link_libraries(math_test PRIVATE GTest::gtest_main)
    target_link_libraries(math_test PRIVATE Math)

    include(GoogleTest)
    gtest_discover_tests(math_test)

endif()