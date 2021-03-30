add_executable(stress_tests stress_test.cpp)
option(MTHREADING_CALC "Multithreading calculating" OFF)

target_include_directories(stress_tests PUBLIC src/vectors/include src/float_array/include)
target_link_libraries(stress_tests vectors float_array)

if (MTRHEADING_CALC)
    target_include_directories(stress_tests PUBLIC src/multithreading_vectors_calculating/include)
    target_link_libraries(stress_tests m_v_calculating)
else ()
    target_include_directories(stress_tests PUBLIC src/sync_vectors_calculating/include)
    target_link_libraries(stress_tests s_v_calculating)
endif ()
