cmake_minimum_required(VERSION 3.17)
project(linux_modificado)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(linux_modificado
        arduinoBoruvka.c
        )
