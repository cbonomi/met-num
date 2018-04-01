cmake_minimum_required(VERSION 3.9)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

add_executable(PageRank PageRank/main.cpp PageRank/Util.cpp PageRank/Util.h
        PageRank/rdtsc.h PageRank/MapMatrix.cpp PageRank/MapMatrix.h
        PageRank/VectorMapMatrix.cpp PageRank/VectorMapMatrix.h)

add_executable(DebugMultiplicacion PageRank/mult.cpp PageRank/Util.cpp PageRank/Util.h
        PageRank/rdtsc.h PageRank/MapMatrix.cpp PageRank/MapMatrix.h
        PageRank/VectorMapMatrix.cpp PageRank/VectorMapMatrix.h)

add_executable(DebugMatrices PageRank/debugMatrices.cpp PageRank/Util.cpp PageRank/Util.h
        PageRank/rdtsc.h PageRank/MapMatrix.cpp PageRank/MapMatrix.h
        PageRank/VectorMapMatrix.cpp PageRank/VectorMapMatrix.h)