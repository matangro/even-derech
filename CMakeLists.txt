cmake_minimum_required(VERSION 3.15)
project(even-derech)

set(CMAKE_CXX_STANDARD 14 )
set(CMAKE_CXX_FLAGS  "-pthread")
add_executable(even-derech main.cpp Command.h implemets.h implements.cpp SingleMapOfVar.cpp SingleMapOfVar.h ex1.h ex1.cpp Expression.h Variable.h)