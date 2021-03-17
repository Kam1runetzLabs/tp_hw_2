add_library(mylib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/header.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.c
        )

target_include_directories(mylib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )