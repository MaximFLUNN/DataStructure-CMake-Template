#new_app("SET_APP_TESTS")
enable_testing()

add_executable(
    SET_TESTS
    test_main.cpp
    test_tbitfield.cpp
    test_tset.cpp
    "../../LIBS/lib_set/set.cpp"
    "../../LIBS/lib_bitfield/bitfield.cpp"
)
target_link_libraries(
    SET_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(SET_TESTS)