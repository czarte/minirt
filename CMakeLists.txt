cmake_minimum_required(VERSION 3.30)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

add_executable(miniRT main.c
        include/minirt.h
        src/window.c src/parser.c)

add_custom_target(makebuild COMMAND make -C ${mytest_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})