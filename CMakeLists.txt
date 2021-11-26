cmake_minimum_required(VERSION 3.20)
project(clang_tictactoe C)

set(CMAKE_C_STANDARD 99)

add_executable(clang_tictactoe main.c src/board.c src/board.h)
