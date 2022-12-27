#new_app("QUEUE_ERASE_ON_LIST_APP_TESTS")
enable_testing()

add_executable(
    QUEUE_ERASE_ON_LIST_TESTS
    test_main.cpp
    test_queue_erase.cpp
    "../../LIBS/lib_Queue_on_list_erase/Queue_on_list_erase.cpp"
)
target_link_libraries(
    QUEUE_ERASE_ON_LIST_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(QUEUE_ERASE_ON_LIST_TESTS)