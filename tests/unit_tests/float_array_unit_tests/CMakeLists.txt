add_executable(float_array_unit_tests tests.cpp)

target_include_directories(float_array_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/float_array/include
        )

target_link_libraries(float_array_unit_tests GTest::gtest_main float_array)
add_test(NAME float_array_unit_tests COMMAND float_array_unit_tests)
