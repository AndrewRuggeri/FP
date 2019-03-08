cmake_minimum_required(VERSION 3.8)
project(FP)
message("Cmaking FP")


# Set build flags for building with ARM
option(ARMBUILD "ARMBUILD" OFF)


# Set architecture specific build flags
if(ARMBUILD)
    message("Building for ARM")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mcpu=cortex-a15 -fipa-pta")
else()
    message("Building for AMD64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -m64")
endif()


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -funroll-loops -Ofast -fvariable-expansion-in-unroller")


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
if(NOT WIN32)	# main.cpp uses posix calls/headers
	add_executable(FP
			main.cpp
			${SOURCE})
endif()

# executable to test filters
add_executable(testFilters
        FilterTestMain.cpp
        ${SOURCE})
