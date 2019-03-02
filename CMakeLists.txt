cmake_minimum_required(VERSION 3.13)
project(FP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FP
        Convolution.h
        Convolution_20190224.h
        Image.cpp
        Image.h
        ImageIO.cpp
        ImageIO.h
        Kernel.h
        log.cpp
        log.h
        main.cpp
        Matrix.h)
