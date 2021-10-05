cmake_minimum_required(VERSION 3.17)
project(BinPacking_BNB)

set(CMAKE_CXX_STANDARD 20)

add_executable(BinPacking_BNB main.cpp LowerBound.cpp LowerBound.h UpperBound.cpp UpperBound.h DataInput.h Algorithm.cpp Algorithm.h Bin.cpp Bin.h)