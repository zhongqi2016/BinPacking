cmake_minimum_required(VERSION 3.17)
project(BinPacking_BNB)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinPacking_BNB main.cpp BinPacking.cpp BinPacking.h Item.cpp Item.h Branch.h Branch.cpp ReadFiles.cpp ReadFiles.h)