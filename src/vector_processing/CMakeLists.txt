add_library(vector_processing STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vectors.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utility.h

        ${CMAKE_CURRENT_SOURCE_DIR}/sources/vectors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/utility.c
        )

target_include_directories(vector_processing PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )