cmake_minimum_required(VERSION 3.21)
project(COMP_LEX_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(COMP_LEX_1 main.c Lexer.h State.h Lexer.c Token.h State.c Token.c)
