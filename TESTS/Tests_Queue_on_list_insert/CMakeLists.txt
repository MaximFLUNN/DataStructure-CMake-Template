#new_app("QUEUE_INSERT_ON_LIST_APP_TESTS")
enable_testing()

add_executable(
    QUEUE_INSERT_ON_LIST_TESTS
    test_main.cpp
    test_queue_insert.cpp
    "../../LIBS/lib_Queue_on_list_insert/Queue_on_list_insert.cpp"
)
target_link_libraries(
    QUEUE_INSERT_ON_LIST_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(QUEUE_INSERT_ON_LIST_TESTS)