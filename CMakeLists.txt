cmake_minimum_required(VERSION 3.9)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

add_executable(PageRank PageRank/main.cpp PageRank/Matriz.cpp PageRank/MapMatrix.cpp PageRank/MapMatrix.h PageRank/VectorMapMatrix.cpp PageRank/VectorMapMatrix.h)