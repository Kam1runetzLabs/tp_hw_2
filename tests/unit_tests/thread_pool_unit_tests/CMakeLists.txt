add_executable(thread_pool_unit_tests tests.cpp)

target_include_directories(thread_pool_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/thread_pool/include
        )

target_link_libraries(thread_pool_unit_tests GTest::gtest_main thread_pool)
add_test(NAME thread_pool_unit_tests COMMAND thread_pool_unit_tests)
