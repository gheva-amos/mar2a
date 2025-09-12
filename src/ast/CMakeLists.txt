cmake_minimum_required(VERSION 3.10)

add_library(ast
    ast_program.cpp
    ast_function.cpp
    ast_return.cpp
    ast_identifier.cpp
    ast_expression.cpp
    ast_factor.cpp
    ast_type.cpp
    )
target_compile_options(ast PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)


