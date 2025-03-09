cmake_minimum_required(VERSION 3.30)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

add_executable(miniRT main.c
        include/minirt.h)
