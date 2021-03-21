
add_library(queue STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/queue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/queue.c
        )

target_include_directories(queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)