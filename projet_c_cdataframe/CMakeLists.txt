cmake_minimum_required(VERSION 3.27)
project(projet_c_cdataframe LANGUAGES C)

set(CMAKE_CXX_STANDARD 17)

add_executable(projet_c_cdataframe main.cpp
        columns.c
        columns.h
        cdataframes.h
        cdataframes.c
        main.c
        function.c)
