cmake_minimum_required(VERSION 3.17)
project(defender)

set(CMAKE_CXX_STANDARD 17)

add_executable(defender main.cpp PortScanner.h PortScanner.cpp utils.cpp utils.h)