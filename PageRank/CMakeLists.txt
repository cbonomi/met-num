cmake_minimum_required(VERSION 3.10)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(PageRank
        main.cpp
        MapMatrix.cpp
        MapMatrix.h
        rdtsc.h
        Util.cpp
        Util.h
        VectorMapMatrix.cpp
        VectorMapMatrix.h)
