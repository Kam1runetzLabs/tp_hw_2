hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(unit_tests unit_tests.cpp)

target_include_directories(unit_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../mylib/include
    )

target_link_libraries(
    unit_tests GTest::gtest_main mylib
    )

add_test(NAME unit_tests COMMAND unit_tests)
