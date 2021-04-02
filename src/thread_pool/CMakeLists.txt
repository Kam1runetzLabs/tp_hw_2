add_library(thread_pool STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/thread_pool.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/thread_pool.c
        )

target_include_directories(thread_pool PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../queue/include
        )

target_link_libraries(thread_pool queue pthread)

