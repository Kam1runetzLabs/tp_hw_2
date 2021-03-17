add_executable(demo main.c)
target_include_directories(demo PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mylib/include
        )

target_link_libraries(demo mylib)
