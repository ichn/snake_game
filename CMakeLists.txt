cmake_minimum_required(VERSION 3.6)
project(snake_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gameBoard.h)
add_executable(snake_game ${SOURCE_FILES})

