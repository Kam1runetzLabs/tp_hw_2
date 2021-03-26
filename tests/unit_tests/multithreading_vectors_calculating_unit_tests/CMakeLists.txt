add_executable(m_v_calculating_unit_tests tests.cpp)

target_include_directories(m_v_calculating_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/multithreading_vectors_calculating/include
        )

target_link_libraries(m_v_calculating_unit_tests GTest::gtest_main m_v_calculating)
add_test(NAME m_v_calculating_unit_tests COMMAND m_v_calculating_unit_tests)
