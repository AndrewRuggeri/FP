cmake_minimum_required(VERSION 3.8)
project(FP)
message("Cmaking FP")

set(CMAKE_CXX_STANDARD 11)
set(CXX_COVERAGE_COMPILE_FLAGS "-funroll -Ofast")

# LOG MACROS
add_definitions(-DLOG_INFO_ON)
add_definitions(-DLOG_WARNING_ON)
add_definitions(-DLOG_DEBUG_ON)
add_definitions(-DLOG_ERROR_ON)

include_directories(.)

set(SOURCE
        Filter.h
        FilterChain.h
        Image.cpp
        Image.h
        ImageIO.cpp
        ImageIO.h
        Kernel.h
        log.h
        Matrix.h)

# main executable
add_executable(FP
        main.cpp
        ${SOURCE})

# executable to test filters
add_executable(testFilters
        FilterTestMain.cpp
        ${SOURCE})
