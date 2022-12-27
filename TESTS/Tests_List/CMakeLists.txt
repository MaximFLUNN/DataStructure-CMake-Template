#new_app("LIST_APP_TESTS")
enable_testing()

add_executable(
    LIST_TESTS
    test_main.cpp
    test_list.cpp
    "../../LIBS/lib_list/List.cpp"
)
target_link_libraries(
    LIST_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LIST_TESTS)