add_library(m_v_calculating SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/include/header.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.c
        )

target_include_directories(m_v_calculating PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)