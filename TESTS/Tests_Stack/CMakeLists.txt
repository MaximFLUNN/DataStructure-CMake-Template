#new_app("STACK_APP_TESTS")
enable_testing()

add_executable(
    STACK_TESTS
    test_main.cpp
    test_stack.cpp
    "../../LIBS/lib_Stack/Stack.cpp"
)
target_link_libraries(
    STACK_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(STACK_TESTS)