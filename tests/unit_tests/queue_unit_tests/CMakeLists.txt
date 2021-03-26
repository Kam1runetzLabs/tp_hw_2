add_executable(queue_unit_tests tests.cpp)

target_include_directories(queue_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/queue/include
        )

target_link_libraries(queue_unit_tests GTest::gtest_main queue)
add_test(NAME queue_unit_tests COMMAND queue_unit_tests)
