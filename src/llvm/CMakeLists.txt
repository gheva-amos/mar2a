cmake_minimum_required(VERSION 3.10)

#set(LLVM_DIR "/usr/lib64/cmake/llvm/" CACHE PATH "Path to LLVMConfig.cmake directory")

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(LLVM_LIBS
    core
    orcjit
    executionengine
    support
    mc
    native
    nativecodegen
    asmprinter
    )

add_library(mar2a_llvm
    llvm_visitor.cpp
    )
target_compile_options(mar2a_llvm PRIVATE -Wall -Wextra -pedantic -Wno-enum-compare -Wno-maybe-uninitialized -Wno-uninitialized -Wno-unused-parameter)
target_link_libraries(mar2a_llvm PUBLIC
    ${LLVM_LIBS}
    )
