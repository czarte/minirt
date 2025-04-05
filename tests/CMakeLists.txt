enable_testing()

add_subdirectory(${CMAKE_BINARY_DIR}/googletest)

add_executable(
        vec_tests
        vec_tests.cc
)
target_link_libraries(
        ${PROJECT_TEST_NAME}
        vec_tests
        gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vec_tests)