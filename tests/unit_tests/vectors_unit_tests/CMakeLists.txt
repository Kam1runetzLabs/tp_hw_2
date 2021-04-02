add_executable(vectors_unit_tests tests.cpp)

target_include_directories(vectors_unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vectors/include
        )

target_link_libraries(vectors_unit_tests GTest::gtest_main vectors)
add_test(NAME vectors_unit_tests COMMAND vectors_unit_tests)
