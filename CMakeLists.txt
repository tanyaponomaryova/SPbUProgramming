cmake_minimum_required(VERSION 3.23)
project(avlTree C)

set(CMAKE_C_STANDARD 99)

add_executable(avlTree main.c avlTree.c avlTree.h)
