add_library(s_v_calculating STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vectors_calc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/vectors_calc.c
        )

target_include_directories(s_v_calculating PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../vector_processing/include
        )
