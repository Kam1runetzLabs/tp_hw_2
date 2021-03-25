add_library(m_v_calculating SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vectors_calc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/vectors_calc.c
        )

target_include_directories(m_v_calculating PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../thread_pool/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../vectors/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../float_array/include
        )

target_link_libraries(m_v_calculating thread_pool vectors float_array)