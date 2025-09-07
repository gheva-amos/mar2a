cmake_minimum_required(VERSION 3.10)

add_library(driver driver.cpp)
target_compile_options(driver PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(driver PUBLIC
    lexer
    parser
    ir
    )
