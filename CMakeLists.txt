cmake_minimum_required(VERSION 3.14)
project(GestaoVendas C)

set(CMAKE_C_STANDARD 99)

add_executable(artigo artigo.c artigo.h)

add_executable(stock stock.c stock.h)

add_executable(ma ma.c ma.h)

add_executable(sv sv.c sv.h )

add_executable(cv cv.c cv.h)
