add_library(vectors STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vectors.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utility.h

        ${CMAKE_CURRENT_SOURCE_DIR}/sources/vectors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/utility.c
        )

target_include_directories(vectors PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )