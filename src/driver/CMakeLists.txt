cmake_minimum_required(VERSION 3.10)

add_library(driver driver.cpp)
target_compile_options(driver PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
set(DRIVER_LIBRARIES
    lexer
    parser
    ir)

if (MAR2A_USE_LLVM)
  list(APPEND DRIVER_LIBRARIES mar2a_llvm)
endif()

target_link_libraries(driver PUBLIC
    ${DRIVER_LIBRARIES}
    )
