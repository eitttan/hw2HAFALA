cmake_minimum_required(VERSION 3.12)
project(hw2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(hw2 main.cpp defines.h bank.cpp ATMs.cpp account.cpp account.h ATMs.h bank.h)
