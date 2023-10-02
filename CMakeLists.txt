cmake_minimum_required(VERSION 3.5)
project(assignment_1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(hamming74 hamming74.c)
add_executable(utf8 utf8.c)
add_executable(tokenize tokenize.c scan_token.c scan_token.h)
