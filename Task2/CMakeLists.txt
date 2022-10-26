cmake_minimum_required(VERSION 3.23)
project(Task2)

set(CMAKE_C_STANDARD 99)

add_executable(Task2 Task2BracketsBalance.c ../stack/stack.c ../stack/stack.h)