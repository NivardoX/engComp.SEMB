cmake_minimum_required(VERSION 3.17)
project(linux_nao_modificado C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(linux_nao_modificado
        boruvka.h
        testDriver.c
        utils.h)
