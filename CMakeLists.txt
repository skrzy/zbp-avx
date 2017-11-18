cmake_minimum_required(VERSION 3.8)
project(zbp_avx)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Jacobi.h Jacobi.cpp SystemOfEquations.h SystemofEquations.cpp vectorclass/vectorclass.h)

#add_compile_options()

add_executable(zbp_avx ${SOURCE_FILES})