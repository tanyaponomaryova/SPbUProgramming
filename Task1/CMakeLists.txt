cmake_minimum_required(VERSION 3.23)
project(Task1)

set(CMAKE_C_STANDARD 99)

add_executable(Task1 Task1ReversePolishNotationCalculation.c ../stack/stack.c ../stack/stack.h)