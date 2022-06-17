# cmake_minimum_required(VERSION <specify CMake version here>)
project(RPI_UART_Demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RPI_UART_Demo
        main.cpp
        PiUART.cpp
        PiUART.h
        )
