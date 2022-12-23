#new_app("MATRIX_APP_TESTS")
enable_testing()

add_executable(
    MATRIX_TESTS
    test_main.cpp
    test_matrix.cpp
    "../../LIBS/lib_Matrix/matrix.cpp"
)
target_link_libraries(
    MATRIX_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MATRIX_TESTS)