cmake_minimum_required(VERSION 3.10)

add_subdirectory(lexer)
add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(driver)
add_executable(mar2a mar2a.cpp)
target_compile_options(mar2a PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(mar2a PRIVATE driver)
