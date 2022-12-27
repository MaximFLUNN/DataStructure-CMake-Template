#new_app("ANALIZER_APP_TESTS")
enable_testing()

add_executable(
    ANALIZER_TESTS
    test_main.cpp
    test_analizer.cpp
    "../../LIBS/lib_Arithmetic_Analyzer/Analizer.cpp"
)
target_link_libraries(
    ANALIZER_TESTS
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ANALIZER_TESTS)