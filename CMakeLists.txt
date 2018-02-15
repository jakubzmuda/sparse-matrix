cmake_minimum_required(VERSION 3.7)
project(PO)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SparseMatrix.h SparseMatrix.cpp)
add_executable(PO ${SOURCE_FILES})