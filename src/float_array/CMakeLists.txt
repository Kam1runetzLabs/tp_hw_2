add_library(float_array STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/float_array.c
        ${CMAKE_CURRENT_SOURCE_DIR}/include/float_array.h
        )
target_include_directories(float_array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)