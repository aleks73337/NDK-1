cmake_minimum_required(VERSION 3.12)
project(Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(Test main.cpp Node.cpp Node.h Tree.cpp Tree.h DK_Tree.cpp DK_Tree.h)