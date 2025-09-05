cmake_minimum_required(VERSION 3.10)

add_library(lexer
    lexer.cpp
    token.cpp
    )
target_compile_options(lexer PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)

