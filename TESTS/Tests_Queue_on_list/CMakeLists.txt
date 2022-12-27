#new_app("QUEUE_ON_LIST_APP_TESTS")
enable_testing()

add_executable(
    QUEUE_ON_LIST_TESTS
    test_main.cpp
    test_queue.cpp
    "../../LIBS/lib_Queue_on_list/Queue_on_list.cpp"
)
target_link_libraries(
    QUEUE_ON_LIST_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(QUEUE_ON_LIST_TESTS)