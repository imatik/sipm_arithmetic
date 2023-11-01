cmake_minimum_required(VERSION 3.26)
project(Simple_arithmetic C)

set(CMAKE_C_STANDARD 11)

add_executable(Simple_arithmetic main.c
        BigInt_class.h
        event_class.h
        fileworker.h)
