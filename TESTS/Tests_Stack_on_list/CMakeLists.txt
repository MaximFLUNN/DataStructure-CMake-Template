#new_app("STACK_ON_LIST_APP_TESTS")
enable_testing()

add_executable(
    STACK_ON_LIST_TESTS
    test_main.cpp
    test_stack_on_list.cpp
    "../../LIBS/lib_Stack_on_list/Stack_on_list.cpp"
)
target_link_libraries(
    STACK_ON_LIST_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(STACK_ON_LIST_TESTS)