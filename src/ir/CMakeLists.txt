cmake_minimum_required(VERSION 3.10)

add_library(ir
    ir_node.cpp
    ir_module.cpp
    ir_function.cpp
    ir_type.cpp
    ir_value.cpp
    ir_const_int.cpp
    ir_return.cpp
    ir_unary_op.cpp
    )
target_compile_options(ir PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)


