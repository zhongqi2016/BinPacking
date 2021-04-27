cmake_minimum_required(VERSION 3.17)
project(BinPacking_BNB)

set(CMAKE_CXX_STANDARD 20)

add_executable(BinPacking_BNB main.cpp Tree.cpp Tree.h LowerBound.cpp LowerBound.h state.h state.cpp UpperBound.cpp UpperBound.h Data.h Data.cpp)