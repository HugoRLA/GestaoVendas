cmake_minimum_required(VERSION 3.14)
project(GestaoVendas C)

set(CMAKE_C_STANDARD 99)

add_executable(GestaoVendas main.c ma.c ma.h)

add_executable(ma ma.c ma.h artigo.c artigo.h)