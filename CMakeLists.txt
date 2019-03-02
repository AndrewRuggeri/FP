cmake_minimum_required(VERSION 3.8)
project(FP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FP
        Filter.h
        Image.cpp
        Image.h
        ImageIO.cpp
        ImageIO.h
        Kernel.h
        log.cpp
        log.h
        main.cpp
        Matrix.h)
