cmake_minimum_required(VERSION 3.17)
project(pl0Compiler)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fakultRecursiv.pl0
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(pl0Compiler lex.c main.c parser.c)