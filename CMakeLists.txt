cmake_minimum_required(VERSION 3.9)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

add_executable(PageRank main.cpp Matriz.cpp MapMatrix.cpp MapMatrix.h VectorMapMatrix.cpp VectorMapMatrix.h)