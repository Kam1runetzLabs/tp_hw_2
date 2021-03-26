add_executable(s_v_calculating_unit_tests tests.cpp)

target_include_directories(s_v_calculating_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sync_vectors_calculating/include
        )

target_link_libraries(s_v_calculating_unit_tests GTest::gtest_main s_v_calculating)
add_test(NAME s_v_calculating_unit_tests COMMAND s_v_calculating_unit_tests)
