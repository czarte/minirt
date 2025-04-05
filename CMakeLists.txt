cmake_minimum_required(VERSION 3.30)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

add_executable(miniRT main.c
        include/minirt.h
        src/window.c src/parser.c src/init.c src/exit.c src/scene.c
        src/object.c src/vec/t_vec_new.c src/vec/t_vec_ops.c src/vec/t_vec_products.c)

add_custom_target(makebuild COMMAND make -C ${mytest_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})